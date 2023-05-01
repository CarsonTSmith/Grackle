#pragma once

#include <rapidjson/document.h>

namespace controller {

int echo_one(const int index, const rapidjson::Document &body);

}