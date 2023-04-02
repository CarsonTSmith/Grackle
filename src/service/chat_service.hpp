#pragma once

#include <string>
#include <json_fwd.hpp>

using json = nlohmann::json;

namespace chat_service {

std::string chat_send_response(const json &body);

}