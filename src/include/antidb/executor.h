//
// Created by Anti on 2022/11/29.
//

#ifndef ANTIDB_EXECUTOR_H
#define ANTIDB_EXECUTOR_H

#include <string>
#include <memory>
#include "antidb/config.h"
#include "antidb/table.h"
#include "antidb/statement.h"
#include "antidb/tuple.h"
#include "antidb/database.h"
namespace antidb {

    class AbstractExecutor {
    };

    class CreateExecutor : AbstractExecutor {
    public:
        explicit CreateExecutor(Create_Statement &createStatement);

        static auto CreateDataBase(const std::string &database_name) -> bool;

        static auto CreateTable(const Create_Statement &createStatement, Database &database) -> Table *;
    };

    class UseExecutor : AbstractExecutor {
    public:
        [[nodiscard]]static auto UseDataBase(const std::string &database_name) -> std::unique_ptr<Database>;
    };

    class InsertExecutor : AbstractExecutor {
    public:
        /**
         * 在指定位置写入tuple数据
         * @param tuple
         * @param
         * @return
         */
        static auto WriteTuple(Tuple &tuple, Table &table) -> void;

        static auto WriteTuple(Tuple &tuple, Table *table) -> void;
    };

    class SelectExecutor : AbstractExecutor {
    public:

        static auto ReadTuple(Table &t, tuple_id_t tid);
    };

    class DropExecutor : AbstractExecutor {
    public:
        static auto DropTable(const std::string &table_name, std::unique_ptr<Database> *db) -> void;

        /**
         * TODO(AntiO2) 记得不允许删除正在使用的db
         * @param db_name
         */
        static auto DropDatabase(const std::string &db_name) -> void;
    };
} // antidb

#endif //ANTIDB_EXECUTOR_H
