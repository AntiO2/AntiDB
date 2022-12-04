//
// Created by Anti on 2022/12/1.
//
#include "iostream"
#include "gtest/gtest.h"
#include "antidb/tuple.h"
#include "antidb/value.h"
#include "antidb/config.h"
#include "antidb/table.h"
#include "antidb/parser.h"
#include "antidb/statement.h"
#include "string"
#include "antidb/database.h"
namespace antidb {
    using std::cout;
    using std::endl;
    TEST(STORAGE_TEST, DISABLED_VALUE) {
        Value v1 = Value(INT, 1);
        char data[MAX_STRING_SIZE];
        v1.GetValue(data);
        EXPECT_EQ(v1.GetSize(), 4);
        EXPECT_EQ(data[0], 1);
        char str[] = "AntiO2";
        Value v2 = Value(STRING, str, sizeof(str));
        EXPECT_EQ(v2.GetSize(), MAX_STRING_SIZE);
        v2.GetValue(data);
        std::string str_ = data;
        EXPECT_EQ(str_, "AntiO2");
    }

    TEST(STORAGE_TEST, DISABLED_PAGE_RW) {
        std::string sql = "create table anti_table(id int,age int,name string);";
        auto stmt = Statement(sql);
        auto c_stmt = (Create_Statement *) Parser::parse_sql(stmt);
        EXPECT_EQ(c_stmt->name_, "anti_table");
        EXPECT_EQ(c_stmt->schema_.GetSize(), 264);
        auto table = Table(c_stmt->schema_);
        std::vector<Value> v;
        v.emplace_back(INT, 2003);
        v.emplace_back(INT, 814);
        char str[] = "AntiO2";
        v.emplace_back(STRING, str, strlen(str));
        auto t = Tuple(v, c_stmt->schema_);
        for (auto i = 0; i < 100; i++) {
            table.WriteTuple(t);
        }
        for (auto i = 0; i < 10; i++) {
            auto new_t = Tuple(c_stmt->schema_.GetSize());
            table.ReadTuple(new_t, i);
            std::vector<Value> vs;
            new_t.deserialize(vs, c_stmt->schema_);
            EXPECT_EQ(vs[0].GetInt(), 2003);
            EXPECT_EQ(vs[1].GetInt(), 814);
            std::cout << strlen(vs[2].GetSTRING()) << " " << vs[2].GetSTRING() << std::endl;
        }
    }

    TEST(STORAGE_TEST, DATABASE) {
        Database db1("antio2");
        Database db2("antio2");
    }

}