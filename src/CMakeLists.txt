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

add_library(server
        STATIC
        server.cpp)

target_link_libraries(
        server
        SHARED
        parser
        executor
)