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
    Table::Table(const Schema &schema, const std::string &dbname) {
        for (auto page: pages) {
            page = nullptr;
        }
        schema_ = schema;
        table_name_ = schema.table_name_;
        tuple_per_page_ = ANTIDB_PAGE_SIZE / schema.GetSize();
        tuple_max_num_ = tuple_per_page_ * TABLE_MAX_PAGE;
        diskManager_ = new DiskManager(DATA_PATH + "/" + dbname + "/" + schema_.table_name_ + DATA_FORMAT);
    }

    Table::~Table() {
        page_id_t pageId = 0;
        for (; pageId < TABLE_MAX_PAGE; pageId++) {
            if (pages[pageId] != nullptr) {
                diskManager_->WritePage(pageId, (char *) pages[pageId]);
                free(pages[pageId]);
            }
        }
        diskManager_->ShutDown();
        delete diskManager_;
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
            diskManager_->ReadPage(page_id, (char *) pages[page_id]);
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

    const Schema &Table::getSchema() const {
        return schema_;
    }

    std::string Table::getTableName() const {
        return table_name_;
    }

    uint32_t Table::getCntTuple() const {
        return cnt_tuple_;
    }

    uint32_t Table::getTuplePerPage() const {
        return tuple_per_page_;
    }

    uint32_t Table::getTupleMaxNum() const {
        return tuple_max_num_;
    }

} // antidb