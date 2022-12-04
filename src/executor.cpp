//
// Created by Anti on 2022/11/29.
//
#include <filesystem>
#include "antidb/executor.h"
#include "antidb/exception.h"
#include "antidb/table.h"
namespace antidb {
    CreateExecutor::CreateExecutor(Create_Statement&createStatement) {
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
        return std::filesystem::create_directories(DATA_PATH + database_name);
    }

    auto CreateExecutor::CreateTable(const Create_Statement &createStatement, const std::string &db_name) -> void {
        if (db_name.empty()) {
            throw error_database("No database selected");
        }
        if (!(std::filesystem::exists(db_name) && std::filesystem::is_directory(db_name)))//检查是否存在数据库
        {
            throw error_database("No such database: " + db_name);
        }
        if (std::filesystem::exists(db_name + "/" + createStatement.name_ + ".dat")) {
            throw error_table("Already exists table " + createStatement.name_);
        }
        auto t = new Table(createStatement.schema_);

    }

    /**
     * 判断数据库是否存在
     * @param database_name
     * @return
     */
    auto UseExecutor::UseDataBase(const std::string &database_name, std::string &server_db_name) -> void {
        if (!std::filesystem::exists(DATA_PATH + database_name)) {
            throw error_command("DataBase \"" + database_name + "\" doesn't exist!!!");
            return;
        }
        server_db_name = database_name;
    }

    /**
     * 将tuple写入指定位置
     * @param tuple
     * @param dst
     * @return
     */
    auto InsertExecutor::WriteTuple(Tuple &tuple, Table &table) {
        table.WriteTuple(tuple);
        return;
    }

    auto SelectExecutor::ReadTuple(Table &t, const tuple_id_t tid) {
        std::vector<Value> values;
        Tuple tuple(t.getSchema().GetSize());
        t.ReadTuple(tuple, tid);
        return tuple;
    }
} // antidb