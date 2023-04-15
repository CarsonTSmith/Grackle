#pragma once

#include <mutex>
#include <string>


namespace response {

void send(const int index, const std::string &msg);
void send_to_all(const std::string &msg);

} // END Namespace response