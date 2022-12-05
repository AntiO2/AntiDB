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

    auto SelectExecutor::ReadTuple(Table &t, const tuple_id_t tid) {
        std::vector<Value> values;
        Tuple tuple(t.getSchema().GetSize());
        t.ReadTuple(tuple, tid);
        return tuple;
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