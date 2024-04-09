#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <functional>

#include "Config.h"
#include "GUI/GUI.h"
#include "BaseController.h"

class GameController;

class SceneController : public BaseController
{
public:
	SceneController(const std::string& root, const ConfigOptions& opts, sf::RenderWindow& window);

	void SetGameController(GameController* game);

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void HandleInput(sf::Event e);

	GUI::MenuBox& GetMainMenu() { return MainMenu; }

	void ShowGame();

private:
	const ConfigOptions& Options;
	const std::string& Root;
	sf::RenderWindow& Window;
	GameController* Game;

private:

	bool bPlay = false;
	GUI::MenuBox MainMenu;
	GUI::DialogBox DialogBox;
	sf::Font TextFont;
	sf::Music Music;
	sf::Texture BackgroundTexture;
	sf::Sprite Background;

private:

	void Render();

	void SetBackgroundColor(const sf::Color& color);
};