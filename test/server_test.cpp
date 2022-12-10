//
// Created by Anti on 2022/12/9.
//
#include "gtest/gtest.h"
#include "antidb/antidb.h"

namespace antidb {
    TEST(SERVER, INIT) {
        try {
            Server::ExecuteOneSQL("drop database antio2", nullptr);
        }
        catch (std::exception &e) {}
    }

    TEST(SERVER, CREATE) {
        try {
            std::string sql("Create database antio2");
            Server::ExecuteOneSQL(std::move(sql), nullptr);
        }
        catch (std::exception &e) {
        }
        EXPECT_EQ(std::filesystem::exists(DATA_PATH + "antio2"), true);
    }

    TEST(SERVER, USE) {
        {
            std::string sql("use antio2");
            std::unique_ptr<Database> db;
            Server::ExecuteOneSQL(std::move(sql), &db);
            EXPECT_NE(db, nullptr);
        }
        {
            std::string sql("use antio3");
            std::unique_ptr<Database> db;
            EXPECT_ANY_THROW(Server::ExecuteOneSQL(std::move(sql), &db));
        }
    }

    TEST(SERVER, DROP_DB) {
        {
            std::string sql("Create database antio2");
            try {
                Server::ExecuteOneSQL(std::move(sql), nullptr);
            }
            catch (std::exception &e) {
            }
        }
        {
            /**
             * 删除不存在的数据库
             *
             */
            std::string sql("drop database antio3");
            EXPECT_ANY_THROW(Server::ExecuteOneSQL(std::move(sql), nullptr));
        }
        {
            /**
             * 不能删除正在使用的数据库
             */
            std::string u_sql("use antio2");
            std::unique_ptr<Database> db;
            Server::ExecuteOneSQL(std::move(u_sql), &db);
            std::string sql("drop database antio2");
            EXPECT_ANY_THROW(Server::ExecuteOneSQL(std::move(sql), &db));
        }
        {
            std::string sql("drop database antio2");
            Server::ExecuteOneSQL(std::move(sql), nullptr);
            EXPECT_EQ(std::filesystem::exists(DATA_PATH + "antio2"), false);
        }
    }

