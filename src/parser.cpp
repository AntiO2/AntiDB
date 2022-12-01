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
            return parse_create(statement);
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
     * 分割空格
     * @param command
     * @param tokens
     */
    auto Parser::get_token(std::string &command, std::vector<std::string> &tokens) -> void {
        if (command.empty()) {
            tokens.clear();
            return;
        }
        command += " ";
        auto pos = command.find(' ');
        decltype(pos) start = 0;
        while (pos != std::string::npos) {
            auto token = command.substr(start, pos - start);
            if (!token.empty()) {
                tokens.emplace_back(token);
            }
            start = pos + 1;
            pos = command.find(' ', start);
        }
    }

    /**
     * 去掉语句最后的分号
     * @param command
     */
    auto Parser::get_rid_last_sem(std::string &command) -> void {
        if (command.empty()) {
            return;
        }
        auto pos = command.end();
        while (pos != command.cbegin()) {
            pos -= 1;
            if (*pos == ' ') {
                pos--;
                continue;
            }
            if (*pos == ';') {
                command = std::string(command.begin(), pos);
                return;
            }
            return;
        }
    }

    auto Parser::parse_create(Statement &statement) -> Create_Statement * {
        if (statement.tokens.size() < 2) {
            throw error_command("Argument Number isn't CORRECT");
        }
        std::transform(statement.tokens[1].begin(), statement.tokens[1].end(), statement.tokens[1].begin(), toupper);
        auto createStatement = std::make_shared<Create_Statement>(std::move(statement));
        if (createStatement->tokens[1] == "TABLE") {
            createStatement->name_ = createStatement->tokens[1];
            createStatement->createType_ = CREATE_TABLE;
            return nullptr;
        }
        if (createStatement->tokens[1] == "DATABASE") {
            if (createStatement->tokens.size() != 3) {
                throw error_command("Argument Number isn't CORRECT");
            }
            createStatement->name_ = createStatement->tokens[2];
            createStatement->createType_ = CREATE_DATABASE;
            return createStatement.get();
        }
    }

    auto Parser::parse_insert(Statement &statement) -> Statement * {
        return nullptr;
    }

    auto Parser::parse_select(Statement &statement) -> Statement * {
        return nullptr;
    }

    auto Parser::parse_use(Statement &statement) -> Statement * {
        return nullptr;
    }

    auto Parser::parse_delete(Statement &statement) -> Statement * {
        return nullptr;
    }

    auto Parser::parse_drop(Statement &statement) -> Statement * {
        return nullptr;
    }


} // antidb