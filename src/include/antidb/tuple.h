//
// Created by Anti on 2022/11/29.
//

#ifndef ANTIDB_TUPLE_H
#define ANTIDB_TUPLE_H

#include <vector>
#include "antidb/value.h"
#include "antidb/schema.h"
#include <cstring>
#include <ostream>

namespace antidb {

    class Tuple {
    public:
        Tuple(uint32_t size) {
            data_ = malloc(size);
            memset(data_, 0, size);
            size_ = size;
        }

        Tuple(std::vector<Value> &values, Schema &schema) {
            size_ = schema.GetSize();
            data_ = malloc(size_);
            memset(data_, 0, size_);
            uint32_t offset = 0;
            for (auto value: values) {
                value.GetValue((char *) data_ + offset);
                offset += value.GetSize();
            }
        };

        ~Tuple() {
            free(data_);
            data_ = nullptr;
        }

        /**
         * 将当前tuple写入dst中
         * @param dst
         */
        void write(char *dst) const {
            memcpy(dst, data_, size_);
        }

        /**
         * 从src读取指定信息
         * @param src
         */
        void read(char *src) {
            memcpy(data_, src, size_);
        }

        friend std::ostream &operator<<(std::ostream &os, const Tuple &tuple) {
            os << "size_: " << tuple.size_ << " data_: " << tuple.data_;
            return os;
        }

    private:
        uint32_t size_;
        void *data_{nullptr};
    };
} // antidb

#endif //ANTIDB_TUPLE_H



