#pragma once

#include <netinet/in.h>
#include <stdint.h>

namespace voice_client {

    struct voice_client_t {
        
        uint64_t        last_message_time; // milliseconds since epoch
        struct sockaddr addr;
    };

    bool operator==(const voice_client_t &rhs, const voice_client_t &lhs);
}