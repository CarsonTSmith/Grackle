#include "basic_json_resp.hpp"

#include <common/json_keys.hpp>
#include <utils/date_time.hpp>

// This is where all the json key values that are common
// to every response are placed.
// body param is from the incoming request
void utils::init_json_resp(rapidjson::Document &doc, const rapidjson::Document &body)
{
    doc.SetObject();

    // ["timestamp"]
    auto timestamp = utils::time_stamp();
    rapidjson::Value timestampkey;
    timestampkey.SetString(json_keys::TIMESTAMP.c_str(), json_keys::TIMESTAMP.size(), doc.GetAllocator());
    rapidjson::Value timestampval;
    timestampval.SetString(timestamp.c_str(), timestamp.size(), doc.GetAllocator());
    doc.AddMember(timestampkey, timestampval, doc.GetAllocator());

    // ["server": "Grackle"]
    rapidjson::Value serverkey;
    serverkey.SetString(json_keys::SERVER.c_str(), json_keys::SERVER.size(), doc.GetAllocator());
    rapidjson::Value serverval;
    serverval.SetString(json_keys::GRACKLE.c_str(), json_keys::GRACKLE.size(), doc.GetAllocator());
    doc.AddMember(serverkey, serverval, doc.GetAllocator());

     // ["path"]
    rapidjson::Value pathkey;
    pathkey.SetString(json_keys::PATH.c_str(), json_keys::PATH.size(), doc.GetAllocator());
    rapidjson::Value pathval;
    pathval.SetString(body[json_keys::PATH.c_str()].GetString(), body[json_keys::PATH.c_str()].GetStringLength(), doc.GetAllocator());
    doc.AddMember(pathkey, pathval, doc.GetAllocator());

    //["username"]
    rapidjson::Value usernamekey;
    usernamekey.SetString(json_keys::USERNAME.c_str(), json_keys::USERNAME.size(), doc.GetAllocator());
    rapidjson::Value usernameval;
    usernameval.SetString(body[json_keys::USERNAME.c_str()].GetString(), body[json_keys::USERNAME.c_str()].GetStringLength(), doc.GetAllocator());
    doc.AddMember(usernamekey, usernameval, doc.GetAllocator());
}