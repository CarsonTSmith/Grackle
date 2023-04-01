#include "chat_controller.hpp"

#include <common/json_keys.hpp>
#include <core/response.hpp>
#include <json.hpp>
#include <utils/date_time.hpp>

int controller::chat_send(json &request)
{
    // send response as a json string
    json response;

    response[json_keys::TIMESTAMP] = utils::time_stamp();
    response[json_keys::SERVER]    = json_keys::SERVER;
    response[json_keys::PATH]      = request[json_keys::PATH];
    response[json_keys::MESSAGE]   = request[json_keys::MESSAGE];
    return 0;
}