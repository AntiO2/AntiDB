//
// Created by Anti on 2022/12/2.
//

#ifndef ANTIDB_SERVER_H
#define ANTIDB_SERVER_H

#include <string>

namespace antidb {

    class Server {
    public:
        Server() = default;

        std::string database_;//现在使用的db名称
        void OpenServer();
    };

} // antidb

#endif //ANTIDB_SERVER_H
