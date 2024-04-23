#pragma once
#include <SFML/Graphics.hpp>

#include <string>
class SceneItem : public sf::Drawable 
{
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const final
	{
		Draw(window, states);
	}

	virtual void Draw(sf::RenderTarget& window, sf::RenderStates states) const = 0;

	virtual void Update(sf::RenderWindow& window) = 0;

	virtual void HandleInput(sf::Event e, sf::RenderWindow& window) = 0;

public:
	bool bShowing = false;
	std::string ItemName;
};