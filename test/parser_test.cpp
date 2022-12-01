//
// Created by Anti on 2022/11/26.
//
#include "antidb/parser.h"
#include "gtest/gtest.h"
#include "vector"
#include "iostream"
/**
 * get_token测试
 */
TEST(PARSER_TEST, PARSE) {
    using std::cout;
    using std::endl;
    std::vector<std::string> tokens;
    antidb::Parser parse_instance;
    std::string sql("insert what");
    antidb::SQL_type sqlType;
    EXPECT_EQ(parse_instance.parse_sql(sql,sqlType), true);
    EXPECT_EQ(sqlType,antidb::INSERT);

    sql="  delete";
    EXPECT_EQ(parse_instance.parse_sql(sql,sqlType), true);
    EXPECT_EQ(sqlType,antidb::DELETE);
    sql="  create   ";
    EXPECT_EQ(parse_instance.parse_sql(sql,sqlType), true);
    EXPECT_EQ(sqlType,antidb::CREATE);


    sql="  select   ";
    EXPECT_EQ(parse_instance.parse_sql(sql,sqlType), true);
    EXPECT_EQ(sqlType,antidb::SELECT);

    sql="  antio2   ";
    EXPECT_EQ(parse_instance.parse_sql(sql,sqlType), false);
}
TEST(PARSER_TEST, NO_SEM)
{
    std::vector<std::string> tokens;
    antidb::Parser parse_instance;
    std::string sql(" insert;  ");
    antidb::SQL_type sqlType;
    EXPECT_EQ(parse_instance.parse_sql(sql,sqlType),true);
    EXPECT_EQ(sqlType,antidb::INSERT);
}