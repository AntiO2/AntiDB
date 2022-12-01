//
// Created by Anti on 2022/11/29.
//

#ifndef ANTIDB_EXCEPTION_H
#define ANTIDB_EXCEPTION_H

#include <exception>
#include <stdexcept>

namespace antidb {
    class error_file : public std::runtime_error {
    public:
        explicit error_file(const std::string &error) : std::runtime_error(error) {};

    };

    class error_command : public std::runtime_error { ;
    public:
        explicit error_command(const std::string &error) : std::runtime_error(error) {}
    };
}

#endif //ANTIDB_EXCEPTION_H
