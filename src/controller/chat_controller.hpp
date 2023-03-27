#pragma once

#include <json_fwd.hpp>

using json = nlohmann::json;

namespace chat_controller {

    int chat_send(json &body);
}