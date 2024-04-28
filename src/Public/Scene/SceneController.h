#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>
#include <functional>

#include "GUI.h"
#include "SceneSprite.h"

struct ConfigOptions
{
	unsigned int width;
	unsigned int height;
	std::string title;
	std::string main_font;
	std::vector<std::string> content_folders;

	uint8_t backgrounds_amount;
	uint8_t sprites_amount;
	uint8_t menus_amount;
};

struct ColorWrapper 
{
	ColorWrapper(unsigned int _r, unsigned int _g, unsigned int _b, unsigned int _a) : r(_r), g(_g), b(_b), a(_a) {}
	sf::Color ToSFMLColor() const;
	static const ColorWrapper Black;
	static const ColorWrapper White;
	static const ColorWrapper Green;
	static const ColorWrapper Red;
	static const ColorWrapper Blue;
	static const ColorWrapper Grey;

	unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;
	unsigned int a = 0;

};

const ColorWrapper ColorWrapper::Black(0, 0, 0, 255);
const ColorWrapper ColorWrapper::White(255, 255, 255, 255);
const ColorWrapper ColorWrapper::Green(0, 255, 0, 255);
const ColorWrapper ColorWrapper::Red(255, 0, 0, 255);
const ColorWrapper ColorWrapper::Blue(0, 0, 255, 255);
const ColorWrapper ColorWrapper::Grey(0, 0, 0, 128);

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
	void SetBackgroundColor(const ColorWrapper& color, float fade_time = 0.0f);

	MenuBox& AddMenu(const sf::Vector2f& pos, const std::vector<std::wstring>& buttons, std::string name);
	void ShowMenu(const std::string& name);
	void HideMenu(const std::string& name);

	void SetupDialogBox(const sf::Vector2f& background_size, const sf::Vector2f& position, float corner_radius = 10.0f, const ColorWrapper& background_color = ColorWrapper(128, 128, 128, 200), float outline_thickness = 0.0f, const ColorWrapper& outline_color = ColorWrapper::Black);
	
	void SetDialogBoxTextColor(const ColorWrapper& color);
	void SetDialogBoxHoverTextColor(const ColorWrapper& color);
	void SetDialogBoxPrintTime(float time_milsec);
	void SetDialogBoxCharSize(float text_size, float name_size);
	
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
