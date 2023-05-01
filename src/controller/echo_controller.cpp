#include "echo_controller.hpp"

#include <core/response.hpp>
#include <core/response_builder.hpp>
#include <common/json_keys.hpp>
#include <rapidjson/document.h>
#include <utils/basic_json_resp.hpp>
#include <utils/date_time.hpp>

int controller::echo_one(const int index, const rapidjson::Document &body)
{
    rapidjson::Document response_body;

    utils::init_json_resp(response_body); // required

    rapidjson::Value pathkey;
    pathkey.SetString(json_keys::PATH.c_str(), json_keys::PATH.size(), response_body.GetAllocator());
    rapidjson::Value pathval;
    pathval.SetString(body[json_keys::PATH.c_str()].GetString(), body[json_keys::PATH.c_str()].GetStringLength(), response_body.GetAllocator());
    response_body.AddMember(pathkey, pathval, response_body.GetAllocator());

    rapidjson::Value messagekey;
    messagekey.SetString(json_keys::MESSAGE.c_str(), json_keys::MESSAGE.size(), response_body.GetAllocator());
    rapidjson::Value messageval;
    messageval.SetString(body[json_keys::MESSAGE.c_str()].GetString(), body[json_keys::MESSAGE.c_str()].GetStringLength(), response_body.GetAllocator());
    response_body.AddMember(messagekey, messageval, response_body.GetAllocator());

    std::string response = response_builder::build(response_body);
    response::send(index, response);
    return 0;
}