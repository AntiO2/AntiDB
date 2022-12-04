//
// Created by Anti on 2022/12/4.
//

#include <utility>

#include "antidb/database.h"

namespace antidb {
    Database::Database(const std::string &db_name) {
        db_name_ = db_name;
        if (std::filesystem::exists(DATA_PATH + db_name) && std::filesystem::exists(DATA_PATH + db_name))//如果已经存在文件夹
        {
            db_stream_.open(DATA_PATH + db_name + DB_INFO, std::fstream::in);
            if (!db_stream_.is_open()) {
                db_stream_.clear();
                db_stream_.open(DATA_PATH + db_name + DB_INFO, std::ios::in | std::ios::trunc | std::ios::out);
            }
            std::string table_name;
            while (!db_stream_.eof()) {
                db_stream_ >> table_name;
                table_set_.insert(table_name);
            }
        } else {

            std::filesystem::create_directories(DATA_PATH + db_name);
            db_stream_.open(DATA_PATH + db_name + DB_INFO, std::ios::in | std::ios::trunc | std::ios::out);
        }
    }

    const std::string &Database::getDbName() const {
        return db_name_;
    }

    void Database::setDbName(const std::string &dbName) {
        db_name_ = dbName;
    }

    bool Database::find(const std::string &table) {
        return !(table_set_.find(table) == table_set_.end());
    }

    Database::~Database() {
        db_stream_.close();
        table_set_.clear();
    }

    void Database::insert(const std::string &table_name) {
        if (find(table_name)) {
            throw error_table("Table " + table_name + " already exists");
        }
        table_set_.insert(table_name);
        db_stream_ << table_name << std::endl;
    }

    void Database::addTable(Table *table) {
        std::string table_name = table->getTableName();
        insert(table_name);
        table_map_.insert(std::make_pair(table_name, table));
    }

    std::ostream &operator<<(std::ostream &os, const Database &database) {
        os << "db_name_: " << database.db_name_ << " is_used_: " << database.is_used_;
        return os;
    }
} // antidb