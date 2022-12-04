//
// Created by Anti on 2022/12/4.
//

#ifndef ANTIDB_DATABASE_H
#define ANTIDB_DATABASE_H

#include <string>
#include <filesystem>
#include <fstream>
#include "antidb/trie.h"
#include "antidb/config.h"
#include "antidb/exception.h"

namespace antidb {

    class Database {
    public:
        Database(const std::string &db_name);

        Trie table_trie_;
    private:
        std::string db_name_;
    };

} // antidb

#endif //ANTIDB_DATABASE_H
