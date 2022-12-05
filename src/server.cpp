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
        std::unique_ptr<Database> db_used_ = nullptr;//现在使用的db
        while (true) {
            std::string sql;
            std::getline(std::cin, sql, ';');
            Statement stmt(sql);
            auto stmt_p = Parser::parse_sql(stmt);
            try {
                switch (stmt_p->sqlType_) {
                    case INSERT:
                        break;
                    case CREATE:

                        break;
                    case SELECT:
                        break;
                    case DELETE:
                        break;
                    case DROP: {
                        auto name = ((Drop_Statement *) stmt_p)->name_;
                        if (db_used_ == nullptr) {
                            throw error_database("No database selected");
                        }
                        switch (((Drop_Statement *) stmt_p)->dropType_) {
                            case DROP_TABLE:
                                DropExecutor::DropTable(name, &db_used_);
                                break;
                            case DROP_DATABASE:
                                if (db_used_->getDbName() == name) {
                                    throw error_database("Database " + name + " is now used,can't drop it!");
                                }
                                DropExecutor::DropDatabase(name);
                                break;
                        }
                        break;
                    }

                    case USE: {
                        std::string db_name = ((Use_Statement *) stmt_p)->db_name_;
                        db_used_ = UseExecutor::UseDataBase(db_name);
                        break;
                    }
                    case EXIT:
                        db_used_ = nullptr;
                        break;
                }
            }
            catch (std::exception &e) {
                e.what();
            }
        }
    }
} // antidb