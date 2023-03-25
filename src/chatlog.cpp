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

/* Breakdown of the method for this
*
* msg.size() will be 1000+ characters
* 1) find the position of the first message delimiter after msg.size()
* 2) then copy that string into a new string
* 3) tokenize the string and extract each individual msg into a vector<string>
* 4) Send all the individual messages to the client that just joined
*
*/
static void format_history_to_send(const int index, std::string &msg)
{
    auto pos         = msg.find(chatlog::chatlog_delim, 0);
    if (pos == std::string::npos)
        return;
    
    std::string text = msg.substr(pos + chatlog::chatlog_delim.size(),
                                  msg.size() - pos - chatlog::chatlog_delim.size());

    pos = 0;
    std::string token;
    std::vector<std::string> msgs;
    while ((pos = text.find(chatlog::chatlog_delim)) != std::string::npos) {
        token = text.substr(0, pos);
        msgs.push_back(token);
        text.erase(0, pos + chatlog::chatlog_delim.length());
    }

    for (const auto &msg: msgs)
        response::send(index, msg, false);
}

// This gets the LAST len bytes from the chatlog file
static void get_chatlog_text(char *buf, const int len)
{
    int fd;
    ssize_t result;
    struct stat sb;

    std::lock_guard<std::mutex> lk(chatlog::chatlog.write_mutex);
    fd = open(chatlog::chatlog.filepath.c_str(), O_RDONLY);
    fstat(fd, &sb);
    if (sb.st_size >= len)
        result = pread(fd, buf, len, sb.st_size - len); // TODO: put this in a while loop
    else
        result = pread(fd, buf, sb.st_size, 0); // TODO: put this in a while loop

    if (result)
        return;
}

void chatlog::chatlog_t::init()
{
    char *cwd, chatlogdir[1000];


    cwd = getcwd(nullptr, 0);
    if (cwd == nullptr) {
        free(cwd);
        return;
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

void chatlog::send_history(const int index)
{
    char buf[10000];
    std::string text;

    if (!chatlog::chatlog.chatlog.is_open()) {
        printf("Error, in send_chatlog_history(), chatlog is closed");
        return;
    }

    get_chatlog_text(buf, sizeof(buf));
    text = buf;
    format_history_to_send(index, text);

}