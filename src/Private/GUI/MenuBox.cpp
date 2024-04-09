#include "GUI/MenuBox.h"
#include <cassert>
namespace GUI
{
    GUI::Button& MenuBox::AddButton(std::string text, sf::Font& font, sf::Uint32 style, unsigned int font_size, sf::Vector2f size, float space) {
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


    void MenuBox::HandleInput(sf::Event& event, sf::RenderWindow& window)
    {
        for (auto& Button : m_buttons)
        {
            Button.update(event, window);
        }
    }

    void MenuBox::draw(sf::RenderTarget& window, sf::RenderStates states) const
    {
        for (const auto& Button : m_buttons)
        {
            window.draw(Button);
        }
    }

    Button& MenuBox::GetButtonByText(const std::string& text)
    {
        for (Button& b : m_buttons) {
            if (std::string(b.GetText().getString()) == text) {
                return b;
            }
        }
        assert(false && "Not found button");
        return Button();
    }

}
