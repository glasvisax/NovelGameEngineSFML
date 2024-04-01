#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Script.h"
#include "Config.h"
#include "FPS.h"
#include <Utils.h>

#include <vector>

class Game
{
public:

	void handleInput(sf::Event e);
	void render(sf::RenderWindow& window);
	void update();
	Game(std::vector<Statement>&, ConfigOptions, std::string);
	void nextStatement();

private:
	ConfigOptions opts;
	std::string root;
	std::wstring textStr;

	sf::Music music;

	sf::Texture backgroundTex;
	sf::Sprite background;

	std::vector<Statement>& statements;

	sf::RectangleShape fadeRect;
	//sf::RectangleShape textRect;
	sf::RectangleShape test;

	sf::Sprite TextBoxSprite;
	sf::Texture TextBoxTexture;

	sf::Sprite MainCharacterSprite;
	sf::Texture MainCharacterTexture;

	sf::Text text;
	sf::Text debugText;
	sf::Font textFont;

	FPS fpsCounter;

	sf::Clock textClock;
	sf::Clock delayClock;
	
	std::size_t textPos = 0;
	std::size_t ip = -1; // Like instruction pointer

	int fade = 0; // if it is fade out, then fade < 0, if fade in - fade > 0
	int delay = 0;
	bool hideText = false;
	bool fadeOn = false;
	bool debug = false;
};
