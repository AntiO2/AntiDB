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

    }

    auto Server::ExecuteOneSQL(std::string &&sql, std::unique_ptr<Database> *db) -> void {
        Statement stmt(sql);
        auto stmt_p = Parser::parse_sql(stmt);
        try {
            switch (stmt_p->sqlType_) {
                case INSERT:
                    if (db == nullptr) {
                        throw error_database("No database using");
                    }
                    InsertExecutor::InsertByStmt((Insert_Statement *) stmt_p, db);
                    break;
                case CREATE:
                    switch (((Create_Statement *) stmt_p)->createType_) {
                        case CREATE_DATABASE:
                            CreateExecutor::CreateDataBase(((Create_Statement *) stmt_p)->name_);
                        case CREATE_TABLE:
                            if (db == nullptr) {
                                throw error_database("No database using");
                            }
                            CreateExecutor::CreateTable(*((Create_Statement *) stmt_p), db);
                    }
                        break;
                case SELECT: {
                    if (db == nullptr) {
                        throw error_database("No database using");
                    }

                    auto results = SelectExecutor::Select((Select_Statement *) stmt_p, db);
                    PrintExecutor::PrintValue((Select_Statement *) stmt_p, std::move(results));
                    break;
                }


                case DELETE:
                    if (db == nullptr) {
                        throw error_database("No database using");
                    }
                    DeleteExecutor::DeleteByStmt((Delete_Statement *) stmt_p, db);
                    break;
                case DROP: {
                    auto name = ((Drop_Statement *) stmt_p)->name_;
                    switch (((Drop_Statement *) stmt_p)->dropType_) {
                        case DROP_TABLE:
                            DropExecutor::DropTable(name, db);
                            break;
                        case DROP_DATABASE:
                            if (db != nullptr && db->get()->getDbName() == name) {
                                throw error_database("Database " + name + " is now used,can't drop it!");
                            }
                                DropExecutor::DropDatabase(name);
                                break;
                    }
                    break;
                }

                case USE: {
                    std::string db_name = ((Use_Statement *) stmt_p)->db_name_;
                    *db = UseExecutor::UseDataBase(db_name);
                    break;
                }
                case EXIT:
                    *db = nullptr;
                    std::cout << "Bye bye" << std::endl;
                    break;
            }
            }
            catch (std::exception &e) {
                std::cout << e.what() << std::endl;
                throw e;
            }
    }
} // antidb