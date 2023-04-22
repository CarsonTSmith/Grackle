#include "echo_controller.hpp"

#include <core/response.hpp>
#include <core/response_builder.hpp>
#include <common/json_keys.hpp>
#include <nlohmann/json.hpp>
#include <utils/date_time.hpp>

int controller::echo_one(const int index, const json &body)
{
    json response_body;

    //response_body[json_keys::TIMESTAMP] = utils::time_stamp();
    response_body[json_keys::SERVER]    = json_keys::GRACKLE;
    response_body[json_keys::PATH]      = body[json_keys::PATH];
    response_body[json_keys::MESSAGE]   = body[json_keys::MESSAGE];

    std::string response = response_builder::build(response_body);
    response::send(index, response);
    return 0;
}