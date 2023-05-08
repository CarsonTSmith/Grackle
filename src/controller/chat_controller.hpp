#pragma once

#include <rapidjson/document.h>

namespace controller {

int chat_send(const rapidjson::Document &body);
int get_chatrooms(const rapidjson::Document &body);

}