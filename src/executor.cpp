//
// Created by Anti on 2022/11/29.
//
#include <filesystem>
#include <memory>
#include "antidb/executor.h"
#include "antidb/exception.h"
#include "antidb/table.h"

namespace antidb {
    /**
     * 已弃用
     * @param createStatement
     */
    CreateExecutor::CreateExecutor(Create_Statement &createStatement) {
        if (createStatement.createType_ == CREATE_DATABASE) {
            if (!CreateDataBase(createStatement.name_)) {
                throw error_command("DataBase " + createStatement.name_ + " already exists");
            }
        }
    }

    auto CreateExecutor::CreateDataBase(const std::string &database_name) -> bool {
        if (database_name.empty()) {
            return false;
        }
        if (std::filesystem::exists(DATA_PATH + database_name) && std::filesystem::exists(DATA_PATH + database_name)) {
            throw error_command("DataBase " + database_name + " exists");
        }
        auto db = new Database(database_name);
        delete db;
        return true;
    }

    auto CreateExecutor::CreateTable(const Create_Statement &createStatement, Database &database) -> Table * {
        auto table = new Table(createStatement.schema_, database.getDbName());
        try {
            database.addTable(table);
        }
            /**
             * 如果重名，则抛出
             */
        catch (error_table &e) {
            delete table;
            throw e;
        }
        /**
         * create table 还需要记录元信息
         */
        std::fstream fsm;
        fsm.open(DATA_PATH + database.getDbName() + "/" + createStatement.schema_.table_name_ + ".info",
                 std::ios::trunc | std::ios::out);
        if (!fsm.is_open()) {
            throw error_file("Cant open information file : " + createStatement.schema_.table_name_ + ".info");
        }
        fsm << createStatement.schema_;
        fsm.flush();
        fsm.close();
        return table;
    }

    /**
     * 判断数据库是否存在
     * @param database_name
     * @return
     */
    auto UseExecutor::UseDataBase(const std::string &database_name) -> std::unique_ptr<Database> {
        if (!std::filesystem::exists(DATA_PATH + database_name)) {
            throw error_command("DataBase \"" + database_name + "\" doesn't exist!!!");
        }
        auto db = std::make_unique<Database>(database_name);
        db->recover();
        return db;
    }

    /**
     * 将tuple写入指定位置
     * @param tuple
     * @param dst
     * @return
     */
    auto InsertExecutor::WriteTuple(Tuple &tuple, Table &table) -> void {
        table.WriteTuple(tuple);
    }

    auto InsertExecutor::WriteTuple(Tuple &tuple, Table *table) -> void {
        table->WriteTuple(tuple);
    }

    auto InsertExecutor::InsertByStmt(Insert_Statement *i_stmt, std::unique_ptr<Database> *db) -> void {
        auto table_name = i_stmt->table_name_;
        auto table = db->get()->getTable(table_name);
        if (table == nullptr) {
            throw error_table("No table named " + table_name);
        }
        /**
         * 将value转化为tuple
         */
        auto schema = table->getSchema();
        std::vector<Value> values;
        for (auto i = 0; i < schema.cols_.size(); i++) {
            switch (schema.cols_[i].type_) {
                case INT:
                    values.emplace_back(Parser::str_to_value(INT, i_stmt->value_str[i]));
                    break;
                case STRING:
                    values.emplace_back(Parser::str_to_value(STRING, i_stmt->value_str[i]));
                    break;
            }
        }
        if (schema.Has_Primary()) {
            /**
             * FIXME() 这里可能出现主键重复的情况
             *
             */
            auto tid = table->WriteTuple(Tuple(values, schema));
            int key = values.at(schema.getKeyId()).GetInt();
            table->Insert_Key(key, tid);
        } else {
            table->WriteTuple(Tuple(values, schema));
        }

    }


    auto SelectExecutor::ReadTuple(Table *t, const tuple_id_t tid) -> Tuple {
        std::vector<Value> values;
        Tuple tuple(t->getSchema().GetSize());
        if (t->is_spare(tid)) {
            throw error_table("Inner error:Try read deleted tuple.Please Connect antio2@qq.com");
        }
        t->ReadTuple(tuple, tid);
        return tuple;
    }

