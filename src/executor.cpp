//
// Created by Anti on 2022/11/29.
//
#include <filesystem>
#include "antidb/executor.h"
#include "antidb/exception.h"
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
} // antidb