#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <Thor/Graphics.hpp>

#include <functional>

#include "Scene/SceneItem.h"

namespace GUI
{
    enum class ButtonStyle
    {
        None,
        Save,
        Cancel,
        Clean
    };

    enum class ButtonState 
    {
        Normal,
        Hovered,
        Clicked,
        Released
    };

    class Button : public SceneItem
    {
        public:
            Button() {};
            Button(const std::wstring& s, sf::Font& font, const sf::Vector2f& position, ButtonStyle style, const sf::Vector2f& size, unsigned int font_size);

            virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            virtual void HandleInput(sf::Event e, sf::RenderWindow& window) override;

            virtual void Update(sf::RenderWindow& window) override;

            void SetColorTextNormal(sf::Color text) { m_textNormal = text; };
            void SetColorTextHover(sf::Color text) { m_textHover = text; };
            void SetColorTextClicked(sf::Color text) { m_textClicked = text; };
            void SetColorNormal(sf::Color bgNormal) { m_bgNormal = bgNormal; };
            void SetColorHover(sf::Color bgHover) { m_bgHover = bgHover; };
            void SetColorClicked(sf::Color bgClicked) { m_bgClicked = bgClicked; };
            void SetBorderColor(sf::Color border) { m_border = border; };
            void SetBorderThickness(float t) { m_borderThickness = t; };
            void SetBorderRadius(float r) { m_borderRadius = r; };
            void SetPosition(const sf::Vector2f& position);
            void SetSize(unsigned int size);
            void SetText(const std::wstring& text) { m_text.setString(text); }
            void SetFont(const sf::Font& font) { m_text.setFont(font); }
            void SetStyle(ButtonStyle style);
            void SetOrigin(const sf::Vector2f& origin) { m_button.setOrigin(origin); }

            sf::Vector2f getPosition() { return m_position; };

            ButtonState getState() { return m_btnstate; };
            sf::Text GetText() const { return m_text; }

            template <typename T>
            void BindOnClick(T* object, void (T::* method)()) 
            {
                m_OnClickListener = [object, method]() { (object->*method)(); };
            }
           
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
            ButtonStyle m_style;
            ButtonState m_btnstate;

            sf::ConvexShape m_button;
            sf::Font m_font;
            unsigned int m_fontSize;
            sf::Text m_text;

            std::function<void()> m_OnClickListener;
            mutable bool bIsClicked = false;
    };
};

