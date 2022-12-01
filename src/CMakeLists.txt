include_directories(include)
add_library(parser
        STATIC
        parser.cpp)

add_library(storage
        STATIC
        disk_manager.cpp
        )

add_library(executor
        STATIC
        executor.cpp)