#include "request_router.hpp"

#include "clients.hpp"

#include <iostream>
#include <json.hpp>
#include <string>
#include <unordered_map>

using json = nlohmann::json;

static constexpr int SEND_CHAT_MSG = 1;

static const std::unordered_map<std::string, int> route_table {
    {"/chat/send", SEND_CHAT_MSG}
};

int request_router::route(const int index)
{
    json j;

    auto &clients = clients::clients_s::get_instance();
    // convert client msg body to json object
    clients.c_clients[index].body_to_json(j);
    std::cout << j.dump() << std::endl;
    // then get the "path" string
    auto it = route_table.find(j["path"]);
    if (it == route_table.end())
        return -1; // not found, return generic response
    
    switch (it->second) {
    case SEND_CHAT_MSG:
        break;
        // call controller
    }
    // then search the route table
    // then send it to the proper controller
    // then return
    return 0;
}