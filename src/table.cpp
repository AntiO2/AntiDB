//
// Created by Anti on 2022/12/1.
//
#include <memory>
#include <cstring>
#include <filesystem>
#include "antidb/table.h"
#include "antidb/exception.h"

namespace antidb {
    /**
     * 通过schema创建一个tuple
     * @param schema
     */
    Table::Table(const Schema &schema) {
        for (auto page: pages) {
            page = nullptr;
        }
        schema_ = schema;
        table_name_ = schema.table_name_;
        tuple_per_page_ = ANTIDB_PAGE_SIZE / schema.GetSize();
        tuple_max_num_ = tuple_per_page_ * TABLE_MAX_PAGE;
    }

    Table::~Table() {
        for (auto page: pages) {
            free(page);
        }
    }

    void Table::WriteTuple(Tuple &tuple) {
        if (cnt_tuple_ >= tuple_max_num_) {
            throw error_table("AntiDB:Table Overflow");
        }
        auto dst = LocateTuple(cnt_tuple_);
        tuple.write(dst);
        cnt_tuple_++;

    }

    char *Table::LocateTuple(const uint32_t &RID) {
        if (RID >= tuple_max_num_) {
            throw error_table("AntiDB:Table Overflow");
        }
        auto page_id = RID / tuple_per_page_;
        if (pages[page_id] == nullptr) {
            pages[page_id] = malloc(ANTIDB_PAGE_SIZE);
            memset(pages[page_id], 0, ANTIDB_PAGE_SIZE);
        }
        if (pages[page_id] == nullptr) {
            throw error_table("Memory Over Flow!");
        }

        auto tuple_offset_in_page = RID % tuple_per_page_;//tuple在页内的偏移数
        auto tuple_offset_byte = tuple_offset_in_page * schema_.GetSize();
        return (char *) pages[page_id] + tuple_offset_byte;
    }

    void Table::ReadTuple(Tuple &tuple, const tuple_id_t tupleId) {
        if (tupleId >= cnt_tuple_) {
            throw error_table("AntiDB: Try Read tuple which is Out of Range!!!plz check it ");
        }
        tuple.read((char *) LocateTuple(tupleId));
    }



} // antidb