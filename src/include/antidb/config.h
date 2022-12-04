//
// Created by Anti on 2022/11/28.
//

#ifndef ANTIDB_CONFIG_H
#define ANTIDB_CONFIG_H

#include <cstdint>
#include <string>

namespace antidb {
    static constexpr int ANTIDB_PAGE_SIZE = 4096;
    static constexpr int TABLE_MAX_PAGE = 256;
    static constexpr int MAX_STRING_SIZE = 256;
    const std::string DATA_PATH = "./data/";
    const std::string DB_INFO = "/information.db";
    const std::string DATA_FORMAT = ".dat";
    enum SQL_type {
        INSERT,
        CREATE,
        SELECT,
        DELETE,
        DROP,
        USE,
        EXIT
    };
    enum CREATE_TYPE {
        CREATE_TABLE,
        CREATE_DATABASE
    };
    enum TYPE_ID {
        INT,
        STRING
    };
    using page_id_t = int32_t;
    using tuple_id_t = uint32_t;

}
#endif //ANTIDB_CONFIG_H

