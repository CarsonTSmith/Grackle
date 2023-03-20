#pragma once

#include <fstream>
#include <mutex>
#include <string>

namespace chatlog {

    const std::string chatlog_delim = "!!:\n\n";

    struct chatlog_t {
        std::fstream chatlog;
        std::mutex   write_mutex;

        chatlog_t();
        ~chatlog_t();

        void add(const std::string &msg);
    };

    extern chatlog_t chatlog; // the global chat log
}