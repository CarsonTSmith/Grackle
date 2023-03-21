#include "voice_clients.hpp"

#include <chrono>
#include <forward_list>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

std::forward_list<voice_client::voice_client_t> voice_clients::clients;

std::mutex voice_clients::clients_mutex;

constexpr int UDP_TIMEOUT = 5000;

static bool client_already_exists(const struct sockaddr *addr)
{
    for (auto &client: voice_clients::clients) {
        if (memcmp(&client.addr, addr, sizeof(struct sockaddr)) == 0) {
            client.last_message_time = std::chrono::duration_cast<std::chrono::milliseconds>
                                       (std::chrono::system_clock::now().time_since_epoch()).count();
            return true;
        }
    }

    return false;
}

static void prune_clients()
{
    uint64_t time = std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::system_clock::now().time_since_epoch()).count();
    std::lock_guard<std::mutex> lk(voice_clients::clients_mutex);
    for (auto &client: voice_clients::clients) {
        if (time - client.last_message_time > UDP_TIMEOUT)
            voice_clients::clients.remove(client); // TODO: fix this, it's slow
    }
}

void voice_clients::do_prune_clients()
{
    while (1) {
        prune_clients();
        usleep(UDP_TIMEOUT / 2);
    }
}

void voice_clients::add_client(const struct sockaddr *addr)
{
    if (client_already_exists(addr))
        return;
    
    uint64_t time = std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::system_clock::now().time_since_epoch()).count();
    std::lock_guard<std::mutex> lk(voice_clients::clients_mutex);
    voice_clients::clients.emplace_front(voice_client::voice_client_t{time, *addr});
}