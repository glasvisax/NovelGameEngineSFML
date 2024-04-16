#include "GUI/DialogBox.h"

constexpr float Offset = 15.0f;
constexpr float CharacterOffset = 7.0f;


namespace GUI 
{
    DialogBox::DialogBox()
    {
        Text.setColor(sf::Color::Black);
        CharacterName.setColor(sf::Color::Black);
        Text.setCharacterSize(14.0f);
        CharacterName.setCharacterSize(14.0f + 3.0f);
    }
    void DialogBox::SetCharacterSize(float size)
    {
        size = size > 0 ? size : 1;
        Text.setCharacterSize(size);
        CharacterName.setCharacterSize(size + 3);

        if ((!Text.getString().toWideString().empty() || !Text.getString().toWideString().empty()) && !bChoise) {
            SetText(Text.getString().toWideString(), CharacterName.getString().toWideString());
        }
        if (!ResponseTexts.empty() && bChoise) {
            SetChoices(Responses);
        }
    }

    void DialogBox::SetText(const std::wstring& text, const std::wstring& name)
    {
        bChoise = false;
        if (name.empty()) {
            bHaveName = false;
            CharacterName.setString(name);
            Text.setPosition(Background.getPosition().x + Offset, Background.getPosition().y + Offset);
        } else {
            bHaveName = true;
            CharacterName.setString(name + L":");
            CharacterName.setPosition(Background.getPosition().x + Offset, Background.getPosition().y + Offset);
            Text.setPosition(CharacterName.getPosition().x, CharacterName.getPosition().y + CharacterName.getCharacterSize() + CharacterOffset);
        }
        TextPos = 0;
        Text.setString(L"");
        WideText = text;
        TextClock.restart();
    }

    void DialogBox::SetFont(const sf::Font& font)
    {
        Text.setFont(font);
        CharacterName.setFont(font);
        if ((!Text.getString().toWideString().empty() || !Text.getString().toWideString().empty()) && !bChoise) {
            SetText(Text.getString().toWideString(), CharacterName.getString().toWideString());
        }
        if (!ResponseTexts.empty() && bChoise) {
            SetChoices(Responses);
        }
    }

    void DialogBox::SetTextColor(const sf::Color& text_color)
    {
        CharacterName.setColor(text_color);
        Text.setColor(text_color);
    }

    void DialogBox::SetBackgroundShape(const sf::Vector2f& background_size, const sf::Vector2f& position, float corner_radius,  const sf::Color& background_color, float outline_thickness, const sf::Color& outline_color)
    {
        Background = thor::Shapes::roundedRect(background_size, corner_radius, background_color, outline_thickness, outline_color);
        Background.setPosition(position);
        BackgroundSize = background_size;
    }


    void DialogBox::draw(sf::RenderTarget& window, sf::RenderStates states)  const
    {
        window.draw(Background, states);

        if (!bChoise) {
            if (bHaveName) window.draw(CharacterName, states);
            
            if (TextPos < WideText.size() && TextClock.getElapsedTime().asMilliseconds() > TimeToAddChar) {
                bPrinting = true;
                std::wstring new_str = Text.getString().toWideString();
                new_str += WideText[TextPos];
                sf::String wrapped_str(new_str);
                WrapText(wrapped_str, BackgroundSize.x - Offset * 2, *Text.getFont(), Text.getCharacterSize(), false);
                Text.setString(wrapped_str);
                TextPos++;
                TextClock.restart();
                if (TextPos >= WideText.size()) {
                    OnTextRenderEnd();
                    bPrinting = false;
                }
            }
            
            window.draw(Text, states);

        } else {
            sf::Vector2i mousePos = sf::Mouse::getPosition(static_cast<sf::RenderWindow&>(window));
            for (auto& s : ResponseTexts) {
                sf::FloatRect bounds = s.getGlobalBounds();

                if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    s.setFillColor(sf::Color::White);
                }
                else {
                    s.setFillColor(sf::Color::Black);
                }
                window.draw(s, states);
            }
        }
    }

    void DialogBox::HandleInput(sf::Event& e, sf::RenderWindow& window)
    {

        if (e.mouseButton.button == sf::Mouse::Left && e.type == sf::Event::MouseButtonReleased) {
            if (bChoise)
            {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(static_cast<sf::RenderWindow&>(window));
                for (int i = 0; i < ResponseTexts.size(); ++i) {
                    sf::FloatRect bounds = ResponseTexts[i].getGlobalBounds();
                    if (bounds.contains(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y))) {
                        OnChooseListener(i);
                        break;
                    }
                }

            } else if(TextPos < WideText.size() && bPrinting) {
                TextPos = WideText.size();
                sf::String wrapped(WideText);
                WrapText(wrapped, BackgroundSize.x - (Offset * 2.0f), *Text.getFont(), Text.getCharacterSize(), false);
                Text.setString(wrapped);
                bPrinting = false;
                OnTextRenderEnd();
            }
        }
    }

    int DialogBox::WrapText(sf::String& string, unsigned width, const sf::Font& font, unsigned charicter_size, bool bold) const
    {
        unsigned current_offset = 0;

        bool first_word = true;
        std::size_t word_begining = 0;
        std::size_t ssize = string.getSize();
        int newline_count = 0;
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
                pos = word_begining;
                newline_count++;
                string[pos] = '\n';
                first_word = true;
                current_offset = 0;
            }
        }

        return newline_count;
    }


    void DialogBox::SetChoices(const std::vector<std::wstring>& responses) 
    {
        bChoise = true;
        Responses = responses;
        ResponseTexts.clear();
        int newline_num = 0;
        for (int i = 0; i < responses.size(); ++i) {
            sf::Text text;
            sf::Vector2f position;
            text.setFont(*Text.getFont());
            text.setCharacterSize(Text.getCharacterSize());
            text.setColor(Text.getColor());
            sf::String wrapped(std::to_wstring(i + 1) + L". " + responses[i]);
            if (ResponseTexts.empty()) 
            {
                position = sf::Vector2f(Background.getPosition().x + Offset, Background.getPosition().y + Offset);
            }
            else {
                position = sf::Vector2f(ResponseTexts.back().getPosition().x, ResponseTexts.back().getPosition().y + (Text.getCharacterSize() + CharacterOffset) * (newline_num + 1));
            }

            newline_num = WrapText(wrapped, BackgroundSize.x - Offset * 2, *Text.getFont(), Text.getCharacterSize(), false);
            text.setPosition(position);
            text.setString(wrapped);

            ResponseTexts.push_back(text);
        } 
    }
}

