#include <sstream>

int StrToInt(std::string const &s)
{
    std::istringstream iss(s);
    int value;

    if (!(iss >> value))
        throw std::runtime_error("invalid int");

    return value;
}