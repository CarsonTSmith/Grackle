#include "response_builder.hpp"

#include "client.hpp"

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

std::string response_builder::build(const rapidjson::Document &body)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    body.Accept(writer);
    if (buffer.GetSize() > 99999999) {
        // response too big
    }

    std::string bytes = std::to_string(buffer.GetSize());
    std::string ret(client::HEADER_SIZE - bytes.size(), '0'); // TODO: need to check if size is too big
    ret += bytes;
    ret += buffer.GetString();
    return ret;
}