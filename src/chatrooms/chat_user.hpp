#pragma once

#include <string>

namespace chat_user {

// stores the information regarding a client
struct chat_user_t {
    std::string m_username;
    int m_tcp_client_index = -1; // index in the tcp socket array

    chat_user_t(std::string &&username, const int index);
};



}