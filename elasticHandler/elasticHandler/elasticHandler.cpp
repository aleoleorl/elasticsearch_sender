#include <iostream>
#include <string>
#include "support.h"
#include "elastic.h"

using namespace std;

int main()
{
    try 
    {
        Support support;
        Elastic elastic("config.json");

        while (true) 
        {
            string index = "index-" + support.getCurrentDate();
            elastic.sendDataToElasticsearch(index, support.makeData());
            this_thread::sleep_for(chrono::minutes(10));
        }
    }
    catch (const exception& e) 
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}