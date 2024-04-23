#include "Scene/SceneSprite.h"

SceneSprite::SceneSprite(const SceneSprite& other)
{
	Texture = other.Texture;
	Sprite.setTexture(Texture);
	Sprite.setOrigin(other.Sprite.getOrigin());
	Sprite.setPosition(other.Sprite.getPosition());
	Sprite.scale(other.Sprite.getScale());
}

SceneSprite::SceneSprite(const sf::Texture& texture)
	: Texture(texture)
{
	Sprite.setTexture(Texture);
}

void SceneSprite::HandleInput(sf::Event e, sf::RenderWindow& window)
{
	if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left && bPlayMoveAnimation) {
		bPlayMoveAnimation = false;
		Sprite.setPosition(moveAnimationTarget);
	}
}

void SceneSprite::Update(sf::RenderWindow& window)
{
	if (bPlayFadeIn)
	{
		float elapsed = clock.getElapsedTime().asSeconds();
		float progress = (elapsed / FadeTime);
		progress = progress > 1.0f ? 1.0f : progress;

		FadeIn(Sprite, progress);

		if (progress >= 1.0f)
		{
			bPlayFadeIn = false;
			if (OnFadeInEnd) OnFadeInEnd();
		}
	}
	else if (bPlayFadeOut)
	{
		float elapsed = clock.getElapsedTime().asSeconds();
		float progress = elapsed / FadeTime;
		progress = progress > 1.0f ? 1.0f : progress;

		FadeOut(Sprite, progress);

		if (progress >= 1.0f)
		{
			bPlayFadeOut = false;
			if (OnFadeOutEnd) OnFadeOutEnd();
			return;
		}
	}
	if (bPlayMoveAnimation)
	{

		float elapsed = moveAnimationClock.getElapsedTime().asSeconds();
		float progress = elapsed / moveAnimationDuration;
		progress = progress > 1.0f ? 1.0f : progress;

		Sprite.setPosition(FormerPos + (moveAnimationTarget - FormerPos) * progress);

		if (progress >= 1.0f)
		{
			bPlayMoveAnimation = false;
			if (OnMoveAnimationEnd) OnMoveAnimationEnd();
		}
	}

}

void SceneSprite::Reset()
{
	auto& color = Sprite.getColor();
	Sprite.setColor(sf::Color(color.r, color.g, color.b, 255));
}

void SceneSprite::SetPosition(sf::Vector2f pos)
{
	Sprite.setPosition(pos);
}

void SceneSprite::Draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(Sprite);
}

void SceneSprite::PlayFadeOut(float fade_time)
{
	FadeTime = fade_time;
	bPlayFadeIn = false;
	bPlayFadeOut = true;
	clock.restart();
}
void SceneSprite::PlayFadeIn(float fade_time)
{
	FadeTime = fade_time;
	bPlayFadeOut = false;
	bPlayFadeIn = true;
	clock.restart();
}

void SceneSprite::PlayMoveAnimation(const sf::Vector2f& targetPosition, float duration)
{
	moveAnimationClock.restart();
	FormerPos = Sprite.getPosition();
	bPlayMoveAnimation = true;
	moveAnimationTarget = targetPosition;
	moveAnimationDuration = duration;
}