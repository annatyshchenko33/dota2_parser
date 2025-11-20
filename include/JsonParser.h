#pragma once

#include "BaseParser.h"
#include <string>
#include <vector>
#include "rapidjson/document.h"
#include <unordered_map>

struct Data
{
	uint64_t match_id;
	int hero_id;
	int kills;
	int deaths;
	int assists;
	bool radiant_win;
	int player_slot;
};

struct Data_User
{
	uint32_t account_id;
	std::string personaname;
	uint32_t steamid;
	std::string avatar;
	float computed_mmr;
};

class JsonParser : public BaseParser
{
public:
	JsonParser() = default;

	void parse(const std::string& data) override;
	const std::vector<Data>& get_matches() const;

	void parse_user(const std::string& data) override;
	 Data_User * get_users();
	
	 void parse_hero() override;
	 std::string get_hero_name(int hero_id) override;

private:
	std::vector<Data> matches;
	Data_User user;
	std::unordered_map<int, std::string> hero_map;
};