//
// Created by Anti on 2022/11/29.
//

#ifndef ANTIDB_COLUMN_H
#define ANTIDB_COLUMN_H
#include <string>
#include "antidb/config.h"
namespace antidb{
    class Column {
    friend class Table;
    friend class Schema;
    public:
        Column(TYPE_ID type,std::string& col_name,bool is_primary)
        {
            type_=type;
            col_name_=col_name;
            is_primary_=is_primary;
            if(type==INT)
            {
                col_size_=4;
            }
            if(type==STRING)
            {
                col_size_ = 256;
            }
        }
        Column(TYPE_ID type,std::string& col_name)
        {
            type_=type;
            col_name_=col_name;
        }
        auto GetType()->TYPE_ID{
            return type_;
        }
        auto GetColumnSize()->uint32_t {
            return col_size_;
        }
        auto GetColumnName()->std::string {
            return col_name_;
        }
        auto Is_Primary()->bool {
            return is_primary_;
        };
    private:
        TYPE_ID type_;
        std::string col_name_;
        bool is_primary_{false};
        uint32_t col_size_;
    };
}
#endif //ANTIDB_COLUMN_H
