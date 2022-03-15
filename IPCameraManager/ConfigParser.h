#pragma once

#include <filesystem>
#include "Types.h"
class ConfigParser
{
public:
	ConfigParser(std::string path);

	types::Config getConfig() const;
private:
	std::filesystem::path configFilePath;
	void parseConfig(std::string jsonContent);
	types::Config config;
};

