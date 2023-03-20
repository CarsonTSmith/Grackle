#pragma once

#include "voice_client.hpp"

#include <forward_list>

namespace voice_clients {

    extern std::forward_list<voice_client::voice_client_t> clients;

    void do_prune_clients();
}