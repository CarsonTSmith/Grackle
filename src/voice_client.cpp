#include "voice_client.hpp"

#include <string.h>

bool voice_client::operator==(const voice_client_t &rhs, const voice_client_t &lhs)
{
    if (rhs.last_message_time != lhs.last_message_time)
        return false;
    
    if (strncmp(rhs.addr.sa_data, lhs.addr.sa_data, sizeof(sockaddr::sa_data)) != 0)
        return false;

    return true;
}