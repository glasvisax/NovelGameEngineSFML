#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>
#include <functional>

#include "Game/Config/Config.h"
#include "GUI.h"
#include "SceneSprite.h"

using namespace GUI;
class SceneController
{
public:
	SceneController(const std::string& root, const ConfigOptions& opts, sf::RenderWindow& window);

public:
	void Exit();
	void StartScene();
	std::function<void()> ToNextFrameEvent = nullptr;
	std::function<void()> EscapePressEvent = nullptr;

private:
	void GlobalHandler();
	void HandleInput(sf::Event e);
	void Update();
	void Render();

public:
	void AddSprite(const std::string& sprite_name, const std::string& file_name, const sf::Vector2f& position = { 50, 40 }, float scale = 1.0f);
	void ShowSprite(const std::string& sprite_name, float fade_time = 0.0f);
	void HideSprite(const std::string& sprite_name, float fade_time = 0.0f);
	void SetSpritePosition(const std::string& sprite_name, sf::Vector2f pos);
	void PlaySpriteMoveAnim(const std::string& sprite_name, sf::Vector2f pos, float time = 5.0f);
	void HideAllSprites();

	void AddBackground(const std::string& bg_name, const std::string& file_name);
	void ShowBackground(const std::string& bg_name, float fade_time = 0.0f);
	void SetBackgroundColor(const sf::Color& color, float fade_time = 0.0f);

	MenuBox& AddMenu(const sf::Vector2f& pos, const std::vector<std::wstring>& buttons, std::string name);
	void ShowMenu(const std::string& name);
	void HideMenu(const std::string& name);

	DialogBox& SetupDialogBox(const sf::Vector2f& background_size, const sf::Vector2f& position, float corner_radius = 10.0f, const sf::Color& background_color = sf::Color(128, 128, 128, 200), float outline_thickness = 0.0f, const sf::Color& outline_color = sf::Color::Black);
	void ShowDialogBox();
	void HideDialogBox();
	void SetText(const std::wstring& text, const std::wstring& name, bool print_anim = false);
	void SetChoices(const std::vector<std::wstring>& options);
	unsigned int GetCurrentResponse();

private:
	const ConfigOptions& Options;
	const std::string& Root;
	sf::RenderWindow& Window;

private:
	bool bStart = false;
	bool bPlay = false;
	bool bWaitNextInput = false;	

private:
	sf::Font TextFont;

	std::vector<SceneSprite> Backgrounds;
	std::pair<SceneSprite*, SceneSprite*> Background;
	std::vector<MenuBox> Menus;
	std::vector<SceneSprite> Sprites;
	DialogBox DialogBox;

private:
	sf::Texture GetImageTexture(const std::string& file_name);
	std::string GetFilePath(const std::string& file_name);
	void SetTextureColor(sf::Texture& texture, const sf::Color& color);

public:
	void AddChannel(const std::string& name, const std::string& file_name);
	void PlayChannel(const std::string& name, bool loop = false);
	void StopChannel(const std::string& name);
	void SetChannelVolume(const std::string& name, float volume);
	void ReloadChannel(const std::string& name, const std::string& file_name);
	void PausePlayingChannels();
	void UnPausePlayingChannels();
	void StopAllChannels();

private:
	std::map<std::string, std::shared_ptr<sf::Music>> AudioChannels;

};
