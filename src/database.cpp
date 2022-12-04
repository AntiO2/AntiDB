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
            std::ifstream ifs(DATA_PATH + db_name + DB_INFO, std::fstream::in);
            if (!ifs.is_open()) {
                throw error_database("DataBase info has been ruined!!!");
            }
            std::string table_name;
            while (!ifs.eof()) {
                ifs >> table_name;
                table_trie_.Insert(table_name, true);
            }
            ifs.close();
        } else {
            std::filesystem::create_directories(DATA_PATH + db_name);
            std::fstream fs(DATA_PATH + db_name + DB_INFO, std::ios::trunc | std::ios::out);//创建文件
            fs.open(DATA_PATH + db_name + DB_INFO, std::ios::trunc | std::ios::out);
            fs.close();
        }
    }
} // antidb