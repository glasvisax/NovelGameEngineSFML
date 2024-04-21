#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>
#include <functional>

#include "Game/Config/Config.h"
#include "GUI.h"
#include "SceneSprite.h"

class SceneController
{
public:

	SceneController(const std::string& root, const ConfigOptions& opts, sf::RenderWindow& window);

public:
	void StartScene();
	void Tick(float DeltaTime);
	void Exit();

	void HandleInput(sf::Event e);

	void StartGame();

public:
	void AddSprite(const std::string& sprite_name, const std::string& file_name, const sf::Vector2u& position = { 50, 40 }, bool user_scale = false, float scale = 1.0f);
	void ShowSprite(const std::string& sprite_name, bool fade_anim = false);
	void HideSprite(const std::string& sprite_name, bool fade_anim = false);

	void AddBackground(const std::string& bg_name, const std::string& file_name);
	void ShowBackground(const std::string& bg_name, bool fade_anim = false);
	void SetBackgroundColor(const sf::Color& color, bool fade_anim = false);

	void SetText(const std::wstring& text, bool print_anim = true, const std::wstring& name = L"");
	void SetTextFont(const std::string& file_name);
	void SetTextCharacterSize(float text_size, float name_size = -1);
	void SetTextColor(const sf::Color& color);
	void SetTextHoverColor(const sf::Color& color);
	
	void SetChoices(const std::vector<std::wstring>& options);

private:
	const ConfigOptions& Options;
	const std::string& Root;
	sf::RenderWindow& Window;

private:
	bool bStart = false;
	bool bPlay = false;
	bool bWaitNextInput = false;
	GUI::MenuBox MainMenu;
	GUI::DialogBox DialogBox;
	sf::Font TextFont;
	sf::Music Music;

	std::vector<SceneSprite> Sprites;
	std::list<SceneSprite*> ShownSprites;

	std::vector<SceneSprite> Backgrounds;
	SceneSprite* Background = nullptr;
	SceneSprite* FormerBackground = nullptr;

private:
	void ToNextFrame();
	void WaitNextInput();
	void OnChoiceSelected(unsigned int choice);
	void Render();

	sf::Texture GetImageTexture(const std::string& file_name);
	std::string GetFilePath(const std::string& file_name);
	void SetTextureColor(const sf::Color& color, sf::Texture& texture);

public:
	void AddAudioChannel(const std::string& name, const std::string& file_name);
	void PlayAudioChannel(const std::string& name, bool loop = false);
	void StopAudioChannel(const std::string& name);
	void SetAudioChannelVolume(const std::string& name, float volume);
	void ReloadAudioChannel(const std::string& name, const std::string& file_name);

private:
	std::map<std::string, std::shared_ptr<sf::Music>> AudioChannels;
};