    TEST(SERVER, CREATE_TABLE) {
        /**
         * 初始化数据库
         */
        {
            std::string sql("Create database antio2");
            try {
                Server::ExecuteOneSQL(std::move(sql), nullptr);
            }
            catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
        std::string sql_u("use antio2");
        std::unique_ptr<Database> db;
        Server::ExecuteOneSQL(std::move(sql_u), &db);
        ASSERT_NE(db, nullptr);
        {
            std::string sql = "create table antio2(id int,age int,name string);";
            auto stmt = Statement(sql);
            Server::ExecuteOneSQL(std::move(sql), &db);
        }
        {
            std::string sql = "create table antio2(id int,age int,name string);";
            auto stmt = Statement(sql);
            EXPECT_ANY_THROW(Server::ExecuteOneSQL(std::move(sql), &db));
        }
    }
    /**
     * 这个需要执行前面一个测试:create table
     * 生成了表之后才能进行正常测试
     */
    TEST(SERVER, DROP_TABLE) {
        std::string sql_u("use antio2");
        std::unique_ptr<Database> db;
        Server::ExecuteOneSQL(std::move(sql_u), &db);
        {
            std::string sql = "drop table antio3";
            auto stmt = Statement(sql);
            EXPECT_ANY_THROW(Server::ExecuteOneSQL(std::move(sql), &db));
        }
        {
            std::string sql = "drop table antio2";
            auto stmt = Statement(sql);
            EXPECT_EQ(db->find("antio2"), true);
            Server::ExecuteOneSQL(std::move(sql), &db);
            EXPECT_EQ(db->find("antio2"), false);
        }
        {
            std::string sql = "drop table antio2";
            auto stmt = Statement(sql);
            EXPECT_ANY_THROW(Server::ExecuteOneSQL(std::move(sql), &db));
        }
    }

    TEST(DML, INSERT_ICHI) {
        /**********************
         * 初始化测试条件
         *
         *
         *
         */
        {
            std::string sql("Create database antio2");
            try {
                Server::ExecuteOneSQL(std::move(sql), nullptr);
            }
            catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
        std::string sql_u("use antio2");
        std::unique_ptr<Database> db;
        Server::ExecuteOneSQL(std::move(sql_u), &db);
        /**
         *
         *******************************************************/
        {

            ASSERT_NE(db, nullptr);
            {
                try {
                    std::string sql = "create table antio2(id int,age int,name string);";
                    Server::ExecuteOneSQL(std::move(sql), &db);
                }
                catch (std::exception &e) {};
            }
            for (int i = 1; i <= 3; i++) {
                Server::ExecuteOneSQL("insert antio2 values(11111,22222,\"anti\")", &db);
            }
        }
    }
    /**
     * 这是上一个测试的延申，测试数据恢复功能
     */
    TEST(DML, INSERT_ICHI_2) {
        /**********************
         * 初始化测试条件
         *
         *
         *
         */
        {
            std::string sql("Create database antio2");
            try {
                Server::ExecuteOneSQL(std::move(sql), nullptr);
            }
            catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
        std::string sql_u("use antio2");
        std::unique_ptr<Database> db;
        Server::ExecuteOneSQL(std::move(sql_u), &db);
        /**
         *
         *******************************************************/
        {

            ASSERT_NE(db, nullptr);
            {
                try {
                    std::string sql = "create table antio2(id int,age int,name string);";
                    Server::ExecuteOneSQL(std::move(sql), &db);
                }
                catch (std::exception &e) {};
            }
            for (int i = 1; i <= 3; i++) {
                Server::ExecuteOneSQL("insert antio2 values(11111,22222,\"anti\")", &db);
            }
        }
    }

    TEST(DML, INSERT_NI) {
        /**********************
         * 初始化测试条件
         *
         *
         *
         */
        {
            std::string sql("Create database antio2");
            try {
                Server::ExecuteOneSQL(std::move(sql), nullptr);
            }
            catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
        std::string sql_u("use antio2");
        std::unique_ptr<Database> db;
        Server::ExecuteOneSQL(std::move(sql_u), &db);
        /**
         *
         *******************************************************/
        {

            ASSERT_NE(db, nullptr);
            {
                try {
                    std::string sql = "create table antio3 (id int primary,age int,name string);";
                    Server::ExecuteOneSQL(std::move(sql), &db);
                }
                catch (std::exception &e) {};
            }
            for (int i = 1; i <= 3; i++) {
                Server::ExecuteOneSQL("insert antio3 values(" + std::to_string(i) + ",22222,\"anti\")", &db);
            }
        }
    }

    TEST(DML, INSERT_NI_2) {
        /**********************
         * 初始化测试条件
         *
         *
         *
         */
        {
            std::string sql("Create database antio2");
            try {
                Server::ExecuteOneSQL(std::move(sql), nullptr);
            }
            catch (std::exception &e) {
            }
        }
        std::string sql_u("use antio2");
        std::unique_ptr<Database> db;
        Server::ExecuteOneSQL(std::move(sql_u), &db);
        /**
         *
         *******************************************************/
        {

            ASSERT_NE(db, nullptr);
            {
                try {
                    Server::ExecuteOneSQL("drop table antio3", &db);
                    std::string sql = "create table antio3 (id int primary,age int,name string);";
                    Server::ExecuteOneSQL(std::move(sql), &db);
                }
                catch (std::exception &e) {};
            }
            for (int i = 1; i <= 3; i++) {
                Server::ExecuteOneSQL("insert antio3 values(" + std::to_string(i) + ",22222,\"anti\")", &db);
                EXPECT_ANY_THROW(
                        Server::ExecuteOneSQL("insert antio3 values(" + std::to_string(i) + ",22222,\"anti\")", &db));
            }
        }
    }
    /**
     * 这个测试需要之前的创建表并插入数据！！！
     */
    TEST(DML, SELECT_NOKEY) {
        std::string sql_u("use antio2");
        std::unique_ptr<Database> db;
        Server::ExecuteOneSQL(std::move(sql_u), &db);
        Server::ExecuteOneSQL("select * from antio2", &db);
        Server::ExecuteOneSQL("select * from antio2 where id = 11111", &db);
        Server::ExecuteOneSQL("select * from antio2 where id = 0", &db);
        Server::ExecuteOneSQL("select age from antio2 where age=22222", &db);
        Server::ExecuteOneSQL("select * from antio3", &db);
        Server::ExecuteOneSQL("select * from antio3 where id = 1", &db);
        Server::ExecuteOneSQL("select age from antio3 where id = 2", &db);
        Server::ExecuteOneSQL("select name from antio3 where id =3", &db);
    }

    TEST(DML, DELETE_TUPLE) {
        std::string sql_u("use antio2");
        std::unique_ptr<Database> db;
        Server::ExecuteOneSQL(std::move(sql_u), &db);
        try {
            Server::ExecuteOneSQL("drop table antio3", &db);
            std::string sql = "create table antio3 (id int primary,age int,name string);";
            Server::ExecuteOneSQL(std::move(sql), &db);
            Server::ExecuteOneSQL("drop table antio2", &db);
            Server::ExecuteOneSQL("create table antio2(id int,age int,name string);", &db);

        }
        catch (std::exception &e) {};

        {
            /**
             * 插入初始数据
             */
            for (int i = 1; i <= 3; i++) {
                Server::ExecuteOneSQL("insert antio2 values(11111,22222,\"anti\")", &db);
            }
            for (int i = 1; i <= 3; i++) {
                Server::ExecuteOneSQL("insert antio3 values(" + std::to_string(i) + ",22222,\"anti\")", &db);
            }
        }

        Server::ExecuteOneSQL("select * from antio2", &db);
        Server::ExecuteOneSQL("delete antio2 where id<11122", &db);
        Server::ExecuteOneSQL("select * from antio3", &db);
        Server::ExecuteOneSQL("delete antio3 where id = 1", &db);
        Server::ExecuteOneSQL("select * from antio3", &db);
        Server::ExecuteOneSQL("delete antio2", &db);
        Server::ExecuteOneSQL("delete antio3", &db);
        Server::ExecuteOneSQL("select * from antio3", &db);
    }

}
