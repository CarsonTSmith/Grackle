#pragma once

#include <mutex>
#include <string>


namespace response {

void send(const int index, const std::string &msg);
void send(const int index, const char *msg, const size_t len);
void send_to_all(const std::string &msg);

} // END Namespace response