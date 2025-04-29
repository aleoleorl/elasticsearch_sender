#include "support.h"


string Support::getCurrentDate()
{
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);

    tm timeinfo;
    localtime_s(&timeinfo, &t);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", &timeinfo);
    return string(buffer);
}

string Support::generateRandomString(size_t length)
{
    const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, chars.size() - 1);

    string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += chars[distribution(generator)];
    }

    return randomString;
}

string Support::makeData()
{
    char buffer[26];
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    ctime_s(buffer, sizeof(buffer), &t);

    string timestamp(buffer);
    timestamp.erase(remove(timestamp.begin(), timestamp.end(), '\n'), timestamp.end());

    return R"({"message": ")" + generateRandomString(20) + R"(", "timestamp": ")" + timestamp + R"("})";
}