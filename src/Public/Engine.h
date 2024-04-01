#pragma once

#include <SFML/Graphics.hpp>
#include "Script.h"
#include "Game.h"
#include "Config.h"
#include <vector>

class Engine
{
public:
	int start();
	Engine(int argc, char* argv[]);

private:
	sf::RenderWindow window;
	std::vector<Statement> statements;

	ConfigOptions opts;
	std::string resRoot;
};

