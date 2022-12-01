//
// Created by Anti on 2022/11/30.
//

#ifndef ANTIDB_SCHEMA_H
#define ANTIDB_SCHEMA_H

#include <vector>
#include "antidb/column.h"
#include "antidb/config.h"

namespace antidb {
    class Schema {
    public:
        Schema() = default;

        void AddCols(Column &col) {
            cols_.push_back(col);
            offset_ += col.GetColumnSize();
        }

    private:
        std::vector<Column> cols_;
        uint32_t offset_;
    };
}

#endif //ANTIDB_SCHEMA_H
