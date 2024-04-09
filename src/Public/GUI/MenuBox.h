#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h" 

namespace GUI
{
    class MenuBox : public sf::Drawable
    {
    public:
        MenuBox() {};

        GUI::Button& AddButton(std::string text, sf::Font& font, sf::Uint32 style, unsigned int font_size, sf::Vector2f size, float space = 10.0f);

        void HandleInput(sf::Event& event, sf::RenderWindow& window);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        void SetPosition(sf::Vector2f pos) { m_pos = pos; }

        sf::Vector2f GetPosition() const { return m_pos; }

        Button& GetButtonByText(const std::string& text);

    private:
        sf::Vector2f m_pos;
        std::vector<Button> m_buttons;
    };
}