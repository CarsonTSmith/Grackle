#pragma once

#include "voice_client.hpp"

#include <forward_list>
#include <mutex>

namespace voice_clients {

    extern std::forward_list<voice_client::voice_client_t> clients;
    extern std::mutex clients_mutex;

    void add_client(const struct sockaddr *addr);
    void do_prune_clients();
}