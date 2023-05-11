#pragma once

#include <rapidjson/document.h>

namespace controller {

int chat_send(const rapidjson::Document &body);

int create_chatroom(const rapidjson::Document &body);
int delete_chatroom(const rapidjson::Document &body);
int get_chatrooms(const rapidjson::Document &body);

int add_user_to_chatroom(const rapidjson::Document &body);
int remove_user_from_chatroom(const rapidjson::Document &body);

}