#include "chatlog.hpp"

#include <core/response.hpp>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

chatlog::chatlog_t chatlog::chatlog;

void chatlog::chatlog_t::init()
{
    char *cwd, chatlogdir[1000] = {0};

    cwd = getcwd(nullptr, 0);
    if (cwd == nullptr) {
        fprintf(stderr, "Log file failed to initialize");
        exit(1);
    }

    sprintf(chatlogdir, "%s/%s", cwd, chatlog::chatlog_dir.c_str());
    mkdir(chatlogdir, 0777); // all permissions
    strcat(chatlogdir, "/");
    strcat(chatlogdir, chatlog::chatlog_file.c_str());
    m_chatlog.open(chatlogdir, std::fstream::app);
    m_filepath = chatlogdir;

    free(cwd);
}

chatlog::chatlog_t::chatlog_t()
{
    init();
}

chatlog::chatlog_t::~chatlog_t()
{
    if (m_chatlog.is_open())
        m_chatlog.close();
}

void chatlog::chatlog_t::add(const std::string &msg)
{
    std::string msg_to_save = msg;
    msg_to_save.append(chatlog_delim); // append delimiter, \n won't work
    std::lock_guard<std::mutex> lk(m_write_mutex);
    m_chatlog << msg_to_save;
    m_chatlog.flush();
}