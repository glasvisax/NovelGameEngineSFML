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
Использование FadeAnimation из Thor для перехода между текстурами
Библиотека Thor предоставляет удобный класс FadeAnimation, который идеально подходит для создания плавного перехода между текстурами фона.
Вот как использовать FadeAnimation для вашей задачи:
Включите заголовочный файл:
#include <Thor/Animations.hpp>
Use code with caution.
C++
Создайте объекты sf::Sprite для каждой текстуры фона.
Создайте объект FadeAnimation:
// Полное время анимации - 1 секунда
sf::Time fadeTime = sf::seconds(1.f);

// FadeAnimation с плавным появлением (0.25 секунды) и исчезновением (0.5 секунды)
thor::FadeAnimation fadeAnimation(0.25f, 0.5f);
Use code with caution.
C++
Создайте объект sf::Clock для отслеживания времени.
В цикле отрисовки:
Обновите время анимации:
sf::Time elapsedTime = clock.restart();
float progress = elapsedTime / fadeTime;
Use code with caution.
C++
Примените FadeAnimation к текущей текстуре фона:
fadeAnimation(currentBackgroundSprite, progress);
Use code with caution.
C++
Примените FadeAnimation к новой текстуре фона (с инвертированным прогрессом):
fadeAnimation(newBackgroundSprite, 1.f - progress);
Use code with caution.
C++
Отрисуйте обе текстуры фона.
После завершения анимации (progress >= 1.f):
Установите новую текстуру как текущую.
Преимущества использования FadeAnimation:
Простота: Не требует написания собственных шейдеров или сложной логики альфа-смешивания.
Гибкость: Позволяет настроить время появления и исчезновения текстур.
Интеграция с SFML: FadeAnimation работает напрямую с объектами sf::Sprite.
Пример кода:
#include
#include

int main()
{
	// ... (Создание окна, текстур и спрайтов) ...

	sf::Clock clock;
	sf::Time fadeTime = sf::seconds(1.f);
	thor::FadeAnimation fadeAnimation(0.25f, 0.5f);

	while (window.isOpen())
	{
		// ... (Обработка событий) ...

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
			// ... (Загрузить новую текстуру для newBackgroundSprite) ...
			clock.restart();
		}
	}

	return 0;
}
*/