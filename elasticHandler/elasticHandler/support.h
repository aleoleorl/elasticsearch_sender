#pragma once
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <string>

using namespace std;

class Support
{
public:
    string getCurrentDate();
    string makeData();
    string generateRandomString(size_t length);
};