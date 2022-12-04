//
// Created by Anti on 2022/12/2.
//

#ifndef ANTIDB_SERVER_H
#define ANTIDB_SERVER_H

#include <string>
#include "antidb/database.h"
namespace antidb {

    class Server {
    public:
        Server() = default;

        std::unique_ptr<Database> db_used_;//现在使用的db
        void OpenServer();
    };

} // antidb

#endif //ANTIDB_SERVER_H
