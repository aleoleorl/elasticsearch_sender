#include "elastic.h"

Elastic::Elastic(const string& configFilePath) : headers(nullptr) 
{
    ifstream configFile(configFilePath);
    if (!configFile.is_open()) 
    {
        throw runtime_error("Failed to open config file: " + configFilePath);
    }

    json config;
    configFile >> config;

    if (config.contains("elastic")) 
    {
        const auto& elasticConfig = config["elastic"];

        baseUrl = elasticConfig["base_url"].get<string>();

        if (elasticConfig.contains("headers")) 
        {
            for (auto it = elasticConfig["headers"].begin(); it != elasticConfig["headers"].end(); ++it)
            {
                string key = it.key();
                string value = it.value();
                headers = curl_slist_append(headers, (key + ": " + value).c_str());
            }
        }
    }
    else 
    {
        throw runtime_error("Elastic section is missing in config file: " + configFilePath);
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
}

Elastic::~Elastic() 
{
    curl_slist_free_all(headers);
    curl_global_cleanup();
}

void Elastic::sendDataToElasticsearch(const string& index, const string& data)
{
    CURL* curl = curl_easy_init();
    if (!curl)
    {
        cerr << "Failed to initialize CURL" << endl;
        return;
    }

    string url = baseUrl + "/" + index + "/_doc";

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) 
    {
        cerr << "CURL error: " << curl_easy_strerror(res) << endl;
    }
    else 
    {
        cout << "Data sent successfully to index: " << index << endl;
    }

    curl_easy_cleanup(curl);
}