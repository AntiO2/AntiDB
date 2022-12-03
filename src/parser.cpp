//
// Created by Anti on 2022/11/25.
//
#define DEBUG 0
#if DEBUG
#include "iostream"
using std::cout;
using std::endl;
#endif

#include "antidb/parser.h"


namespace antidb {
    char TOKEN[] = {
            ',',
            '(',
            ')',
            ';'
    };
    char SPACE[] = {
            '\r',
            '\n',
            ' '
    };

    /**
     * 通过string解析sql，已废弃
     * @param sql_command
     * @param sqlType
     * @return
     */
    auto Parser::parse_sql(std::string &sql_command, SQL_type &sqlType) -> bool {
        std::vector<std::string> tokens;
        get_rid_last_sem(sql_command);
        get_token(sql_command, tokens);
        std::string first_token = tokens[0];
        if (first_token == "insert") {
            sqlType = INSERT;
            return true;
        }
        if (first_token == "select") {
            sqlType = SELECT;
            return true;
        }
        if (first_token == "create") {
            sqlType = CREATE;
            return true;
        }
        if (first_token == "delete") {
            sqlType = DELETE;
            return true;
        }
        if (first_token == "exit") {
            sqlType = EXIT;
            return true;
        }
        return false;
    }

    /**
     * TODO(Anti) 用的时候记得捕获异常
     * 通过Statement解析sql语句
     * @param statement
     * @return
     */
    auto Parser::parse_sql(Statement &statement) -> Statement * {
        get_rid_last_sem(statement.commandline_);
        get_token(statement.commandline_, statement.tokens);
        std::transform(statement.tokens[0].begin(),
                       statement.tokens[0].end(),
                       statement.tokens[0].begin(),
                       tolower);
        auto first_token = statement.tokens[0];
        if (first_token == "insert") {
            statement.sqlType_ = INSERT;
            return parse_insert(statement);
        }
        if (first_token == "select") {
            statement.sqlType_ = SELECT;
            return parse_select(statement);
        }
        if (first_token == "create") {
            statement.sqlType_ = CREATE;
            //return parse_create(statement);
            auto res = parse_create(statement);
            return res;
        }
        if (first_token == "delete") {
            statement.sqlType_ = DELETE;
            return parse_delete(statement);
        }
        if (first_token == "drop") {
            statement.sqlType_ = DROP;
            return parse_drop(statement);
        }
        if (first_token == "use") {
            statement.sqlType_ = USE;
            return parse_use(statement);
        }
        if (first_token == "exit") {
            statement.sqlType_ = EXIT;
            return &statement;
        }
        return nullptr;
    }

    /**
     * NOT 分割空格
     * DONE(Anti) 分割出括号，逗号
     * @param command
     * @param tokens
     */
    auto Parser::get_token(std::string &command, std::vector<std::string> &tokens) -> void {
        if (command.empty()) {
            tokens.clear();
            return;
        }
        command += " ";
//        auto pos = command.find(' ');
//        decltype(pos) start = 0;
//        while (pos != std::string::npos) {
//            auto token = command.substr(start, pos - start);
//            if (!token.empty()) {
//                tokens.emplace_back(token);
//            }
//            start = pos + 1;
//            pos = command.find(' ', start);
//        }
        /**
         * 扫描一遍，获取token，如果是空格 跳过，单词或者指定标志符则加入tokens
         *
         *
         */
        auto point = -1;
        for (auto i = 0; i < command.length(); i++) {
            char c = command[i];
            /**
             * 如果是空格，检查前面是否有单词
             */
            if (is_space(c)) {
                if (point != -1) {
                    tokens.push_back(command.substr(point, i - point));
                    point = -1;
                }
            } else {
                /**
                 * 如果是token
                 */
                if (is_token(c)) {
                    if (point != -1) {
                        tokens.push_back(command.substr(point, i - point));
                        point = -1;
                    }
                    tokens.emplace_back(1, c);
                } else {
                    /**
                     * 如果之前没有指向单词首字母，将point放在当前位置
                     */
                    if (point == -1) {
                        point = i;
                    }
                }
            }
        }
    }

    /**
     * FIXME 可能有错
     * 去掉语句最后的分号
     * @param command
     */
    auto Parser::get_rid_last_sem(std::string &command) -> void {
        if (command.empty()) {
            return;
        }
        auto pos = command.end();
        pos--;
        while (pos != command.cbegin()) {
            pos--;
            if (*pos == ';') {
                command = std::string(command.begin(), pos);
                return;
            }
        }
    }

