#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <THOR/Shapes.hpp>
#include <THOR/Graphics.hpp>
#include <functional>

namespace GUI
{
    
    namespace style
    {
        enum 
        {
            none = 0,
            save = 1,
            cancel = 2,
            clean = 3,
        };
    };

    namespace state
    {
        enum
        {
            normal = 0,
            hovered = 1,
            clicked = 2
        };
    };

    class Button : public sf::Drawable
    {
        public:
            Button();
            Button(std::string s, sf::Font& font, sf::Vector2f position, sf::Uint32 style, sf::Vector2f size, unsigned int font_size);
            //Button(std::string s, sf::Font& font, sf::Vector2f position, sf::Uint32 style);

            ~Button();

            void setColorTextNormal(sf::Color text){m_textNormal = text;};
            void setColorTextHover(sf::Color text){m_textHover = text;};
            void setColorTextClicked(sf::Color text){m_textClicked = text;};
            void setColorNormal(sf::Color bgNormal){m_bgNormal = bgNormal;};
            void setColorHover(sf::Color bgHover){m_bgHover = bgHover;};
            void setColorClicked(sf::Color bgClicked){m_bgClicked = bgClicked;};
            void setBorderColor(sf::Color border){m_border = border;};
            void setBorderThickness(float t){m_borderThickness = t;};
            void setBorderRadius(float r){m_borderRadius = r;};
            void setPosition(sf::Vector2f position); // {m_position = position;}; код говна
            void setSize(unsigned int size);
            void setText(std::string s)
            {
                m_text.setString(s);
                //m_shadow = m_text;
            };
            void setStyle(sf::Uint32 style);
            void setFont(sf::Font& font);

            sf::Vector2f getPosition(){return m_position;};
            sf::Vector2f getDimensions(){return sf::Vector2f(m_button.getGlobalBounds().width, m_button.getGlobalBounds().height);};
            sf::Uint32 getState(){return m_btnstate;};

            void update(sf::Event& e, sf::RenderWindow& window);

            template <typename T>
            void bind_on_click(T* object, void (T::* method)()) 
            {
                m_OnClickListener = [object, method]() { (object->*method)(); };
            }

        private:

            void init();

            virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

        private:

            sf::Color m_bgNormal;
            sf::Color m_bgHover;
            sf::Color m_bgClicked;
            sf::Color m_textNormal;
            sf::Color m_textHover;
            sf::Color m_textClicked;
            sf::Color m_border;

            float m_borderThickness;
            float m_borderRadius;
            sf::Vector2f m_size;
            sf::Vector2f m_position;
            sf::Uint32 m_style;
            sf::Uint32 m_btnstate;

            sf::ConvexShape m_button;
            sf::Font m_font;
            unsigned int m_fontSize;
            sf::Text m_text;

            std::function<void()> m_OnClickListener = nullptr;
    };
};

