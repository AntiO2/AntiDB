//
// Created by Anti on 2022/11/30.
//
#pragma once
#ifndef ANTIDB_SCHEMA_H
#define ANTIDB_SCHEMA_H

#include <utility>
#include <vector>
#include <iostream>
#include "antidb/column.h"
#include "antidb/config.h"

namespace antidb {
    class Schema {

    public:
        Schema() = default;

        void AddCols(Column &&col) {
            cols_.push_back(col);
            offset_ += col.GetColumnSize();
        }

        [[nodiscard]] uint32_t GetSize() const {
            return offset_;
        }

        [[nodiscard]] bool Has_Primary() const {
            return has_primary;
        };

        auto Set_Primary(bool is_primary) -> void {
            has_primary = is_primary;
        }

        friend std::ostream &operator<<(std::ostream &os, const Schema &schema) {
            os << schema.table_name_ << " " << schema.offset_ << " "
               << schema.has_primary << std::endl;
            for (const auto &col: schema.cols_) {
                os << col << std::endl;
            }
            return os;
        }

        friend std::ifstream &operator>>(std::ifstream &ifs, Schema &schema) {
            ifs >> schema.table_name_ >> schema.offset_ >> schema.has_primary;
            while (!ifs.eof()) {
                Column col;
                ifs >> col;
                schema.cols_.emplace_back(col);
            }
            return ifs;
        }

        std::string table_name_;
        std::vector<Column> cols_;
    private:

        uint32_t offset_{0};
        bool has_primary{false};
    };
}

#endif //ANTIDB_SCHEMA_H
