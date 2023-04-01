#include "chatlog.hpp"

#include "response.hpp"

#include <fcntl.h>
#include <fstream>
#include <mutex>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

chatlog::chatlog_t chatlog::chatlog;

void chatlog::chatlog_t::init()
{
    char *cwd, chatlogdir[1000];

    cwd = getcwd(nullptr, 0);
    if (cwd == nullptr) {
        fprintf(stderr, "Log file failed to initialize");
        exit(1);
    }

    sprintf(chatlogdir, "%s/chatlog", cwd);
    mkdir(chatlogdir, 0777); // all permissions
    strcat(chatlogdir, "/chatlog.txt");
    chatlog.open(chatlogdir, std::fstream::app);
    filepath = chatlogdir;

    free(cwd);
}

chatlog::chatlog_t::chatlog_t()
{
    init();
}

chatlog::chatlog_t::~chatlog_t()
{
    if (chatlog.is_open())
        chatlog.close();
}

void chatlog::chatlog_t::add(const std::string &msg)
{
    std::string msg_to_save = msg;
    msg_to_save.append(chatlog_delim); // append delimiter, \n won't work
    std::lock_guard<std::mutex> lk(write_mutex);
    chatlog << msg_to_save;
    chatlog.flush();
}