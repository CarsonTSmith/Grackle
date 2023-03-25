#pragma once

#include <mutex>
#include <stdint.h>
#include <string>
#include <string.h>

namespace client {

    constexpr int BODY_SIZE   = 8192;
    constexpr int HEADER_SIZE = 8;

    // anytime a client makes a change to an instance variable
    // the mutex needs to be locked
    struct client_t {
        char       header[HEADER_SIZE];
        char       body[BODY_SIZE];
        bool       header_done     = false;
        uint32_t   body_length     = 0;
        uint32_t   header_bytes_rd = 0;
        uint32_t   body_bytes_rd   = 0;
        std::mutex mutex;
        
        client_t();

        void reset();
    };

} // END namespace client
