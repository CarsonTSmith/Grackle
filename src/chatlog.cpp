#include "chatlog.hpp"

#include <fstream>
#include <mutex>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

chatlog::chatlog_t chatlog::chatlog;

static void init_chatlog(std::fstream &chatlog)
{
    char cwd[256], chatlogdir[300];

    getcwd(cwd, sizeof(cwd));
    if (cwd == nullptr)
        return; // error

    sprintf(chatlogdir, "%s/chatlog", cwd);
    mkdir(chatlogdir, 0777); // all permissions
    strcat(chatlogdir, "/chatlog.txt");
    chatlog.open(chatlogdir, std::fstream::app);
}

chatlog::chatlog_t::chatlog_t()
{
    init_chatlog(chatlog);
}