#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>
#include <functional>

#include "Config.h"
#include "GUI/GUI.h"
#include "BaseController.h"

#include <Thor/Animations.hpp>

class GameController;

class SceneController : public BaseController
{
public:

	struct SceneSprite : sf::Drawable
	{
		SceneSprite(const SceneSprite& other)
		{
			Name = other.Name;
			Texture = other.Texture;
			Sprite.setTexture(Texture);
			Sprite.setOrigin(other.Sprite.getOrigin());
			Sprite.setPosition(other.Sprite.getPosition());
			Sprite.scale(other.Sprite.getScale());
		}

		SceneSprite(const std::string& name, const sf::Texture& texture)
			: Name(name)
			, Texture(texture)
		{
			Sprite.setTexture(Texture);
		}

		void update()
		{
			if (bPlayFadeIn)
			{
				float elapsedTime = clock.getElapsedTime().asSeconds();
				float progress = (elapsedTime / FadeTime);
				progress = progress > 1 ? 1 : progress;

				FadeIn(Sprite, progress);

				if (progress >= 1)
				{
					bPlayFadeIn = false;
					if (OnFadeInEnd) OnFadeInEnd();
				}
			} else if (bPlayFadeOut)
			{
				float elapsedTime = clock.getElapsedTime().asSeconds();
				float progress = elapsedTime / FadeTime;
				progress = progress > 1 ? 1 : progress;

				FadeOut(Sprite, progress);

				if (progress >= 1)
				{
					bPlayFadeOut = false;
					if (OnFadeOutEnd) OnFadeOutEnd();
					return;
				}
			} 
			if (bPlayMoveAnimation)
			{
				float elapsedTime = moveAnimationClock.getElapsedTime().asSeconds();
				float progress = elapsedTime / moveAnimationDuration;
				progress = progress > 1.f ? 1.f : progress;

				sf::Vector2f currentPosition = Sprite.getPosition();
				sf::Vector2f targetPosition = moveAnimationTarget;

				Sprite.setPosition(currentPosition + (targetPosition - currentPosition) * progress);

				if (progress >= 1.f)
				{
					bPlayMoveAnimation = false;
					if (OnMoveAnimationEnd) OnMoveAnimationEnd();
				}
			}
			
		}

		void Reset() 
		{
			auto& color = Sprite.getColor();
			Sprite.setColor(sf::Color(color.r, color.g, color.b, 255));
		}

		void draw(sf::RenderTarget& window, sf::RenderStates states) const override 
		{
			window.draw(Sprite);
		}

		std::string Name;
		sf::Texture Texture;
		sf::Sprite Sprite;

		void PlayFadeOut() 
		{
			bPlayFadeIn = false;
			bPlayFadeOut = true;
			clock.restart();
		}
		void PlayFadeIn() 
		{
			bPlayFadeOut = false;
			bPlayFadeIn = true;
			clock.restart();
		}
		void PlayMoveAnimation(const sf::Vector2f& targetPosition, float duration)
		{
			bPlayMoveAnimation = true;
			moveAnimationTarget = targetPosition;
			moveAnimationDuration = duration;
			moveAnimationClock.restart();
		}

		thor::FadeAnimation FadeIn = thor::FadeAnimation(0.5f, 0.0f);
		thor::FadeAnimation FadeOut = thor::FadeAnimation(0.0f, 0.5f);
		float FadeTime = 0.8f;	

	private:
		bool bPlayFadeOut = false;
		bool bPlayFadeIn = false;
		sf::Clock clock;

	private:

		bool bPlayMoveAnimation = false;
		sf::Vector2f moveAnimationTarget;
		float moveAnimationDuration = 1.0f;
		sf::Clock moveAnimationClock;

	public:
		std::function<void()> OnFadeOutEnd;
		std::function<void()> OnFadeInEnd;
		std::function<void()> OnMoveAnimationEnd;
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

	void ShowBackground(const std::string& bg_name, bool fade_anim = false);

	void SetBackgroundColor(const sf::Color& color, bool fade_anim = false);
	
	void ShowSprite(const std::string& sprite_name, bool fade_anim = false);

	void HideSprite(const std::string& sprite_name, bool fade_anim = false);

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
	GameController* Game;
	bool bHandleInput = true;


private:
	bool bPlay = false;
	bool bPlayBackgAnim = false;
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
