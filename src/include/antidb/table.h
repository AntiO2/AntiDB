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
#include "antidb/tuple.h"
namespace antidb {
    /**
     * 表类
     */
    class Table {
    public:
        explicit Table(const Schema &schema);

        ~Table();

        void WriteTuple(Tuple &tuple);

        void ReadTuple(Tuple &tuple, tuple_id_t tupleId);

        char *LocateTuple(const uint32_t &RID);//通过编号获取写入位置


    private:
        Schema schema_;
        std::string table_name_;
        void *pages[TABLE_MAX_PAGE]{};
        std::fstream page_io_;
        uint32_t cnt_tuple_{0};
        uint32_t tuple_per_page_;//每页存放tuple数目
        uint32_t tuple_max_num_;//最多tuple数目
    };

} // antidb

#endif //ANTIDB_TABLE_H
