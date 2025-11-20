#include "JsonParser.h"
#include <iostream>

void JsonParser::parse(const std::string& data)
{
	rapidjson::Document document;

	document.Parse(data.c_str());

	if (document.HasParseError())
	{
		std::cout << "Parse Error" << std::endl;
		return;
	}

	if (!document.IsArray())
	{
		std::cout << "Parse Error(Array)" << std::endl;
		return;
	}

	matches.clear();

	for (auto& match : document.GetArray())
	{
		Data data;

		if (match.HasMember("match_id") && match["match_id"].IsInt64()) {
			data.match_id = match["match_id"].GetInt64();
		}
		else {
			data.match_id = 0; 
		}


		if (match.HasMember("hero_id") && match["hero_id"].IsInt()) {
			data.hero_id = match["hero_id"].GetInt();
		}
		else {
			data.hero_id = 0;
		}


		if (match.HasMember("kills") && match["kills"].IsInt()) {
			data.kills = match["kills"].GetInt();
		}
		else {
			data.kills = 0;
		}


		if (match.HasMember("deaths") && match["deaths"].IsInt()) {
			data.deaths = match["deaths"].GetInt();
		}
		else {
			data.deaths = 0;
		}


		if (match.HasMember("assists") && match["assists"].IsInt()) {
			data.assists = match["assists"].GetInt();
		}
		else {
			data.assists = 0;
		}


		if (match.HasMember("radiant_win") && match["radiant_win"].IsBool()) {
			data.radiant_win = match["radiant_win"].GetBool();
		}
		else {
			data.radiant_win = false;
		}


		if (match.HasMember("player_slot") && match["player_slot"].IsInt()) {
			data.player_slot = match["player_slot"].GetInt();


			bool isRadiant = data.player_slot < 128;
			bool playerWon = (isRadiant && data.radiant_win) || (!isRadiant && !data.radiant_win);

		}
		else {
			data.player_slot = 0;
		}

		
		matches.push_back(data);
	}
}


const std::vector<Data>& JsonParser::get_matches() const
{
	return matches;
}


void JsonParser::parse_user(const std::string& data)
{
	rapidjson::Document document;
	document.Parse(data.c_str());
	if (document.HasParseError())
	{
		std::cout << "Parse Error (user)" << std::endl;
		return;
	}

	if (!document.IsObject())
	{
		std::cout << "Parse Error(Object - user expected)" << std::endl;
		return;
	}

	const rapidjson::Value* src = nullptr;
	if (document.HasMember("profile") && document["profile"].IsObject()) {
		src = &document["profile"];
	}
	else {
		src = &document;
	}

	Data_User data_user;
	if (src->HasMember("account_id") && (*src)["account_id"].IsUint()) {
		data_user.account_id = (*src)["account_id"].GetUint();
	}
	else if (document.HasMember("account_id") && document["account_id"].IsUint()) {
		data_user.account_id = document["account_id"].GetUint();
	}
	else {
		data_user.account_id = 0;
	}

	if (src->HasMember("personaname") && (*src)["personaname"].IsString()) {
		data_user.personaname = (*src)["personaname"].GetString();
	}
	else {
		data_user.personaname.clear();
	}

	if (src->HasMember("steamid") && (*src)["steamid"].IsString()) {
		data_user.steamid = 0;
	}
	else if (src->HasMember("steamid") && (*src)["steamid"].IsUint64()) {
		data_user.steamid = static_cast<uint32_t>((*src)["steamid"].GetUint64());
	}
	else {
		data_user.steamid = 0;
	}

	if (src->HasMember("avatar") && (*src)["avatar"].IsString()) {
		data_user.avatar = (*src)["avatar"].GetString();
	}
	else {
		data_user.avatar.clear();
	}

	if (document.HasMember("mmr_estimate") && document["mmr_estimate"].IsObject() &&
		document["mmr_estimate"].HasMember("estimate") && document["mmr_estimate"]["estimate"].IsNumber()) {
		data_user.computed_mmr = static_cast<float>(document["mmr_estimate"]["estimate"].GetDouble());
	}
	else if (src->HasMember("computed_mmr") && (*src)["computed_mmr"].IsNumber()) {
		data_user.computed_mmr = static_cast<float>((*src)["computed_mmr"].GetDouble());
	}
	else {
		data_user.computed_mmr = 0.0f;
	}

	user = data_user;
}

Data_User* JsonParser::get_users() 
{
    return &user;
}