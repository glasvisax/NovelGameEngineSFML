#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h" 

namespace GUI
{
    class Menu
    {
    public:
        Menu() {};

        GUI::Button& AddButton(std::string text, sf::Font& font, sf::Uint32 style, unsigned int font_size, sf::Vector2f size, float space = 10.0f);

        
        void handleEvents(sf::Event& event, sf::RenderWindow& window);

        void render(sf::RenderWindow& window);
        
        void SetPosition(sf::Vector2f pos) { m_pos = pos; }

        sf::Vector2f GetPosition() { return m_pos; }

    private:
        sf::Vector2f m_pos;
        std::vector<Button> m_buttons;
    };
}