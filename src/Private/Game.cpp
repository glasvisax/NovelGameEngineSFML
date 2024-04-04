#include "Game.h"
#include "Script.h"
#include "Logger.h"
#include "Utils.h"
#include "Config.h"

#include <locale>
#include <string>
#include <sstream>
#include <codecvt>



Game::Game(std::vector<Statement>& _statements, ConfigOptions _opts, std::string _root) 
	: statements(_statements)
	, opts(_opts)
	, root(_root) {

	if (!TextBoxTexture.loadFromFile(root + "/text_box/text_box1.png"))
	{
		LOGGER->Log("Game", "ERROR: Failed to load /text_box/text_box1.png");
	}

	TextBoxSprite.setTexture(TextBoxTexture);
	TextBoxSprite.setPosition(sf::Vector2f(16.f, opts.height - 50 - 128));

	auto size = TextBoxTexture.getSize();
	TextBoxSprite.setScale(float(opts.width - 32.f) / size.x, float(170.f) / size.y);


	if (!MainCharacterTexture.loadFromFile(root + "/characters/milk_chan.png"))
	{
		LOGGER->Log("Game", "ERROR: Failed to load /characters/milk_chan.png");
	}

	MainCharacterSprite.setTexture(MainCharacterTexture);
	MainCharacterSprite.setPosition(sf::Vector2f(50, 50));
	MainCharacterSprite.setScale(0.5, 0.5);
	fadeRect.setSize(sf::Vector2f(opts.width, opts.height));
	fadeRect.setPosition(sf::Vector2f(0, 0));
	fadeRect.setFillColor(sf::Color::Black);


	LOGGER->Log("Game", "Got resRoot from Engine: '%s'", root.c_str());

	if (!textFont.loadFromFile(root + "/fonts/script.ttf")) {
		LOGGER->Log("Game","ERROR: Failed to load font /fonts/script.ttf");
	} else {
		text.setFont(textFont);
		text.setFillColor(sf::Color::Black);
		text.setPosition(TextBoxSprite.getPosition() + sf::Vector2f(30, 40));
		text.setCharacterSize(24);
	}


	backgroundTex.create(opts.width, opts.height);

	sf::Uint8* pixels = new sf::Uint8[opts.width * opts.height * 4]; // RGBA (4 канала цвета)
	memset(pixels, 255, opts.width * opts.height * 4);
	backgroundTex.update(pixels);

	background.setTexture(backgroundTex);
	delete[] pixels;

	main_menu.SetPosition(sf::Vector2f(opts.width / 2, (opts.height / 2) - 3 * 30));
	GUI::Button& play = main_menu.AddButton("Play", textFont, GUI::style::save, 20, sf::Vector2f(opts.width / 3, 50.0f));
	play.bind_on_click(this, &Game::OnPlay);
	main_menu.AddButton("Options", textFont, GUI::style::save, 20, sf::Vector2f(opts.width / 3, 50.0f));
	main_menu.AddButton("Exit", textFont, GUI::style::save, 20, sf::Vector2f(opts.width / 3, 50.0f));

}

void Game::handleInput(sf::Event e, sf::RenderWindow& window)
{
	//Show next text on mouse click
	if (e.type == sf::Event::MouseButtonReleased && delay == 0 && !fadeOn) {
		nextStatement();
	}

	if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::F3) {
		debug = !debug;
	}

	main_menu.handleEvents(e, window);
}

