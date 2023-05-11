#pragma once

#include "chatroom.hpp"

namespace chatrooms {

class chatrooms_t {

using rooms_it = std::unordered_set<std::shared_ptr<chatroom::chatroom_t>>::iterator;

private:
    std::unordered_set<std::shared_ptr<chatroom::chatroom_t>> m_rooms;
    std::mutex m_mutex;

public:
    chatrooms_t() = default;
    ~chatrooms_t() = default;

    bool add_chatroom(std::shared_ptr<chatroom::chatroom_t> &&chatroom);
    bool remove_chatroom(const std::string &chatroom_name);
    bool add_user(const std::string &chatroom_name,
                  std::shared_ptr<chat_user::chat_user_t> &&user);
    bool remove_user(const std::string &chatroom_name, 
                     const int tcp_client_index);

private:
    rooms_it find_chatroom(const std::string &chatroom_name);
};

extern chatrooms_t g_rooms;

}