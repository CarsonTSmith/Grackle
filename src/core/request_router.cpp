#include "request_router.hpp"

#include "clients.hpp"

#include <common/json_keys.hpp>
#include <controller/chat_controller.hpp>
#include <controller/echo_controller.hpp>
#include <core/response.hpp>
#include <nlohmann/json.hpp>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <unordered_map>

using json = nlohmann::json;

static constexpr int CHAT_SEND = 1;
static constexpr int ECHO      = 2;

// The value to the "path" key in the body
static const std::unordered_map<std::string, int> route_table {
    {"/chat/send", CHAT_SEND},
    {"/echo" , ECHO}
};

int request_router::route(const int index)
{
    //int status;
    //json body;

    auto &clients = clients::clients_s::get_instance();
    // convert client msg body to json object

    rapidjson::Document d;
    d.Parse(clients.c_clients[index].body);

    //status = clients.c_clients[index].body_to_json(body);
    //if (status != 0)
    //    return -1; // failed, send json parse failed response
    // then get the "path" string
    auto it = route_table.find(d[json_keys::PATH.c_str()].GetString());
    if (it == route_table.end())
        return -1; // not found, return path not found response
    
    switch (it->second) {
    case CHAT_SEND:
        //controller::chat_send(body);
        break;
    case ECHO:
        response::send(index, "Hello, World!", 13);
        //controller::echo_one(index, body);
        break;
    default:
        // error response
        break;
    }
    // then search the route table
    // then send it to the proper controller
    // then return
    return 0;
}