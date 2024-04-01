#pragma once

#include <string>
#include <vector> 
#include <SFML/Graphics.hpp>


namespace Utils
{
	sf::String wrapText(sf::String string, unsigned width, const sf::Font &font, unsigned charicterSize, bool bold = false);

	sf::Color parseColor(std::string str);


    class RoundedRectangleShape : public sf::Shape
    {
    public:
        RoundedRectangleShape() {}

        RoundedRectangleShape(const sf::Vector2f& size, float radius, unsigned int cornerPointCount);
        
        void setSize(const sf::Vector2f& size);

        const sf::Vector2f& getSize() const;

        void setCornersRadius(float radius);

        float getCornersRadius() const;

        void setCornerPointCount(unsigned int count);

        virtual std::size_t getPointCount() const;

        virtual sf::Vector2f getPoint(std::size_t index) const;

    private:
        sf::Vector2f mySize;
        float myRadius = 0;
        unsigned int myCornerPointCount = 0;
    };
};

