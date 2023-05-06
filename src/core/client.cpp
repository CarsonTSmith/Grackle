#include "client.hpp"

void client::client_t::reset()
{
    memset(header, 0, sizeof(header));
    memset(body, 0, sizeof(body));
    header_done     = false;
    body_length     = 0;
    header_bytes_rd = 0;
    body_bytes_rd   = 0;
    is_processing   = false;
}

int client::client_t::body_to_json(rapidjson::Document &json)
{
    int i = 0;

    for (i = 0; i < client::BODY_SIZE; ++i) {
        if (body[i] == '{') {
            break;
        }
    }

    json.Parse(&(body[i]));
    if (json.HasParseError()) {
        return -1;
    } else {
        return 0;
    }
}