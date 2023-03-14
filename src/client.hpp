#pragma once

#include "http_header.hpp"

#include <string>

namespace client {

    static const int BUF_SIZE = 8196;

    struct client_t {
        std::string header_str;
        int header_bytes_read = 0;
        bool headers_finished = false;
        http_header::http_header_s headers;

        std::string body;
        int body_length = 0;
        int body_bytes_read = 0;
        
        client_t()
        {
            header_str.resize(BUF_SIZE);
            body.resize(BUF_SIZE);
        }
    };

} // END namespace client
