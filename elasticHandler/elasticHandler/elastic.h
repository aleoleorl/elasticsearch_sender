#pragma once
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class Elastic
{
private:
    string baseUrl;
    struct curl_slist* headers;

public:
    Elastic(const string& configFilePath);
    ~Elastic();
    void sendDataToElasticsearch(const string& index, const string& data);
};