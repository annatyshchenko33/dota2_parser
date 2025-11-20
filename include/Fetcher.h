#pragma once
#include<string>


class Fetcher 
{
public:
	std::string fetch(int user_id, int limit);
	std::string fetch_user(int user_id);
private:
	static std::string fixInvalidJson(const std::string& json);
};