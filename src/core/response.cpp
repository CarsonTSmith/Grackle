#include "response.hpp"

#include "clients.hpp"

#include <mutex>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

// sends the msg to all connected tcp clients
void response::send_to_all(const std::string &msg)
{
    auto &clients = clients::clients_s::get_instance();
    for (int i = 0; i < clients::MAX_CLIENTS; ++i) {
        if (clients.p_clients[i].fd != -1) {
            response::send(i, msg);
        }
    }
}

// index is who is being sent the message
// msg is the string being sent
void response::send(const int index, const std::string &msg)
{
    ssize_t result = 0, total = 0;

    if (msg.size() == 0) {
        return;
    }

    auto &clients = clients::clients_s::get_instance();
    std::lock_guard<std::mutex> lk(clients.c_clients[index].write_mutex);
    while (total < (ssize_t)msg.size()) {
        result = send(clients.p_clients[index].fd, msg.c_str() + total, msg.size() - total, MSG_NOSIGNAL);
        if (result > 0) {
            total += result;
        } else if (result == 0) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                return;
            }

            if (errno == EINTR) {
                continue;
            }
                
            clients::reset(index);
            return;
        } else if (result < 0) {
            clients::reset(index);
            return;
        }
    }
}

void response::send(const int index, const char *msg, const size_t len)
{
    size_t result = 0, total = 0;

    if (len == 0) {
        return;
    }

    auto &clients = clients::clients_s::get_instance();
    std::lock_guard<std::mutex> lk(clients.c_clients[index].write_mutex);
    while (total < len) {
        result = send(clients.p_clients[index].fd, msg + total, len - total, MSG_NOSIGNAL);
        if (result > 0) {
            total += result;
        } else if (result == 0) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                return;
            }

            if (errno == EINTR) {
                continue;
            }
                
            clients::reset(index);
            return;
        } else if (result < 0) {
            clients::reset(index);
            return;
        }
    }
}