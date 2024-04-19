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
	void StopHandlingInput();
	void StartHandlingInput();

	GUI::MenuBox& GetMainMenu() { return MainMenu; }

	void ShowGame();

	void AddSprite(const std::string& sprite_name, const std::string& file_name, const sf::Vector2u& position = { 50, 40 }, bool user_scale = false, float scale = 1.0f);

	void AddBackground(const std::string& bg_name, const std::string& file_name);

	void ShowBackground(const std::string& bg_name);

	void SetBackgroundColor(const sf::Color& color);
	
	void ShowSprite(const std::string& sprite_name);

	void HideSprite(const std::string& sprite_name);

	void SetText(const std::wstring& text, const std::wstring& name = L"");
	void SetTextFont(const std::string& file_name);
	void SetTextCharacterSize(float text_size, float name_size = -1);
	void SetTextColor(const sf::Color& color);
	void SetTextHoverColor(const sf::Color& color);
	
	void SetChoices(const std::vector<std::wstring>& options);

private:
	const ConfigOptions& Options;
	const std::string& Root;
	sf::RenderWindow& Window;
	GameController* Game;
	bool bHandleInput = true;


private:
	bool bPlay = false;
	bool bPlayBackgAnim = false;
	GUI::MenuBox MainMenu;
	GUI::DialogBox DialogBox;
	sf::Font TextFont;
	sf::Music Music;

	std::vector<UserSprite> Sprites;
	std::list<UserSprite*> ShownSprites;

	std::vector<UserSprite> Backgrounds;
	UserSprite* Background;

private:
	void ToggleHandlingInput();
	void ToNextFrame();
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

/*
������������� FadeAnimation �� Thor ��� �������� ����� ����������
���������� Thor ������������� ������� ����� FadeAnimation, ������� �������� �������� ��� �������� �������� �������� ����� ���������� ����.
��� ��� ������������ FadeAnimation ��� ����� ������:
�������� ������������ ����:
#include <Thor/Animations.hpp>
Use code with caution.
C++
�������� ������� sf::Sprite ��� ������ �������� ����.
�������� ������ FadeAnimation:
// ������ ����� �������� - 1 �������
sf::Time fadeTime = sf::seconds(1.f);

// FadeAnimation � ������� ���������� (0.25 �������) � ������������� (0.5 �������)
thor::FadeAnimation fadeAnimation(0.25f, 0.5f);
Use code with caution.
C++
�������� ������ sf::Clock ��� ������������ �������.
� ����� ���������:
�������� ����� ��������:
sf::Time elapsedTime = clock.restart();
float progress = elapsedTime / fadeTime;
Use code with caution.
C++
��������� FadeAnimation � ������� �������� ����:
fadeAnimation(currentBackgroundSprite, progress);
Use code with caution.
C++
��������� FadeAnimation � ����� �������� ���� (� ��������������� ����������):
fadeAnimation(newBackgroundSprite, 1.f - progress);
Use code with caution.
C++
��������� ��� �������� ����.
����� ���������� �������� (progress >= 1.f):
���������� ����� �������� ��� �������.
������������ ������������� FadeAnimation:
��������: �� ������� ��������� ����������� �������� ��� ������� ������ �����-����������.
��������: ��������� ��������� ����� ��������� � ������������ �������.
���������� � SFML: FadeAnimation �������� �������� � ��������� sf::Sprite.
������ ����:
#include
#include

int main()
{
	// ... (�������� ����, ������� � ��������) ...

	sf::Clock clock;
	sf::Time fadeTime = sf::seconds(1.f);
	thor::FadeAnimation fadeAnimation(0.25f, 0.5f);

	while (window.isOpen())
	{
		// ... (��������� �������) ...

		sf::Time elapsedTime = clock.restart();
		float progress = elapsedTime / fadeTime;

		fadeAnimation(currentBackgroundSprite, progress);
		fadeAnimation(newBackgroundSprite, 1.f - progress);

		window.clear();
		window.draw(currentBackgroundSprite);
		window.draw(newBackgroundSprite);
		window.display();

		if (progress >= 1.f)
		{
			currentBackgroundSprite = newBackgroundSprite;
			// ... (��������� ����� �������� ��� newBackgroundSprite) ...
			clock.restart();
		}
	}

	return 0;
}
*/