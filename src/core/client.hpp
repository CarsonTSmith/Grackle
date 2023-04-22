#pragma once

#include <nlohmann/json_fwd.hpp>
#include <mutex>
#include <stdint.h>
#include <string>
#include <string.h>

using json = nlohmann::json;

namespace client {

constexpr int BODY_SIZE   = 8192;
constexpr int HEADER_SIZE = 8;

// anytime a client makes a change to an instance variable
// the mutex needs to be locked
struct client_t {
    char              header[HEADER_SIZE] = {0};
    char              body[BODY_SIZE]     = {0};
    bool              header_done         = false;
    uint32_t          body_length         = 0;
    uint32_t          header_bytes_rd     = 0;
    uint32_t          body_bytes_rd       = 0;
    std::mutex        read_mutex;
    std::mutex        write_mutex;
    //std::atomic<bool> is_processing;

    void reset();
    int  body_to_json(json &json);
};

} // END namespace client
