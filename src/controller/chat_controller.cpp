#include "chat_controller.hpp"

#include <core/response.hpp>
#include <logger/chatlog.hpp>
#include <service/chat_service.hpp>

// takes the body of the incoming request
int controller::chat_send(const rapidjson::Document &body)
{
    std::string response = chat_service::chat_send_response(body);
    response::send_to_all(response);
    chatlog::chatlog.add(response);
    return 0;
}