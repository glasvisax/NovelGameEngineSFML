#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>
#include "SceneItem.h"

class SceneSprite : public SceneItem
{
public:

	SceneSprite(const SceneSprite& other);

	SceneSprite(const sf::Texture& texture);

	//TODO: implement handling
	virtual void HandleInput(sf::Event e, sf::RenderWindow& window) override;

	virtual void Update(sf::RenderWindow& window) override;
	virtual void Draw(sf::RenderTarget& window, sf::RenderStates states) const override;

public:
	void PlayFadeOut(float fade_time = 1.0f);
	void PlayFadeIn(float fade_time = 1.0f);
	void PlayMoveAnimation(const sf::Vector2f& targetPosition, float duration);

	sf::Sprite& GetSFMLSprite() { return Sprite; }
	sf::Texture& GetSFMLTexture() { return Texture; }

	void Reset();
	void SetPosition(sf::Vector2f pos);

private:
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
	sf::Vector2f FormerPos;

public:
	std::function<void()> OnFadeOutEnd;
	std::function<void()> OnFadeInEnd;
	std::function<void()> OnMoveAnimationEnd;
};