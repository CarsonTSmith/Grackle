#include "chat_service.hpp"

#include <common/json_keys.hpp>
#include <core/response_builder.hpp>
#include <utils/basic_json_resp.hpp>
#include <utils/date_time.hpp>

std::string chat_service::chat_send_response(const rapidjson::Document &body)
{
    rapidjson::Document response_body;
    
    utils::init_json_resp(response_body); // required

    // ["path"]
    rapidjson::Value pathkey;
    pathkey.SetString(json_keys::PATH.c_str(), json_keys::PATH.size(), response_body.GetAllocator());
    rapidjson::Value pathval;
    pathval.SetString(body[json_keys::PATH.c_str()].GetString(), body[json_keys::PATH.c_str()].GetStringLength(), response_body.GetAllocator());
    response_body.AddMember(pathkey, pathval, response_body.GetAllocator());

    // ["message"]
    rapidjson::Value messagekey;
    messagekey.SetString(json_keys::MESSAGE.c_str(), json_keys::MESSAGE.size(), response_body.GetAllocator());
    rapidjson::Value messageval;
    messageval.SetString(body[json_keys::MESSAGE.c_str()].GetString(), body[json_keys::MESSAGE.c_str()].GetStringLength(), response_body.GetAllocator());
    response_body.AddMember(messagekey, messageval, response_body.GetAllocator());

    //["username"]
    rapidjson::Value usernamekey;
    usernamekey.SetString(json_keys::USERNAME.c_str(), json_keys::USERNAME.size(), response_body.GetAllocator());
    rapidjson::Value usernameval;
    usernameval.SetString(body[json_keys::USERNAME.c_str()].GetString(), body[json_keys::USERNAME.c_str()].GetStringLength(), response_body.GetAllocator());
    response_body.AddMember(usernamekey, usernameval, response_body.GetAllocator());

    std::string response = response_builder::build(response_body);
    return response;
}