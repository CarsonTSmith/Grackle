#pragma once

#include "chatroom.hpp"

namespace chatrooms {

class chatrooms_t {
private:
    std::unordered_set<std::shared_ptr<chatroom::chatroom_t>> m_rooms;

public:
    chatrooms_t();
    ~chatrooms_t();

    bool add(std::shared_ptr<chatroom::chatroom_t> &chatroom);
    bool remove(const std::string &chatroom_name);
};

extern chatrooms_t g_rooms;

}