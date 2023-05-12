#pragma once

#include "chatrooms.hpp"



namespace chatrooms {


static const std::string MAIN_CHATROOM = "Main";



class chatroom_s {

public:
    chatrooms_t rooms;

    chatroom_s(const chatroom_s &) = delete;
    chatroom_s &operator=(const chatroom_s &) = delete;

    static chatroom_s &get_instance();

private:
    chatroom_s();
};



void init();


}