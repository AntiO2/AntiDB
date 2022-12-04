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
#include "antidb/disk_manager.h"
namespace antidb {
    /**
     * 表类
     */
    class Table {
    public:
        Table() = default;

        explicit Table(const Schema &schema, const std::string &dbname);

        ~Table();

        /**
         * 传入tuple，写入表中
         * @param tuple
         */
        void WriteTuple(Tuple &tuple);

        /**
         * 读出指定rid
         * @param tuple
         * @param tupleId
         */
        void ReadTuple(Tuple &tuple, tuple_id_t tupleId);

        char *LocateTuple(const uint32_t &RID);

        [[nodiscard]] const Schema &getSchema() const;

        [[nodiscard]] std::string getTableName() const;

        [[nodiscard]] uint32_t getCntTuple() const;

        [[nodiscard]] uint32_t getTuplePerPage() const;

        [[nodiscard]] uint32_t getTupleMaxNum() const;


    private:
        Schema schema_;
        std::string table_name_;
        void *pages[TABLE_MAX_PAGE]{};
        DiskManager *diskManager_;
        uint32_t cnt_tuple_{0};
        uint32_t tuple_per_page_;//每页存放tuple数目
        uint32_t tuple_max_num_;//最多tuple数目
    };

} // antidb

#endif //ANTIDB_TABLE_H
