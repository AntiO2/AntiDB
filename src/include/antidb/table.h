//
// Created by Anti on 2022/12/1.
//

#ifndef ANTIDB_TABLE_H
#define ANTIDB_TABLE_H

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include "antidb/schema.h"
#include "antidb/config.h"

namespace antidb {
    /**
     * 表类
     */
    class Table {
    public:
        explicit Table(const std::string &table_name, Schema &schema);

    private:
        Schema schema_;
        std::string table_name_;
        char pages[ANTIDB_PAGE_SIZE * TABLE_MAX_PAGE];
        std::fstream page_io_;
    };

} // antidb

#endif //ANTIDB_TABLE_H
