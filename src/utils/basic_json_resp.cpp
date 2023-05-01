#include "basic_json_resp.hpp"

#include <common/json_keys.hpp>
#include <utils/date_time.hpp>

// This is where all the json key values that are common
// to every response are placed.
void utils::init_json_resp(rapidjson::Document &doc)
{
    doc.SetObject();

    auto timestamp = utils::time_stamp();
    rapidjson::Value timestampkey;
    timestampkey.SetString(json_keys::TIMESTAMP.c_str(), json_keys::TIMESTAMP.size(), doc.GetAllocator());
    rapidjson::Value timestampval;
    timestampval.SetString(timestamp.c_str(), timestamp.size(), doc.GetAllocator());
    doc.AddMember(timestampkey, timestampval, doc.GetAllocator());

    rapidjson::Value serverkey;
    serverkey.SetString(json_keys::SERVER.c_str(), json_keys::SERVER.size(), doc.GetAllocator());
    rapidjson::Value serverval;
    serverval.SetString(json_keys::GRACKLE.c_str(), json_keys::GRACKLE.size(), doc.GetAllocator());
    doc.AddMember(serverkey, serverval, doc.GetAllocator());
}