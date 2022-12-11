//
// Created by Anti on 2022/11/28.
//

#ifndef ANTIDB_CONFIG_H
#define ANTIDB_CONFIG_H

#include <cstdint>
#include <string>

namespace antidb {
    static constexpr int ANTIDB_PAGE_SIZE = 4096;
    static constexpr int TABLE_MAX_PAGE = 1024;
    static constexpr int MAX_STRING_SIZE = 256;
    const std::string DATA_PATH = "./data/";
    const std::string DB_INFO = "/information.db";
    const std::string DATA_FORMAT = ".dat";
    const std::string INFO_FORMAT = ".info";
    const std::string IDX_FORMAT = ".idx";
    const std::string ANTIDB_VERSION = "0.2";
    enum SQL_type {
        NONE,
        INSERT,
        CREATE,
        SELECT,
        DELETE,
        DROP,
        USE,
        EXIT,
        HELP,
        SHOW
    };
    enum CREATE_TYPE {
        CREATE_TABLE,
        CREATE_DATABASE
    };
    enum SHOW_TYPE {
        SHOW_TABLE,
        SHOW_DATABASE
    };
    enum TYPE_ID {
        INT,
        STRING
    };
    enum DROP_TYPE {
        DROP_TABLE,
        DROP_DATABASE
    };
    enum CONDITION_TYPE {
        NO_CONDITION,
        GREATER,
        LESS,
        EQUAL
    };

    using page_id_t = int32_t;
    using tuple_id_t = uint32_t;

}
#endif //ANTIDB_CONFIG_H

