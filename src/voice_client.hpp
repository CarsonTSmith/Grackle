#pragma once

#include <netinet/in.h>
#include <stdint.h>

namespace voiceclient {

    struct voiceclient_t {
        
        uint64_t        last_message_time; // seconds since epoch
        struct sockaddr addr;
    };
}