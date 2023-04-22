#pragma once

#include <nlohmann/json_fwd.hpp>

using json = nlohmann::json;

namespace controller {

int echo_one(const int index, const json &body);

}