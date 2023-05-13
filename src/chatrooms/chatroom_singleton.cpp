#include "chatroom_singleton.hpp"



chatrooms::chatroom_s::chatroom_s()
{
    rooms.add_chatroom(std::move(std::make_shared<chatroom::chatroom_t>(MAIN_CHATROOM)));
}



chatrooms::chatroom_s &chatrooms::chatroom_s::get_instance()
{
    static chatrooms::chatroom_s s;
    return s;
}



void chatrooms::init()
{
    chatrooms::chatroom_s::get_instance();
}