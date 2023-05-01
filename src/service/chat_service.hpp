#pragma once

#include <rapidjson/document.h>
#include <string>

namespace chat_service {

std::string chat_send_response(const rapidjson::Document &body);

}