#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>

using json = nlohmann::json;

namespace response_builder {

std::string build(const json &body);

}