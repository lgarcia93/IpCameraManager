#include "ConfigParser.h"
#include <string>
#include <fstream>
#include "json.hpp"
#include <filesystem>
#include <iostream>
#include "Types.h"

ConfigParser::ConfigParser(std::string path) : configFilePath(path)
{
	std::cout << std::filesystem::current_path() << std::endl;

	std::ifstream file(configFilePath);

	if (!file.is_open())
	{
		throw std::runtime_error("Error opening config file");
	}

	std::string jsonContent;
	
	std::string line;

	while (std::getline(file, line))
	{
		jsonContent.append(line);
		jsonContent.append("\n");
	}

	file.close();

	parseConfig(jsonContent);
}

void ConfigParser::parseConfig(std::string jsonContent)
{
	nlohmann::json parsedConfig = nlohmann::json::parse(jsonContent);

	config = parsedConfig.get<types::Config>();
}

types::Config ConfigParser::getConfig() const
{
	return config;
}
