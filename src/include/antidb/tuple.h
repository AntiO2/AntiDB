//
// Created by Anti on 2022/11/29.
//

#ifndef ANTIDB_TUPLE_H
#define ANTIDB_TUPLE_H

#include <vector>
#include "antidb/value.h"
#include "antidb/schema.h"
namespace antidb {

    class Tuple {
    public:
        Tuple(std::vector<Value> &values, Schema &schema) {
            size_ = schema.GetSize();
            data_ = new char[size_];
            uint32_t offset = 0;
            for (auto value: values) {
                value.GetValue(data_ + offset);
                offset += value.GetSize();
            }
        };

        ~Tuple() {
            delete data_;
            data_ = nullptr;
        }

    private:
        uint32_t size_;
        char *data_{nullptr};
    };
} // antidb

#endif //ANTIDB_TUPLE_H
