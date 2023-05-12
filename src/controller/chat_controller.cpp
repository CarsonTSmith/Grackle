#include "chat_controller.hpp"

#include <chatrooms/chatroom_singleton.hpp>
#include <common/json_keys.hpp>
#include <core/response.hpp>
#include <logger/chatlog.hpp>
#include <service/chat_service.hpp>

// takes the body of the incoming request
int controller::chat_send(const rapidjson::Document &body)
{
    std::string response = chat_service::chat_send_response(body);
    auto &chatrooms = chatrooms::chatroom_s::get_instance();
    chatrooms.rooms.send_msg_to_chatroom(body[json_keys::CHATROOM.c_str()].GetString(), response);
    //response::send_to_all(response);
    //chatlog::chatlog.add(response);
    return 0;
}



int controller::create_chatroom(const rapidjson::Document &body)
{
    std::string response = chat_service::create_chatroom_response(body);
    response::send_to_all(response);
    return 0;
}