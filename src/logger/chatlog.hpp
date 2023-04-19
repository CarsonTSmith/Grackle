#pragma once

#include <fstream>
#include <mutex>
#include <string>

namespace chatlog {

static const std::string chatlog_dir   = "chatlog";
static const std::string chatlog_file  = "chatlog.txt";
static const std::string chatlog_delim = "!!:\n\n";

struct chatlog_t {
    std::fstream m_chatlog;
    std::mutex   m_write_mutex;
    std::string  m_filepath;

    chatlog_t();
    ~chatlog_t();

    void add(const std::string &msg);

private:
    void init();
};

extern chatlog_t chatlog; // the global chat log

}