//
// Created by Anti on 2022/11/29.
//

#ifndef ANTIDB_EXECUTOR_H
#define ANTIDB_EXECUTOR_H

#include <string>
#include <memory>
#include "antidb/config.h"
#include "statement.h"

namespace antidb {

    class AbstractExecutor {
    };

    class CreateExecutor : AbstractExecutor {
    public:
        explicit CreateExecutor(Create_Statement &createStatement);

        static auto CreateDataBase(const std::string &database_name) -> bool;
    };

    class UseExecutor : AbstractExecutor {
    public:

        static auto UseDataBase(const std::string &database_name, std::string &server_db_name) -> void;
    };
} // antidb

#endif //ANTIDB_EXECUTOR_H
