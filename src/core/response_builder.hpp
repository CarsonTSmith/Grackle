#pragma once

#include <json_fwd.hpp>
#include <string>

using json = nlohmann::json;

namespace response {

std::string build(const json &body);

}