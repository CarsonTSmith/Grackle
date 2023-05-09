#pragma once

#include "voice_client.hpp"

#include <forward_list>
#include <mutex>
#include <unordered_set>

namespace voice_clients {

// TODO: place these in a struct
// struct clients {

//     std::unordered_set<voice_client::voice_client_t> m_clients;
//     std::mutex mutex;

// };
extern std::forward_list<voice_client::voice_client_t> clients;
extern std::mutex clients_mutex;

void add_client(const struct sockaddr *addr);
void do_prune_clients();

}