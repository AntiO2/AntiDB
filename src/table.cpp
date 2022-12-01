//
// Created by Anti on 2022/12/1.
//
#include <memory>
#include <cstring>
#include <filesystem>
#include "antidb/table.h"
#include "antidb/exception.h"

namespace antidb {

    Table::Table(const std::string &table_name, Schema &schema) {
        table_name_ = table_name;
        memset(pages, 0, sizeof(pages));
        /**
         * TODO(AntiO2) 如果在磁盘上已经存在该表名字
         *
         */
        if (std::filesystem::exists(table_name + ".dat")) {

        } else {
            std::
        }
    }
} // antidb