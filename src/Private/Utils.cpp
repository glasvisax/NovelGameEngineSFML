#include "Logger.h"
#include "Utils.h"
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Utils 
{
    sf::String wrapText(sf::String string, unsigned width, const sf::Font& font, unsigned charicterSize, bool bold) {
        unsigned currentOffset = 0;
        bool firstWord = true;
        std::size_t wordBegining = 0;

        for (std::size_t pos(0); pos < string.getSize(); ++pos) {
            auto currentChar = string[pos];
            if (currentChar == '\n') {
                currentOffset = 0;
                firstWord = true;
                continue;
            }
            else if (currentChar == ' ') {
                wordBegining = pos;
                firstWord = false;
            }

            auto glyph = font.getGlyph(currentChar, charicterSize, bold);
            currentOffset += glyph.advance;

            if (!firstWord && currentOffset > width) {
                pos = wordBegining;
                string[pos] = '\n';
                firstWord = true;
                currentOffset = 0;
            }
        }

        return string;
    }


    sf::Color parseColor(std::string str) {
        std::istringstream ss(str);

        int r = 0;
        int g = 0;
        int b = 0;
        int a = 0;
        ss >> r;
        ss >> g;
        ss >> b;
        ss >> a;

        sf::Color newColor(r, g, b, a);
        return newColor;
    }

    RoundedRectangleShape::RoundedRectangleShape(const sf::Vector2f& size, float radius = 0, unsigned int cornerPointCount = 0)
    {
        mySize = size;
        myRadius = radius;
        myCornerPointCount = cornerPointCount;
        update();
    }

    void RoundedRectangleShape::setSize(const sf::Vector2f& size)
    {
        mySize = size;
        update();
    }

    const sf::Vector2f& RoundedRectangleShape::getSize() const
    {
        return mySize;
    }

    void RoundedRectangleShape::setCornersRadius(float radius)
    {
        myRadius = radius;
        update();
    }

    float RoundedRectangleShape::getCornersRadius() const
    {
        return myRadius;
    }

    void RoundedRectangleShape::setCornerPointCount(unsigned int count)
    {
        myCornerPointCount = count;
        update();
    }

    std::size_t RoundedRectangleShape::getPointCount() const
    {
        return myCornerPointCount * 4;
    }

    sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const
    {
        if (index >= myCornerPointCount * 4)
            return sf::Vector2f(0, 0);

        float deltaAngle = 90.0f / (myCornerPointCount - 1);
        sf::Vector2f center;
        unsigned int centerIndex = index / myCornerPointCount;
        static const float pi = 3.141592654f;

        switch (centerIndex)
        {
        case 0: center.x = mySize.x - myRadius; center.y = myRadius; break;
        case 1: center.x = myRadius; center.y = myRadius; break;
        case 2: center.x = myRadius; center.y = mySize.y - myRadius; break;
        case 3: center.x = mySize.x - myRadius; center.y = mySize.y - myRadius; break;
        }

        return sf::Vector2f(myRadius * cos(deltaAngle * (index - centerIndex) * pi / 180) + center.x,
            -myRadius * sin(deltaAngle * (index - centerIndex) * pi / 180) + center.y);
    }
}