#include "chat_controller.hpp"

#include <common/json_keys.hpp>
#include <core/clients.hpp>
#include <core/response.hpp>
#include <core/response_builder.hpp>
#include <json.hpp>
#include <utils/date_time.hpp>

// takes the body of the incoming request
int controller::chat_send(const json &body)
{
    json response_body;

    response_body[json_keys::TIMESTAMP] = utils::time_stamp();
    response_body[json_keys::SERVER]    = json_keys::SERVER;
    response_body[json_keys::PATH]      = body[json_keys::PATH];
    response_body[json_keys::MESSAGE]   = body[json_keys::MESSAGE];

    std::string response = response::build(response_body);
    response::send_to_all(response);
    // log it in the chatlog
    return 0;
}