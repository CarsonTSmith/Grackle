#pragma once

#include <nlohmann/json_fwd.hpp>

using json = nlohmann::json;

namespace controller {

int chat_send(const json &body);

}