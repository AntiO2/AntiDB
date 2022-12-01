//
// Created by Anti on 2022/11/29.
//
#include <filesystem>
#include "antidb/executor.h"

namespace antidb {
    CreateExecutor::CreateExecutor(Create_Statement&createStatement) {
        if (createStatement.createType_ == CREATE_DATABASE) {
            CreateDataBase(createStatement.name_);
        }
    }

    auto CreateExecutor::CreateDataBase(const std::string &database_name) -> bool {
        if(database_name.empty()){
            return false;
        }
        return std::filesystem::create_directories(DATA_PATH+database_name);
    }

} // antidb