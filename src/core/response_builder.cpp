#include "response_builder.hpp"

#include "client.hpp"

#include <nlohmann/json.hpp>

std::string response_builder::build(const json &body)
{
    std::string bytes = std::to_string(body.dump().size());
    std::string ret(client::HEADER_SIZE - bytes.size(), '0'); // TODO: need to check if size is too big
    ret += bytes;
    ret += body.dump();
    return ret;
}