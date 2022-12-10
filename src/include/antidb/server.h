//
// Created by Anti on 2022/12/2.
//

#ifndef ANTIDB_SERVER_H
#define ANTIDB_SERVER_H

#include <string>
#include "antidb/database.h"
#include "antidb/executor.h"
namespace antidb {

    class Server {
    public:
        Server() = default;

        void OpenServer();

        static auto ExecuteOneSQL(std::string &&sql, std::unique_ptr<Database> *db) -> void;
    };

} // antidb

#endif //ANTIDB_SERVER_H
