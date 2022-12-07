//
// Created by Anti on 2022/11/29.
//
#pragma once
#ifndef ANTIDB_STATEMENT_H
#define ANTIDB_STATEMENT_H

#include <string>
#include <utility>
#include <vector>

#include "antidb/config.h"
#include "antidb/schema.h"
#include "antidb/condition.h"
namespace antidb {
    /**
     * 这是一个抽象的声明，用于获取token
     */
    class Statement {
    public:
        explicit Statement(std::string commandline) : commandline_(std::move(commandline)) {};
        std::string commandline_;
        std::vector<std::string> tokens;
        SQL_type sqlType_{EXIT};
    };

    class Create_Statement : public Statement {
    public:
        explicit Create_Statement(Statement &&statement) : Statement(std::move(statement)) {};

        std::string name_;
        CREATE_TYPE createType_{CREATE_DATABASE};
        Schema schema_;
    };

    class Use_Statement : public Statement {
    public:
        explicit Use_Statement(Statement &&stmt) : Statement(std::move(stmt)) {};
        std::string db_name_;
    };

    class Drop_Statement : public Statement {
    public:
        explicit Drop_Statement(Statement &&stmt) : Statement(std::move(stmt)) {};
        std::string name_;
        DROP_TYPE dropType_{DROP_DATABASE};
    };

    /**
     * TODO 生成
     */
    class Select_Statement : public Statement {
    public:
        explicit Select_Statement(Statement &&statement) : Statement(std::move(statement)) {};
        std::string table_name_;
        /**
         * 选择的列名
         */
        std::string col_name_;
        bool select_all_{false};
        bool has_condition{false};
        Condition condition;
    };

    class Delete_Statement : public Statement {
    public:
        explicit Delete_Statement(Statement &&statement) : Statement(std::move(statement)) {};
        std::string table_name_;
        bool has_condition{false};
        Condition condition;
    };

    class Insert_Statement : public Statement {
    public:
        explicit Insert_Statement(Statement &&statement) : Statement(std::move(statement)) {};
        std::string table_name_;
        std::vector<std::string> value_str;
    };
} // antidb


#endif //ANTIDB_STATEMENT_H
