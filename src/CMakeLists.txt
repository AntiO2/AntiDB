add_library(parser
        STATIC
        parser.cpp)

add_library(storage
        STATIC
        disk_manager.cpp
        table.cpp)

add_library(executor
        STATIC
        executor.cpp)