    auto
    SelectExecutor::Select(Select_Statement *s_stmt, std::unique_ptr<Database> *db) -> std::vector<std::vector<Value>> {
        std::vector<std::vector<Value>> results;
        if (db == nullptr) {
            throw error_database("No database using");
        }
        auto table = db->get()->getTable(s_stmt->table_name_);
        if (table == nullptr) {
            throw error_table("No table named " + s_stmt->table_name_);
        }
        /**
         * 如果没有主键,遍历所有tuple 或者有主键但是没有条件
         * 或者是有主键，有条件，但是需要比较的列和主键不是同一列
         */
        auto tuple_size = table->getSchema().GetSize();
        if (!table->getSchema().Has_Primary() || (table->getSchema().Has_Primary() && (!s_stmt->has_condition ||
                                                                                       (s_stmt->has_condition &&
                                                                                        (s_stmt->condition.getColName() !=
                                                                                         table->getSchema().cols_.at(
                                                                                                 table->schema_.getKeyId()).col_name_))))) {

            for (auto i = 0; i < table->getCntTuple(); i++) {
                if (table->is_spare(i)) {
                    continue;
                }
                Tuple tuple(tuple_size);
                table->ReadTuple(tuple, i);
                std::vector<Value> vs;
                table->Parse_tuple(vs, tuple);
                if (s_stmt->has_condition) {
                    /**
                     * FIXME(AntiO2) 想到了一个问题，如果列的名字相同呢？parser是没有处理这种情况的
                     *
                     * 解决方案：在table中创建一个parser的map，这样由解决了寻找col_name的方式，又能找出col_name相同的情况
                     */
                    auto col_condition = table->schema_.GetColId(s_stmt->condition.getColName());
                    if (col_condition == -1) {
                        throw error_command("No column " + s_stmt->condition.getColName());
                    }

                    if (s_stmt->condition.condition_is_true(vs[col_condition])) {
                        continue;
                    }
                }
                results.emplace_back(vs);
            }
        } else {
            int left = INT_MIN;
            int right = INT_MAX;
            tuple_id_t tid{0};
            std::vector<tuple_id_t> tids_;
            switch (s_stmt->condition.getConditionType()) {

                case NO_CONDITION:
                    break;
                case GREATER: {
                    auto left_ = s_stmt->condition.getComparedNum();
                    table->bpt->search_range(&left_, right, tids_, table->getRealTuple() + 1);
                    break;
                }
                case LESS: {
                    auto right_ = s_stmt->condition.getComparedNum() - 1;
                    table->bpt->search_range(&left, right_, tids_, table->getRealTuple() + 1);
                    break;
                }

                case EQUAL:
                    table->bpt->search(s_stmt->condition.getComparedNum(), &tid);
                    tids_.push_back(tid);
                    break;
            }
            /**
             * 根据tuple id,寻找对应的tuple
             * FIXME 这里和上面的代码有重复，考虑优化为函数
             */
            for (auto a_tid: tids_) {
                Tuple tuple(tuple_size);
                table->ReadTuple(tuple, a_tid);
                std::vector<Value> vs;
                table->Parse_tuple(vs, tuple);
                results.emplace_back(vs);
            }
        }
        if (!s_stmt->select_all_) {
            auto col_selected = table->schema_.GetColId(s_stmt->col_name_);
            if (col_selected == -1) {
                throw error_command("No column " + s_stmt->col_name_);
            }
            Projection(results, col_selected);
        }
        return results;
    }

    auto SelectExecutor::Projection(std::vector<std::vector<Value>> &values, uint32_t col_id) -> void {
        for (auto tuple_value: values) {
            auto selected_value = tuple_value[col_id];
            tuple_value.clear();
            tuple_value.emplace_back(selected_value);
        }
    }


    auto DropExecutor::DropTable(const std::string &table_name, std::unique_ptr<Database> *db) -> void {
        if (db == nullptr) {
            throw error_database("No database selected");
        }
        db->get()->removeTable(table_name);
    }

    auto DropExecutor::DropDatabase(const std::string &db_name) -> void {
        std::filesystem::remove_all(DATA_PATH + db_name);
    }
} // antidb