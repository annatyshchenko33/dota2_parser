#include "Fetcher.h"
#include <httplib.h>
#include <iostream>
#include <sstream>


std::string Fetcher::fixInvalidJson(const std::string& json)
{
   
    if (json.empty()) return json;

    auto first = json.find_first_of("{[");
    auto last = json.find_last_of("}]");
    if (first != std::string::npos && last != std::string::npos && last >= first) {
        return json.substr(first, last - first + 1);
    }

    std::string out;
    out.reserve(json.size());
    for (char c : json) {
        if (c != '\0') out.push_back(c);
    }
    return out;
}


std::string Fetcher::fetch(int user_id, int limit)
{
    try
    {
        httplib::Client cli("https://api.opendota.com");
        std::ostringstream url;
        url << "/api/players/" << user_id << "/matches?limit=" << limit;
        auto res = cli.Get(url.str().c_str());
        if (res && res->status == 200) {
            return fixInvalidJson(res->body);
        } else {
            std::cerr << "Failed to fetch data. HTTP Status: " 
                      << (res ? std::to_string(res->status) : "No Response") 
                      << std::endl;
            return "";
		}

    }
    catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
	}
}

std::string Fetcher::fetch_user(int user_id)
{
    try
    {
        httplib::Client cli("https://api.opendota.com");
        std::ostringstream url;
        url << "/api/players/" << user_id;
        auto res = cli.Get(url.str().c_str());
        if (res && res->status == 200) {
            return fixInvalidJson(res->body);
        } else {
            std::cerr << "Failed to fetch data. HTTP Status: " 
                      << (res ? std::to_string(res->status) : "No Response") 
                      << std::endl;
            return "";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }
}
