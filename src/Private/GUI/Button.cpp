#include <GUI/Button.h>
namespace GUI {
    Button::Button(const std::wstring& s, sf::Font& font, const sf::Vector2f& position, ButtonStyle style, const sf::Vector2f& size, unsigned int font_size)
    {
        m_position = position;
        m_btnstate = ButtonState::Normal;
        m_style = style;

        SetStyle(style);

        m_text.setString(s);
        m_text.setFont(font);
        m_text.setCharacterSize(font_size);
        m_text.setColor(m_textNormal);
        m_size = size;
        m_borderRadius = 5.f;
        m_borderThickness = 0.f;
        m_fontSize = font_size;

        m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
        m_button.setOrigin(m_size.x / 2, m_size.y / 2);
    }

    void Button::SetPosition(const sf::Vector2f& position)
    {
        m_position = position;
        m_button.setPosition(m_position);
        m_text.setPosition(sf::Vector2f(m_position.x - (m_text.getGlobalBounds().width / 2), m_position.y - (m_text.getGlobalBounds().height)));

    }
    void Button::SetSize(unsigned int size)
    {
        m_fontSize = size;
        m_text.setCharacterSize(m_fontSize);
        m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
        m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, (m_text.getGlobalBounds().height + m_text.getGlobalBounds().height) * 1.5f);
        m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
    }

    void Button::HandleInput(sf::Event& e, sf::RenderWindow& window)
    {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        sf::FloatRect bounds = m_button.getGlobalBounds();
        bool mouse_in_button = bounds.contains(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));

        if (mouse_in_button) {
            if (e.type == sf::Event::MouseMoved) {
                m_btnstate = ButtonState::Hovered;
                m_button.setFillColor(m_bgHover);
                m_text.setColor(m_textHover);
                return;
            }
            if (e.mouseButton.button == sf::Mouse::Left) {
                if (e.type == sf::Event::MouseButtonPressed) {
                    m_btnstate = ButtonState::Clicked;
                    m_button.setFillColor(m_bgClicked);
                    m_text.setColor(m_textClicked);
                    return;
                }
                if (e.type == sf::Event::MouseButtonReleased) {
                    m_btnstate = ButtonState::Released;
                    bIsClicked = true;
                    m_button.setFillColor(m_bgHover);
                    m_text.setColor(m_textHover);
                    return;
                }
            }
        }
        m_btnstate = ButtonState::Normal;
        m_button.setFillColor(m_bgNormal);
        m_text.setColor(m_textNormal);
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_button, states);
        target.draw(m_text, states);
        if (bIsClicked && m_OnClickListener != nullptr) {
            m_OnClickListener();
            bIsClicked = false;
        }
    }

    void Button::SetStyle(ButtonStyle style)
    {
        switch (style)
        {
        case ButtonStyle::None:
        {
            m_textNormal = sf::Color(255, 255, 255);
            m_textHover = sf::Color(255, 255, 255);
            m_textClicked = sf::Color(255, 255, 255);
            m_bgNormal = sf::Color(255, 255, 255, 100);
            m_bgHover = sf::Color(200, 200, 200, 100);
            m_bgClicked = sf::Color(150, 150, 150);
            m_border = sf::Color(255, 255, 255, 100);
        }
        break;

        case ButtonStyle::Save:
        {
            m_textNormal = sf::Color(255, 255, 255);
            m_textHover = sf::Color(255, 255, 255);
            m_textClicked = sf::Color(255, 255, 255);
            m_bgNormal = sf::Color(0, 255, 0, 100);
            m_bgHover = sf::Color(0, 200, 0, 100);
            m_bgClicked = sf::Color(0, 150, 0);
            m_border = sf::Color(0, 0, 0, 100);
        }
        break;

        case ButtonStyle::Cancel:
        {
            m_textNormal = sf::Color(255, 255, 255);
            m_textHover = sf::Color(255, 255, 255);
            m_textClicked = sf::Color(255, 255, 255);
            m_bgNormal = sf::Color(255, 0, 0, 100);
            m_bgHover = sf::Color(200, 0, 0, 100);
            m_bgClicked = sf::Color(150, 0, 0);
            m_border = sf::Color(255, 255, 255, 100);
        }
        break;

        case ButtonStyle::Clean:
        {
            m_textNormal = sf::Color(255, 255, 255);
            m_textHover = sf::Color(255, 255, 255);
            m_textClicked = sf::Color(255, 255, 255);
            m_bgNormal = sf::Color(0, 255, 255, 100);
            m_bgHover = sf::Color(0, 200, 200, 100);
            m_bgClicked = sf::Color(0, 150, 150);
            m_border = sf::Color(255, 255, 255, 100);
        }
        break;

        default:
            break;
        }
    }
}