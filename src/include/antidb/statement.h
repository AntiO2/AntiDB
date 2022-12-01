//
// Created by Anti on 2022/11/29.
//

#ifndef ANTIDB_STATEMENT_H
#define ANTIDB_STATEMENT_H

#include <string>
#include <utility>
#include <vector>

#include "antidb/config.h"

namespace antidb {

    class Statement {
    public:
        explicit Statement(std::string commandline) : commandline_(std::move(commandline)) {};
        std::string commandline_;
        std::vector<std::string> tokens;
        SQL_type sqlType_{EXIT};
    };

    class Create_Statement : public Statement {
    private:

    public:
        explicit Create_Statement(Statement &&statement) : Statement(std::move(statement)) {}

        std::string name_;
        CREATE_TYPE createType_{CREATE_DATABASE};

    };
} // antidb


#endif //ANTIDB_STATEMENT_H
