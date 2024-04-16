#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>
#include <functional>

#include "Config.h"
#include "GUI/GUI.h"
#include "BaseController.h"

class GameController;

class SceneController : public BaseController
{
public:

	struct UserSprite 
	{
		UserSprite(const UserSprite& other) {
			Name = other.Name;
			Texture = other.Texture;
			Sprite.setTexture(Texture);
			Sprite.setOrigin(other.Sprite.getOrigin());
			Sprite.setPosition(other.Sprite.getPosition());
			Sprite.scale(other.Sprite.getScale());
		}

		UserSprite(const std::string& name, const sf::Texture& texture) : Name(name), Texture(texture)
		{
			Sprite.setTexture(Texture);
		}
		std::string Name;
		sf::Texture Texture;
		sf::Sprite Sprite;
	};


	SceneController(const std::string& root, const ConfigOptions& opts, sf::RenderWindow& window);

	void SetGameController(GameController* game) { this->Game = game; }

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void HandleInput(sf::Event e);

	GUI::MenuBox& GetMainMenu() { return MainMenu; }

	void ShowGame();

	void AddSprite(const std::string& sprite_name, const std::string& file_name, const sf::Vector2u& position = { 50, 40 }, bool user_scale = false, float scale = 1.0f);
	
	void ShowSprite(const std::string& sprite_name);

	void HideSprite(const std::string& sprite_name);

	void SetBackgroundColor(const sf::Color& color);

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
	std::vector<UserSprite> Sprites;
	std::list<UserSprite*> ShownSprites;

private:

	void Render();

	sf::Texture GetImageTexture(const std::string& file_name);
};