void Game::nextStatement() 
{
	//Stop if EOV (end-of-vector)
	if (ip + 1 == statements.size()) return;

	//Increment instruction pointer
	ip++;

	//Execute current statement
	Statement s = statements.at(ip);
	if (s.type == StatementType::BACKGROUND) {
		std::string path = root + "/img/" + s.content;
		if (!backgroundTex.loadFromFile(path)) {
			LOGGER->Log("Game","ERROR: Failed to load background %s at statement %d", s.content.c_str(), ip);
		} else {
			LOGGER->Log("Game","Changed background to %s", s.content.c_str());
		}
		background.setTexture(backgroundTex);
		background.setPosition(sf::Vector2f(0,0));

		nextStatement();
		return;
	}

	if (s.type == StatementType::TEXT) {
		textStr = s.wtext;
		text.setString(textStr[0]);
		textPos = 0;
		return;
	}

	if (s.type == StatementType::DELAY) {
		delay = atoi(s.content.c_str());
		hideText = true;
		delayClock.restart();
	}

	if (s.type == StatementType::FONT) {
		if (!textFont.loadFromFile(root + "/fonts/"+s.content)) {
			LOGGER->Log("Game","ERROR: Failed to load font %s at statement %d", s.content.c_str(), ip);
		} else {
			LOGGER->Log("Game","Changed font to %s", s.content.c_str());
		}
		nextStatement();
	}

	if (s.type == StatementType::TEXT_COLOR) {
		sf::Color c = Utils::parseColor(s.content);
		text.setFillColor(c);
		debugText.setFillColor(c);
		LOGGER->Log("Game","Changed text color to RGBA(%d,%d,%d,%d)", c.r, c.g, c.b, c.a);
		nextStatement();
	}

	if (s.type == StatementType::MUSIC) {
		std::string path = root + "/music/" + s.content;
		if (!music.openFromFile(path)) {
			LOGGER->Log("Game","ERROR: Failed to load music %s at statement %d", s.content.c_str(), ip);
		} else {
			LOGGER->Log("Game","Changed music to %s", s.content.c_str());
		}
		music.setLoop(true);
		music.play();

		nextStatement();
		return;
	}

	if (s.type == StatementType::FADE) {
		std::stringstream ss(s.content);
		int n = 0;
		std::string way;

		ss >> way; //in or out
		ss >> n; //fade speed

		if (way == "in") {
			fade = n;
			fadeOn = true;
			fadeRect.setFillColor(sf::Color(0,0,0,0));
			hideText = true;
		} else if (way == "out"){
			fade = -n;
			fadeOn = true;
			fadeRect.setFillColor(sf::Color(0,0,0,255));
			hideText = true;
		} else {
			LOGGER->Log("Game", "Unknown fade value at statements %d. Only 'in' and 'out' values are supported.", ip);
		}
	}
}

void Game::OnPlay()
{
	play = true;
}

void Game::update() 
{

	//Text printing animation
	if (textClock.getElapsedTime().asMilliseconds() > 30) {
		textPos++;
		if (textPos >= textStr.size()) {

		} else {
			std::wstring newStr = text.getString().toWideString();
			newStr += textStr[textPos];
			sf::String newsfStr(newStr);
			sf::String wrappedStr = Utils::wrapText(newsfStr, static_cast<unsigned int>(TextBoxTexture.getSize().x - 150), textFont, 24.f);
			text.setString(wrappedStr);
		}

	}

	//Delay logic
	if (delay > 0 && delayClock.getElapsedTime().asMilliseconds() > delay) {
		hideText = false;
		delay = 0;
		nextStatement();
	}

	if (fadeOn) {
		sf::Color c = fadeRect.getFillColor();

		//If fade animation is finished, continue executing statements
		if (fade < 0 && fade + c.a < 0) {
			fadeOn = false;
			hideText = false;
			nextStatement();
			return;
		} else if (fade > 0 && fade + c.a > 255) {
			fade = 0; // We do not set fadeOn to false to allow executing next statements without losing fade rect state
			hideText = false;
			nextStatement();
			return;
		} else {
			//If animation is in process, set rect color
			c.a += fade;
			fadeRect.setFillColor(c);
		}
	}

}

void Game::render(sf::RenderWindow& window) 
{

	window.draw(background);

	if (!play) 
	{
		main_menu.render(window);
	}
	//main_menu.draw(window);
	/*
	window.draw(background);
	window.draw(MainCharacterSprite);

	if (fadeOn) window.draw(fadeRect);

	//Draw only if text is not hidden
	if (!hideText) {
		window.draw(TextBoxSprite);
		window.draw(text);
	}


	//if (debug) window.draw(debugText);

	//fpsCounter.update();
	*/
}