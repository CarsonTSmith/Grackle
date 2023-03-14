#pragma once

#include <string>

namespace client {

    constexpr int BODY_SIZE   = 8196;
    constexpr int HEADER_SIZE = 8;

    struct client_t {
        std::string header;
        std::string body;
        bool        header_done = false;
        int         body_length = 0;
        
        client_t()
        {
            header.resize(HEADER_SIZE);
            body.resize(BODY_SIZE);
        }
    };

} // END namespace client
