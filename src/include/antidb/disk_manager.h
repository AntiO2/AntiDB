//
// Created by Anti on 2022/11/28.
//

#ifndef ANTIDB_DISKMANAGER_H
#define ANTIDB_DISKMANAGER_H

#include <string>
#include <fstream>
#include <sys/stat.h>
#include "antidb/config.h"

namespace antidb {

    class DiskManager {
    public:
        explicit DiskManager(const std::string &file_name);

        DiskManager() = default;

        virtual ~DiskManager() = default;

        virtual void ShutDown();

        virtual void WritePage(page_id_t page_id, const char *page_data);

        virtual void ReadPage(page_id_t page_id, char *page_data);

    protected:
        static auto GetFileSize(const std::string &file_name) -> int;

        std::fstream file_io_;
        std::string file_name_;
        int num_flushes_{0};
        int num_writes_{0};

    };

} // antidb

#endif //ANTIDB_DISKMANAGER_H
