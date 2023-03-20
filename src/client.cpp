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