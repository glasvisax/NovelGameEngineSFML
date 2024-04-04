#include <GUI/Button.h>

GUI::Button::Button()
{

}

GUI::Button::Button(std::string s, sf::Font& font, sf::Vector2f position, sf::Uint32 style, sf::Vector2f size, unsigned int font_size)
{
    //set position
    m_position = position;

    // Set initial state
    m_btnstate = GUI::state::normal;

    //set Button style
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

    // Set up text
    m_text.setString(s);
    m_text.setFont(font);
    m_text.setCharacterSize(font_size); // Set font size directly
    m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
    m_text.setColor(m_textNormal);

    // Set size and other defaults
    m_size = size;
    m_borderRadius = 5.f;
    m_borderThickness = 0.f;

    // Create button shape
    m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
    m_button.setOrigin(m_size.x / 2, m_size.y / 2); // Center origin

    // Set positions
    setPosition(position); // Use setPosition to update element positions
}

GUI::Button::~Button()
{
    //dtor
}

void GUI::Button::setPosition(sf::Vector2f position)
{
    m_position = position;

    // Update the button shape's position
    m_button.setPosition(m_position);

    // Update the text position (centered within the button)
    sf::Vector2f textPosition = sf::Vector2f(
        m_position.x,
        m_position.y - m_text.getGlobalBounds().height / 2
    );
    m_text.setPosition(textPosition);

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
    //set Button style
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

void GUI::Button::setFont(sf::Font& font)
{
    m_text.setFont(font);
}

void GUI::Button::update(sf::Event& e, sf::RenderWindow& window)
{
    /*
    //perform updates for settings from user
    switch(m_style)
    {
        case GUI::style::none:
        {
            m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
            m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
            m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
            m_button.setPosition(m_position);
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_text.getGlobalBounds().height/2);
            m_text.setPosition(textPosition);
            m_text.setColor(m_textNormal);
        }
        break;

        case GUI::style::save:
        {
            m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
            m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
            m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
            m_button.setPosition(m_position);
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_text.getGlobalBounds().height/2);
            m_text.setPosition(textPosition);
            m_text.setColor(m_textNormal);
        }
        break;

        case GUI::style::cancel:
        {
           m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
            m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
            m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
            m_button.setPosition(m_position);
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_text.getGlobalBounds().height/2);
            m_text.setPosition(textPosition);
            m_text.setColor(m_textNormal);
        }
        break;

        case GUI::style::clean:
        {
            m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
            m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
            m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
            m_button.setPosition(m_position);
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_text.getGlobalBounds().height/2);
            m_text.setPosition(textPosition);
            m_text.setColor(m_textNormal);
        }
        break;

        default:
            break;
    }
    */

    //perform updates for user mouse interactions
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
                if (m_OnClickListener != nullptr) m_OnClickListener();
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
                m_btnstate = GUI::state::hovered;
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
    }
}

void GUI::Button::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    switch(m_style)
    {
        case GUI::style::none:
        {
            target.draw(m_button, states);
            target.draw(m_text, states);
        }
        break;

        case GUI::style::save:
        {
            target.draw(m_button, states);
            target.draw(m_text, states);
        }
        break;

        case GUI::style::cancel:
        {
            target.draw(m_button, states);
            target.draw(m_text, states);
        }
        break;

        case GUI::style::clean:
        {
            target.draw(m_button, states);
            target.draw(m_text, states);
        }
        break;

        default:
            break;
    }
}
