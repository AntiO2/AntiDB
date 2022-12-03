//
// Created by Anti on 2022/11/29.
//

#ifndef ANTIDB_VALUE_H
#define ANTIDB_VALUE_H

#include <memory>
#include <charconv>
#include "antidb/config.h"

namespace antidb {
    class Value {


    public:
        Value(TYPE_ID typeId, int value) {
            value_.int32_ = value;
            value_size_ = 4;
            typeId_ = typeId;
        }

        Value(TYPE_ID typeId, char *str, size_t len) {
            memcpy(value_.str_, str, len);
            //TODO(ANTIO2) 检查是否需要加'\0'
            value_size_ = MAX_STRING_SIZE;
            typeId_ = typeId;
        }

        /**
         * FIXME(AntiO2) 名字为Write更合适
         * 将当前value写入指定位置
         * @param data
         */
        void GetValue(char *data) {

            switch (typeId_) {
                case INT: {
                    memcpy(data, (unsigned char *) &value_, 4);
                    break;
                }
                case STRING:

                    memcpy(data, (unsigned char *) &value_, MAX_STRING_SIZE);
                    break;
            }
        }

        [[nodiscard]] uint32_t GetSize() const {
            return value_size_;
        }

    private:
        union {
            int int32_;
            char str_[MAX_STRING_SIZE];
        } value_{};
        uint32_t value_size_;
        TYPE_ID typeId_;
    };
}


#endif //ANTIDB_VALUE_H
