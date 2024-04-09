#include "GUI/DialogBox.h"

namespace GUI 
{
    DialogBox::DialogBox()
    {
        Text.setColor(sf::Color::Black);
        CharacterName.setColor(sf::Color::Black);
    }
    void DialogBox::SetCharacterSize(float size)
    {
        size = size > 0 ? size : 1;
        Text.setCharacterSize(size);
        CharacterName.setCharacterSize(size + 3);
        LocateText();
    }

    void DialogBox::SetText(const std::wstring& text)
    {
        WideText = text;
    }

    void DialogBox::SetCharacterName(const std::wstring& name)
    {
        bHaveName = true;
        CharacterName.setString(name + L":"); 
        LocateText();

    }

    void DialogBox::SetTextFont(const sf::Font& font)
    {
        Text.setFont(font);
        CharacterName.setFont(font);
    }

    void DialogBox::SetTextColor(const sf::Color& text_color)
    {
        CharacterName.setColor(text_color);
        Text.setColor(text_color);
    }

    void DialogBox::SetPosition(sf::Vector2f pos)
    {
        Background.setPosition(pos);
        LocateText();
    }

    void DialogBox::SetBackgroundShape(const sf::Vector2f& background_size, float corner_radius, const sf::Color& background_color, float outline_thickness, const sf::Color& outline_color)
    {
        Background = thor::Shapes::roundedRect(background_size, corner_radius, background_color, outline_thickness, outline_color);
        BackgroundSize = background_size;
    }

    void DialogBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(Background, states);
        if(bHaveName) target.draw(CharacterName, states);
        target.draw(Text, states);
    }
    
    void DialogBox::update()
    {
        if (TextClock.getElapsedTime().asMilliseconds() > TimeToAddChar) {
            if (TextPos < WideText.size()) {
                std::wstring new_str = Text.getString().toWideString();
                new_str += WideText[TextPos];
                sf::String wrapped_str = WrapText(sf::String(new_str), BackgroundSize.x - 50, *Text.getFont(), Text.getCharacterSize(), false);
                Text.setString(wrapped_str);
                TextPos++;
            }
            TextClock.restart();
        }
    }

    void DialogBox::ToggleCharacter()
    {
        bHaveName = !bHaveName;
        LocateText();
    }

    void DialogBox::LocateText()
    {
        if (bHaveName) 
        {
            CharacterName.setPosition(Background.getPosition().x + 25.0f, Background.getPosition().y + 10.0f);
            Text.setPosition(CharacterName.getPosition().x, CharacterName.getPosition().y + 25.0f);
        }
        else 
        {
            Text.setPosition(Background.getPosition().x + 25.0f, Background.getPosition().y + 25.0f);
        }     
    }

    sf::String DialogBox::WrapText(sf::String string, unsigned width, const sf::Font& font, unsigned charicter_size, bool bold)
    {
        unsigned current_offset = 0;
        bool first_word = true;
        std::size_t word_begining = 0;
        std::size_t ssize = string.getSize();
        for (std::size_t pos(0); pos < ssize; ++pos) {
            auto current_char = string[pos];
            if (current_char == '\n') {
                current_offset = 0;
                first_word = true;
                continue;
            }
            else if (current_char == ' ') {
                word_begining = pos;
                first_word = false;
            }

            auto glyph = font.getGlyph(current_char, charicter_size, bold);
            current_offset += glyph.advance;

            if (!first_word && current_offset > width) {
                if (word_begining == pos) {
                    word_begining = pos + 1;
                    while (word_begining < ssize && string[word_begining] != ' ') {
                        word_begining++;
                    }
                }
                string.insert(pos, "\n-");
                pos = word_begining;
                first_word = true;
                current_offset = 0;
            }
        }

        return string;
    }
}
