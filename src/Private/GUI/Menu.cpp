#include "GUI/Menu.h"

namespace GUI
{

    GUI::Button& Menu::AddButton(std::string text, sf::Font& font, sf::Uint32 style, unsigned int font_size, sf::Vector2f size, float space) {
        sf::Vector2f position;
        if (!m_buttons.empty()) {
            position.x = m_buttons.back().getPosition().x;
            position.y = m_buttons.back().getPosition().y + m_buttons.back().getDimensions().y + space;
        }
        else {
            position = m_pos;
        }

        m_buttons.emplace_back(text, font, position, style, size, font_size); // Construct button in-place
        return m_buttons.back(); // Return a reference to the newly created button
    }


    void Menu::handleEvents(sf::Event& event, sf::RenderWindow& window)
    {
        for (auto& Button : m_buttons)
        {
            Button.update(event, window);
        }
    }

    void Menu::render(sf::RenderWindow& window)
    {
        for (const auto& Button : m_buttons)
        {
            window.draw(Button);
        }
    }
}
