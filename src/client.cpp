#include "client.hpp"

client::client_t::client_t()
{
    memset(header, 0, sizeof(header));
    memset(body, 0, sizeof(body));
}

void client::client_t::reset()
{
    memset(header, 0, sizeof(header));
    memset(body, 0, sizeof(body));
    header_done     = false;
    body_length     = 0;
    header_bytes_rd = 0;
    body_bytes_rd   = 0;
}

int client::client_t::body_to_json(json &json)
{
    int i = 0;

    for (i = 0; i < client::BODY_SIZE; ++i) {
        if (body[i] == '{')
            break;
    }

    json = &(body[i]);
    return 0;
}