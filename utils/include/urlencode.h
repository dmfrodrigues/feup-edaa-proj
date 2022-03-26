#ifndef URLENCODE_H_INCLUDED
#define URLENCODE_H_INCLUDED

#include <string>
#include <iostream>

std::string urlencode(const std::string &s);
std::string urlencode(const std::string &s, const std::string &encode);

std::string urldecode(const std::string &str);

#endif //URLENCODE_H_INCLUDED