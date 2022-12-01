//
// Created by Anti on 2022/11/29.
//

#ifndef ANTIDB_VALUE_H
#define ANTIDB_VALUE_H

#include <memory>
#include "antidb/config.h"

namespace antidb {
    class Value {
    public:
        Value(TYPE_ID typeId, int value) {
            value_.int32_ = value;
            value_size_ = 4;
        }

        Value(TYPE_ID typeId, char *str, size_t len) {
            memcpy(value_.str_, str, len);
        }

    private:
        union {
            int int32_;
            char *str_;
        } value_;
        uint32_t value_size_;
    };
}


#endif //ANTIDB_VALUE_H
