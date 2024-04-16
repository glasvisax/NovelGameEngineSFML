#pragma once

#include <string>
#include <vector>

struct ConfigOptions 
{
	unsigned int width;
	unsigned int height;
	std::string title;
	std::string code_file;
	std::vector<std::string> content_folders;
};

class Config
{
public:
	ConfigOptions Parse(std::string filename);
};

