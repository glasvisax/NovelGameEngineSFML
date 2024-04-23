#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Engine
{

public:
	Engine(const std::string& root) { Root = root; }
	int Start();

private:
	std::string Root;
};

