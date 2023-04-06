#include "date_time.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>

std::string utils::time_stamp()
{
    std::stringstream ss;
    std::time_t t = std::time(nullptr);
    ss << std::put_time(std::localtime(&t), "%F %T %Z");
    return ss.str();
}