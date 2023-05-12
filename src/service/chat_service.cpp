#include "chat_service.hpp"

#include <common/json_keys.hpp>
#include <core/response_builder.hpp>
#include <utils/basic_json_resp.hpp>
#include <utils/date_time.hpp>



using namespace rapidjson;



std::string chat_service::chat_send_response(const Document &body)
{
    Document response_body;
    std::string response;
    
    utils::init_json_resp(response_body, body); // required

    // ["message"]
    Value messagekey;
    messagekey.SetString(json_keys::MESSAGE.c_str(), json_keys::MESSAGE.size(), response_body.GetAllocator());
    Value messageval;
    messageval.SetString(body[json_keys::MESSAGE.c_str()].GetString(), body[json_keys::MESSAGE.c_str()].GetStringLength(), response_body.GetAllocator());
    response_body.AddMember(messagekey, messageval, response_body.GetAllocator());

    // ["chatroom"]
    /*
    Value chatroomkey;
    chatroomkey.SetString(json_keys::CHATROOM.c_str(), json_keys::CHATROOM.size(), response_body.GetAllocator());
    Value chatroomval;
    chatroomval.SetString(body[json_keys::CHATROOM.c_str()].GetString(), body[json_keys::CHATROOM.c_str()].GetStringLength(), response_body.GetAllocator());
    response_body.AddMember(chatroomkey, chatroomval, response_body.GetAllocator());
    */

    response = response_builder::build(response_body);
    return response;
}




std::string chat_service::create_chatroom_response(const Document &body)
{
    Document response_body;
    std::string response;
    
    utils::init_json_resp(response_body, body); // required

    // ["chatroom"]
    Value chatroomkey;
    chatroomkey.SetString(json_keys::CHATROOM.c_str(), json_keys::CHATROOM.size(), response_body.GetAllocator());
    Value chatroomval;
    chatroomval.SetString(body[json_keys::CHATROOM.c_str()].GetString(), body[json_keys::CHATROOM.c_str()].GetStringLength(), response_body.GetAllocator());
    response_body.AddMember(chatroomkey, chatroomval, response_body.GetAllocator());

    response = response_builder::build(response_body);
    return response;
}