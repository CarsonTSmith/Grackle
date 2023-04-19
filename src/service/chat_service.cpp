#include "chat_service.hpp"

#include <common/json_keys.hpp>
#include <core/response_builder.hpp>
#include <json.hpp>
#include <utils/date_time.hpp>

std::string chat_service::chat_send_response(const json &body)
{
    json response_body;

    response_body[json_keys::TIMESTAMP] = utils::time_stamp();
    response_body[json_keys::SERVER]    = json_keys::GRACKLE;
    response_body[json_keys::PATH]      = body[json_keys::PATH];
    response_body[json_keys::MESSAGE]   = body[json_keys::MESSAGE];
    response_body[json_keys::USERNAME]  = body[json_keys::USERNAME];

    std::string response = response_builder::build(response_body);
    return response;
}