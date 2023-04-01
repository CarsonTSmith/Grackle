#pragma once

#include <mutex>
#include <string>


namespace response {

    extern std::mutex write_mutex;

    void send(const int index, const std::string &msg);
    void send_to_all(const std::string &msg);

} // END Namespace response