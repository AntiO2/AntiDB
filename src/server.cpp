//
// Created by Anti on 2022/12/2.
//

#include <iostream>
#include "antidb/server.h"
#include "antidb/parser.h"
#include "antidb/statement.h"
#include "antidb/executor.h"

namespace antidb {
    void Server::OpenServer() {
        while (true) {
            std::string sql;
            std::getline(std::cin, sql, ';');
            Statement stmt(sql);
            auto stmt_p = Parser::parse_sql(stmt);
            if (stmt_p->sqlType_ == EXIT) {
                break;
            }
            switch (stmt_p->sqlType_) {
                case INSERT:
                    break;
                case CREATE:

                    break;
                case SELECT:
                    break;
                case DELETE:
                    break;
                case DROP:
                    break;
                case USE:
                    std::string db_name = ((Use_Statement *) stmt_p)->db_name_;
                    try { UseExecutor::UseDataBase(db_name, database_); }
                    catch (error_command &error_command_) {
                        error_command_.what();
                    }
                    break;
            }
        }
    }
} // antidb