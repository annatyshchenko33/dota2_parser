#pragma once
#include <vector>
#include <string>
struct Data;
struct Data_User;

class BaseParser
{
public:
	BaseParser() = default;
	virtual ~BaseParser() = default;

	virtual void parse(const std::string& data) = 0;

	virtual const std::vector<Data>& get_matches() const {
		static std::vector<Data> empty;
		return empty;
	}

	virtual void parse_user(const std::string& data) = 0;

	virtual  Data_User* get_users()  {
		static  Data_User* empty;
		return empty;
	}
};