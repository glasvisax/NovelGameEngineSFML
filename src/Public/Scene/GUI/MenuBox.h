#pragma once

#include <SFML/Graphics.hpp>

#include "Scene/GUI/Button.h" 
#include "Scene/SceneItem.h"

namespace GUI
{
    class MenuBox : public SceneItem
    {
    public:
        MenuBox() {};

        void HandleInput(sf::Event event, sf::RenderWindow& window) override;
        void Draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void Update(sf::RenderWindow& window) override;

        Button& AddButton(std::wstring text);

    public:
        void SetBoxPosition(const sf::Vector2f& position) { Position = position; }
        void SetButtonSize(const sf::Vector2f& size) { ButtonSize = size; }
        void SetSpace(float space) { Space = space; }

        void SetFont(const sf::Font& font) { Font = font; }
        void SetFontSize(float size) { FontSize = size; }

        sf::Vector2f GetPosition() const { return Position; }
        sf::Vector2f GetButtonSize() const { return ButtonSize; }

        Button* GetButtonByText(const std::wstring& text);
        
    private:
        std::vector<Button> Buttons;
        sf::Vector2f Position = sf::Vector2f(0.0f, 0.0f);
        sf::Vector2f ButtonSize = sf::Vector2f(200.0f, 50.0f);
        sf::Vector2f BoxSize = sf::Vector2f(0.0f, 0.0f);
        sf::Font Font;
        float Space = 10.0f;
        float FontSize = 24.0f;

        void LocateButtons();
    };
}