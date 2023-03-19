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
        ~chatlog_t()
        {
            if (chatlog.is_open())
                chatlog.close();
        }

        void add(const std::string &msg)
        {
            std::string msg_to_save = msg;
            msg_to_save.append(chatlog_delim); // append delimiter, \n won't work
            std::lock_guard<std::mutex> lk(write_mutex);
            chatlog << msg_to_save << std::endl; // endl flushes to disk
        }
    };

    extern chatlog_t chatlog; // the global chat log
}