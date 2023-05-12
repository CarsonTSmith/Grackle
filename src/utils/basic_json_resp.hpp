#pragma once

#include <rapidjson/document.h>

namespace utils {

    // body is from the incoming request
    // doc is the outgoing json request document
    void init_json_resp(rapidjson::Document &doc, const rapidjson::Document &body);

}