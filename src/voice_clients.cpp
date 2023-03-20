#include "voice_clients.hpp"

#include <chrono>
#include <forward_list>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

std::forward_list<voice_client::voice_client_t> voice_clients::clients;

constexpr int UDP_TIMEOUT = 5000;

static void prune_clients()
{
    uint64_t time = std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::system_clock::now().time_since_epoch()).count();
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