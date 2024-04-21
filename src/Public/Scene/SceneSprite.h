#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

class SceneSprite : public sf::Drawable
{
public:
	SceneSprite(const SceneSprite& other);

	SceneSprite(const std::string& name, const sf::Texture& texture);

	void update();
	void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

public:
	void PlayFadeOut(float fade_time = 1.0f);
	void PlayFadeIn(float fade_time = 1.0f);
	void PlayMoveAnimation(const sf::Vector2f& targetPosition, float duration);

	std::string GetName() const { return Name; }

	void Reset();

private:
	std::string Name;
	sf::Texture Texture;
	sf::Sprite Sprite;

private:
	thor::FadeAnimation FadeIn = thor::FadeAnimation(0.5f, 0.0f);
	thor::FadeAnimation FadeOut = thor::FadeAnimation(0.0f, 0.5f);
	float FadeTime = 0.8f;
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