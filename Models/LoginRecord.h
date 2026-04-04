#pragma once
#include <string>

struct LoginRecord {
    std::string dateTime{};
    std::string userName{};
    std::string password{};
    int permissions{ 0 };
};
