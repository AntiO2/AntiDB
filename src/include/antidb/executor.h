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
#include "antidb/parser.h"
namespace antidb {

    class AbstractExecutor {
    };

    class CreateExecutor : AbstractExecutor {
    public:
        static auto Create(Create_Statement *createStatement, std::unique_ptr<Database> *db) -> void;

        static auto CreateDataBase(const std::string &database_name) -> bool;

        static auto CreateTable(const Create_Statement &createStatement, std::unique_ptr<Database> *db) -> Table *;
    };

    class UseExecutor : AbstractExecutor {
    public:
        [[nodiscard]]static auto UseDataBase(const std::string &database_name) -> std::unique_ptr<Database>;
    };

    class InsertExecutor : AbstractExecutor {
    public:
        static auto InsertByStmt(Insert_Statement *i_stmt, std::unique_ptr<Database> *db) -> void;

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
        /**
         * select,并且打印出结果
         * @return
         */
        static auto LazySelect(Select_Statement *s_stmt, std::unique_ptr<Database> *db) -> void;

        static auto Projection(std::vector<std::vector<Value>> &values, uint32_t col_id) -> void;

        //static auto OutputProjection(Select_Statement *s_stmt,std::vector<std::vector<Value>> &values)->void ;
        static auto Select(Select_Statement *s_stmt, std::unique_ptr<Database> *db) -> std::vector<std::vector<Value>>;
        /**
         * 根据tid将tuple读入，已经放弃使用
         * @param t
         * @param tid
         * @param tuple
         * @return
         */
//        static auto ReadTuple(Table *t, tuple_id_t tid,Tuple*tuple) -> bool;
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

    class DeleteExecutor : AbstractExecutor {
    public:
        static auto DeleteByStmt(Delete_Statement *deleteStatement, std::unique_ptr<Database> *db) -> void;
    };

    class PrintExecutor : AbstractExecutor {
    public:
        static auto PrintValue(Select_Statement *s_stmt, std::vector<std::vector<Value>> &&values_s) -> void;
    };

} // antidb

#endif //ANTIDB_EXECUTOR_H
