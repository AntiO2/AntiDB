//
// Created by Anti on 2022/11/29.
//

#ifndef ANTIDB_TUPLE_H
#define ANTIDB_TUPLE_H

#include <vector>
#include "antidb/value.h"

namespace antidb {

    class Tuple {
    public:
        Tuple();

    private:
        std::vector<Value> values;
    };
} // antidb

#endif //ANTIDB_TUPLE_H
