#include "response.hpp"

#include "clients.hpp"

#include <mutex>
#include <string>
#include <unistd.h>

// sends the msg to all connected tcp clients
void response::send_to_all(const std::string &msg)
{
    auto &clients = clients::clients_s::get_instance();
    for (int i = 0; (size_t)i < clients::MAX_CLIENTS; ++i) {
        if (clients.p_clients[i].fd == -1)
            continue;

        response::send(i, msg);
    }
}

// index is who is being sent the message
// msg is the string being sent
void response::send(const int index, const std::string &msg)
{
    size_t result = 0, total = 0;

    if (msg.size() == 0)
        return;

    auto &clients = clients::clients_s::get_instance();
    std::lock_guard<std::mutex> lk(clients.c_clients[index].write_mutex);
    while (total < msg.size()) {
        result = write(clients.p_clients[index].fd, msg.c_str() + total, msg.size() - total);
        if (result > 0) {
            total += result;
        } else if (result == 0) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                return;
                
            clients::reset(index);
            return;
        } else if (result < 0) {
            clients::reset(index);
            return;
        }
    }
}