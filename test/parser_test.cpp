//
// Created by Anti on 2022/11/26.
//
#include "antidb/parser.h"
#include "gtest/gtest.h"
#include "antidb/statement.h"
#include "vector"
#include "iostream"

namespace antidb {
    /**
 * get_token测试
 */
    TEST(PARSER_TEST, DISABLED_PARSE) {
        using std::cout;
        using std::endl;
        std::vector<std::string> tokens;
        antidb::Parser parse_instance;
        std::string sql("insert what");
        antidb::SQL_type sqlType;
        EXPECT_EQ(parse_instance.parse_sql(sql, sqlType), true);
        EXPECT_EQ(sqlType, antidb::INSERT);

        sql = "  delete";
        EXPECT_EQ(parse_instance.parse_sql(sql, sqlType), true);
        EXPECT_EQ(sqlType, antidb::DELETE);
        sql = "  create   ";
        EXPECT_EQ(parse_instance.parse_sql(sql, sqlType), true);
        EXPECT_EQ(sqlType, antidb::CREATE);


        sql = "  select   ";
        EXPECT_EQ(parse_instance.parse_sql(sql, sqlType), true);
        EXPECT_EQ(sqlType, antidb::SELECT);

        sql = "  antio2   ";
        EXPECT_EQ(parse_instance.parse_sql(sql, sqlType), false);
    }

    TEST(PARSER_TEST, DISABLED_NO_SEM) {
        std::vector<std::string> tokens;
        antidb::Parser parse_instance;
        std::string sql(" insert;  ");
        antidb::SQL_type sqlType;
        EXPECT_EQ(parse_instance.parse_sql(sql, sqlType), true);
        EXPECT_EQ(sqlType, antidb::INSERT);
    }

    TEST(PARSER_TEST, TOKEN_v2) {
        std::vector<std::string> tokens;
        antidb::Parser parse_instance;
        std::string sql(" create table new_table(column int primary,email string ,anti int); ");
        antidb::SQL_type sqlType;
        antidb::Parser::get_token(sql, tokens);
//        for(const auto& token:tokens)
//        {
//            std::cout<<token<<std::endl;
//        }
    }

    TEST(PARSER_TEST, CREATE_TABLE) {
        std::string sql(" create table new_table (column int primary,email string ,anti int); ");
        auto stmt = Statement(sql);
        auto c_stmt = (Create_Statement *) antidb::Parser::parse_sql(stmt);
        EXPECT_EQ(1, 1);
    }

    TEST(PARSER_TEST, CREATE_TABLE_2) {
        std::string sql("create table anti_table(id int,age int,name string);");
        auto stmt = Statement(sql);
        auto c_stmt = (Create_Statement *) antidb::Parser::parse_sql(stmt);
        EXPECT_EQ(1, 1);
    }

}
