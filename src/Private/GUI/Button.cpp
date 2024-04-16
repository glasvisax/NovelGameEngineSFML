#include <GUI/Button.h>

GUI::Button::Button(std::wstring s, sf::Font& font, sf::Vector2f position, sf::Uint32 style, sf::Vector2f size, unsigned int font_size)
{

    m_position = position;

    m_btnstate = GUI::state::normal;

    m_style = style;

    switch (m_style)
    {
    case GUI::style::none:
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

    case GUI::style::save:
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

    case GUI::style::cancel:
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

    case GUI::style::clean:
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

    m_text.setString(s);
    m_text.setFont(font);
    m_text.setCharacterSize(font_size); 
    m_text.setColor(m_textNormal);
    m_size = size;
    m_borderRadius = 5.f;
    m_borderThickness = 0.f;
    m_fontSize = font_size;

    m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
    m_button.setOrigin(m_size.x / 2, m_size.y / 2); // Center origin

}

void GUI::Button::setPosition(const sf::Vector2f& position)
{
    m_position = position;

    m_button.setPosition(m_position);

    m_text.setPosition(sf::Vector2f(m_position.x - (m_text.getGlobalBounds().width/2), m_position.y - (m_text.getGlobalBounds().height)));

}
void GUI::Button::setSize(unsigned int size)
{
    m_fontSize = size;
    m_text.setCharacterSize(m_fontSize);
    m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
    m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, (m_text.getGlobalBounds().height + m_text.getGlobalBounds().height) * 1.5f);
    m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
}

void GUI::Button::setStyle(sf::Uint32 style)
{
    m_style = style;

    switch(m_style)
    {
        case GUI::style::none:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(255,255,255,100);
            m_bgHover = sf::Color(200,200,200,100);
            m_bgClicked = sf::Color(150,150,150);
            m_border = sf::Color(255,255,255,100);
        }
        break;

        case GUI::style::save:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(0,255,0,100);
            m_bgHover = sf::Color(0,200,0,100);
            m_bgClicked = sf::Color(0,150,0);
            m_border = sf::Color(0,0,0,100);
        }
        break;

        case GUI::style::cancel:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(255,0,0,100);
            m_bgHover = sf::Color(200,0,0,100);
            m_bgClicked = sf::Color(150,0,0);
            m_border = sf::Color(255,255,255,100);
        }
        break;

        case GUI::style::clean:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(0,255,255,100);
            m_bgHover = sf::Color(0,200,200,100);
            m_bgClicked = sf::Color(0,150,150);
            m_border = sf::Color(255,255,255,100);
        }
        break;

        default:
            break;
    }
}


void GUI::Button::update(sf::Event& e, sf::RenderWindow& window)
{
    sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);

    bool mouseInButton =    m_mousePosition.x >= m_button.getPosition().x - m_button.getGlobalBounds().width/2
                            && m_mousePosition.x <= m_button.getPosition().x + m_button.getGlobalBounds().width/2
                            && m_mousePosition.y >= m_button.getPosition().y - m_button.getGlobalBounds().height/2
                            && m_mousePosition.y <= m_button.getPosition().y + m_button.getGlobalBounds().height/2;

    if(e.type == sf::Event::MouseMoved)
    {
        if(mouseInButton)
        {
            m_btnstate = GUI::state::hovered;
        }

        else
        {
            m_btnstate = GUI::state::normal;
        }
    }

    if (e.type == sf::Event::MouseButtonPressed)
    {
        switch(e.mouseButton.button)
        {
        case sf::Mouse::Left:
        {
            if(mouseInButton)
            {
                m_btnstate = GUI::state::clicked;
                
            }

            else
            {
                m_btnstate = GUI::state::normal;
            }
        }
        break;
        }
    }

    if (e.type == sf::Event::MouseButtonReleased)
    {
        switch(e.mouseButton.button)
        {
        case sf::Mouse::Left:
        {
            if(mouseInButton)
            {
                m_btnstate = GUI::state::released;
            }

            else
            {
                m_btnstate = GUI::state::normal;
            }
        }

        }
    }

    switch(m_btnstate)
    {
    case GUI::state::normal:
    {
        m_button.setFillColor(m_bgNormal);
        m_text.setColor(m_textNormal);
    }
    break;

    case GUI::state::hovered:
    {
        m_button.setFillColor(m_bgHover);
        m_text.setColor(m_textHover);
    }
    break;

    case GUI::state::clicked:
    {
        m_button.setFillColor(m_bgClicked);
        m_text.setColor(m_textClicked);
    }
    break;
    case GUI::state::released:
    {
        bIsClicked = true;
        m_button.setFillColor(m_bgHover);
        m_text.setColor(m_textHover);
    }
    break;
    }
}

void GUI::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_button, states);
    target.draw(m_text, states);
    bool check = bIsClicked && m_OnClickListener != nullptr;
    if (check)
    { 
        m_OnClickListener(); 
        bIsClicked = false;
    }
    target.draw(&point, 1, sf::Points);
}
