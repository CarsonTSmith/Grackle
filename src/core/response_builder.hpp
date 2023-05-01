#pragma once

#include <rapidjson/document.h>
#include <string>

namespace response_builder {

std::string build(const rapidjson::Document &body);

}