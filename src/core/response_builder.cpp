#include "response_builder.hpp"

#include "client.hpp"

#include <json.hpp>

std::string response::build(const json &body)
{
    std::string bytes = std::to_string(body.length());
    std::string ret(client::HEADER_SIZE - bytes.size(), 0);
    ret += bytes;
    ret += body.dump();
    return ret;
}