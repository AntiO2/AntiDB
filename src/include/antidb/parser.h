//
// Created by Anti on 2022/11/25.
//
#pragma once
#ifndef ANTIDB_PHASER_H
#define ANTIDB_PHASER_H

#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "antidb/exception.h"
#include "antidb/config.h"
#include "antidb/statement.h"

namespace antidb {


    class Parser {
    public:
        static auto get_token(std::string &command, std::vector<std::string> &tokens) -> void;

        static auto parse_sql(std::string &sql_command, SQL_type &sqlType) -> bool;

        static auto parse_sql(Statement &statement) -> Statement *;

        static auto parse_create(Statement &statement) -> Create_Statement *;

        static auto parse_insert(Statement &statement) -> Statement *;

        static auto parse_select(Statement &statement) -> Statement *;

        static auto parse_drop(Statement &statement) -> Statement *;

        static auto parse_delete(Statement &statement) -> Statement *;

        static auto parse_use(Statement &statement) -> Use_Statement *;

        static auto is_token(char &c) -> bool;

        static auto is_space(char &c) -> bool;

    private:
        /**
         * 去除最后的分号
         * @param command 一条SQL语句
         */
        static auto get_rid_last_sem(std::string &command) -> void;
    };

} // antidb

#endif //ANTIDB_PHASER_H
