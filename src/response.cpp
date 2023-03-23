#include "response.hpp"

#include "chatlog.hpp"
#include "clients.hpp"

#include <mutex>
#include <string>
#include <unistd.h>

std::mutex response::write_mutex;

void response::send_to_all(const int index)
{
    auto &clients = clients::clients_s::get_instance();
    for (int i = 0; (size_t)i < clients.p_clients.size(); ++i) {
        if (clients.p_clients[i].fd == -1)
            continue;

        response::send(i, clients.c_clients[index].header, true);
    }
}

void response::echo(const int index)
{
    auto &clients = clients::clients_s::get_instance();
    response::send(index, clients.c_clients[index].header, true);
}

void response::send(const int index, const std::string &msg, const bool record_msg)
{
    size_t result = 0, total = 0;

    if (msg.size() == 0)
        return;

    auto &clients = clients::clients_s::get_instance();
    std::lock_guard<std::mutex> lk(response::write_mutex);
    while (total < msg.size()) {
        result = write(clients.p_clients[index].fd, msg.c_str(), msg.size());
        if (result > 0) {
            total += result;
        } else if (result == 0) {
            clients::reset(index);
            return;
        } else if (result < 0) {
            clients::reset(index);
            return;
        }
    }

    //if (record_msg)
    //    chatlog::chatlog.add(msg);
}