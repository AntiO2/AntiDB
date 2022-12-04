//
// Created by Anti on 2022/12/4.
//

#ifndef ANTIDB_DATABASE_H
#define ANTIDB_DATABASE_H

#include <string>
#include <filesystem>
#include <fstream>
#include <set>
#include <map>
#include <ostream>
#include "antidb/trie.h"
#include "antidb/config.h"
#include "antidb/exception.h"
#include "antidb/table.h"

namespace antidb {

    class Database {
    public:
        Database() : is_used_(false) {};

        explicit Database(const std::string &db_name);

        ~Database();

        [[nodiscard]] const std::string &getDbName() const;

        void setDbName(const std::string &dbName);

        bool find(const std::string &table);

        void insert(const std::string &table_name);

        void addTable(Table *table);

        friend std::ostream &operator<<(std::ostream &os, const Database &database);

    private:
        std::string db_name_;
        std::set<std::string> table_set_;
        std::fstream db_stream_;
        bool is_used_{true};
        std::map<std::string, Table *> table_map_;


    };

} // antidb

#endif //ANTIDB_DATABASE_H
