#include "request_router.hpp"

#include "clients.hpp"

#include <common/json_keys.hpp>
#include <controller/chat_controller.hpp>
#include <controller/echo_controller.hpp>
#include <core/response.hpp>
#include <rapidjson/document.h>
#include <string_view>
#include <unordered_map>

static constexpr int ECHO          = -1;
static constexpr int CHAT_SEND     = 1;
static constexpr int GET_CHATROOMS = 2;


// The value to the "path" key in the body
static const std::unordered_map<std::string_view, int> route_table {
    {"/echo", ECHO},
    {"/chat/send", CHAT_SEND},
    {"/chat/chatrooms", GET_CHATROOMS}
};

int request_router::route(const int index)
{
    auto &clients = clients::clients_s::get_instance();
    rapidjson::Document d;
    int status = clients.c_clients[index].body_to_json(d);
    if (status != 0) {
        return -1; // TODO: failed, send json parse failed response to client
    }

    auto it = route_table.find(d[json_keys::PATH.c_str()].GetString());
    if (it == route_table.end()) {
        return -1; // not found, return path not found response
    }

    switch (it->second) {
    case ECHO:
        response::send(index, "Hello, World!", 13);
        //controller::echo_one(index, body);
        break;
    case CHAT_SEND:
        controller::chat_send(d);
        break;
    case GET_CHATROOMS:
        //controller::get_chatrooms(d);
    default:
        // error response
        break;
    }
    // then search the route table
    // then send it to the proper controller
    // then return
    return 0;
}