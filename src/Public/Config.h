#pragma once

#include <string>

struct ConfigOptions {
	int width;
	int height;
	std::string title;
	int fps;
};

class Config
{
public:
	ConfigOptions parse(std::string filename);
};