    auto Parser::parse_create(Statement &statement) -> Create_Statement * {
        if (statement.tokens.size() < 3) {
            throw error_command("Argument Number isn't CORRECT");
        }
        std::transform(statement.tokens[1].begin(), statement.tokens[1].end(), statement.tokens[1].begin(), toupper);
        auto createStatement = new Create_Statement(std::move(statement));
        if (createStatement->tokens[1] == "TABLE") {
            /**
             * create table table_name (  ); 至少有五个单词
             */
            if (createStatement->tokens.size() < 5) {
                throw error_command("Invalid Create Statement");
            }
            createStatement->name_ = createStatement->tokens[2];// table name
            createStatement->createType_ = CREATE_TABLE;
            /**
             * TODO(AntiO2) 分词器 加入括号解析
             * 解析列信息
             * 创建对应schema
             *
             */
            if (createStatement->tokens[3] != "(") {
                throw error_command("No '(' Found");
            }
            if (*createStatement->tokens.rbegin() != ")") {
                throw error_command("Create Table statement should end with ')'");
            }
            Column new_col = *new Column();
            int cnt = 0;
            /**
             * CHECK(AntiO2) not right
             */
            for (int i = 4; i < createStatement->tokens.size(); i++) {

                auto token = createStatement->tokens[i];
                if (token == ")") {
                    if (cnt != 0) {
                        createStatement->schema_.AddCols(std::move(new_col));
                    }
                    break;
                }
                switch (cnt) {
                    case 0://处理列名阶段
                        new_col.col_name_ = token;
                        cnt++;

                        break;
                    case 1://处理类型阶段
                        if (token == "int") {
                            new_col.type_ = INT;
                            new_col.col_size_ = 4;

                        } else if (token == "string") {
                            new_col.type_ = STRING;
                            new_col.col_size_ = MAX_STRING_SIZE;
                        } else {
                            throw error_command("Invalid type named " + token);
                        }
                        cnt++;
                        break;
                    case 2://处理主键，或者结束一个列的定义
                        if (token == ",") {
                            createStatement->schema_.AddCols(std::move(new_col));
                            new_col = *new Column();
                            cnt = 0;
                            break;
                        }
                        if (token == "primary") {
                            if (createStatement->schema_.Has_Primary()) {
                                throw error_command("Two Primary Keys? It is not allowed by AntiDB");
                            }
                            createStatement->schema_.Set_Primary(true);
                            new_col.is_primary_ = true;
                            break;
                        }
                    default:
                        throw error_command("Invalid creat table,please check it");
                }
            }
            return createStatement;
        }
        if (createStatement->tokens[1] == "DATABASE") {
            if (createStatement->tokens.size() != 3) {
                throw error_command("Argument Number isn't CORRECT");
            }
            createStatement->name_ = createStatement->tokens[2];
            createStatement->createType_ = CREATE_DATABASE;
            return createStatement;
        }
        return nullptr;
    }

    auto Parser::parse_insert(Statement &statement) -> Statement * {
        return nullptr;
    }

    auto Parser::parse_select(Statement &statement) -> Statement * {
        return nullptr;
    }

    auto Parser::parse_use(Statement &statement) -> Use_Statement * {
        auto u_stmt = new Use_Statement(std::move(statement));
        /**
         * 比如 use antidb,只需要俩token，多了就错了
         */
        if (u_stmt->tokens.size() != 2) {
            throw error_command("Argument isn't correct! e.g. Use <dbname>");
        }
        if (u_stmt->tokens[1].empty()) {
            throw error_command("No DB name ! e.g. Use <dbname>");
        }
        u_stmt->db_name_ = u_stmt->tokens[1];
        return u_stmt;
    }

    auto Parser::parse_delete(Statement &statement) -> Statement * {
        return nullptr;
    }

    auto Parser::parse_drop(Statement &statement) -> Statement * {
        return nullptr;
    }

    auto Parser::is_token(char &c) -> bool {
        for (auto token: TOKEN) {
            if (c == token) {
                return true;
            }
        }
        return false;
    }

    auto Parser::is_space(char &c) -> bool {
        for (auto space: SPACE) {
            if (c == space) {
                return true;
            }
        }
        return false;
    }

} // antidb