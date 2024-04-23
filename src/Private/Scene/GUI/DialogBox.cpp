#include "Scene/GUI/DialogBox.h"

constexpr float Offset = 15.0f;
constexpr float CharacterOffset = 7.0f;

// костыли костылечки
// пришлось делать но думаю это ошибка в дизайне (€ не профи в этом всем)
static bool true_callback = false;
static bool true_select = false;

namespace GUI 
{
    DialogBox::DialogBox()
    {
        Text.setColor(sf::Color::Black);
        CharacterName.setColor(sf::Color::Black);
        Text.setCharacterSize(14.0f);
        CharacterName.setCharacterSize(14.0f + 5.0f);
    }

    void DialogBox::Draw(sf::RenderTarget& window, sf::RenderStates states)  const
    {
        window.draw(Background, states);

        if (!bChoise) {
            if (bHaveName) window.draw(CharacterName, states);
            window.draw(Text, states);
            if (true_callback) {
                OnTextRendered();
                true_callback = false;
            }
        }
        else {
            for (auto& s : ResponseTexts) {
                window.draw(s, states);
                if (!true_select) true_select = true;
            }
        }
    }

    void DialogBox::Update(sf::RenderWindow& window)
    {
        if (!bChoise && bPlayPrintAnim && TextPos < WideText.size() && TextClock.getElapsedTime().asMilliseconds() > TimeToAddChar) {
            std::wstring new_str = Text.getString().toWideString();
            new_str += WideText[TextPos];
            sf::String wrapped_str(new_str);
            WrapText(wrapped_str, BackgroundSize.x - Offset * 2, *Text.getFont(), Text.getCharacterSize(), false);
            Text.setString(wrapped_str);
            TextPos++;
            TextClock.restart();
            bPrinting = true;
            if (TextPos >= WideText.size()) {
                true_callback = true;
                bPrinting = false;
            }
        } 
    }

    void DialogBox::HandleInput(sf::Event e, sf::RenderWindow& window)
    {
        if (e.mouseButton.button == sf::Mouse::Left && e.type == sf::Event::MouseButtonReleased) {
            if (bChoise && true_select) {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                for (int i = 0; i < ResponseTexts.size(); ++i) {
                    sf::FloatRect bounds = ResponseTexts[i].getGlobalBounds();
                    if (bounds.contains(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y))) {
                        CurrentResponse = i;
                        OnChoiceSelected();
                        bChoise = false;
                        true_select = false;
                        break;
                    }
                }
            }
            else if (TextPos < WideText.size() && bPrinting) {
                SetFullText();
            }
        } else if (e.type == sf::Event::MouseMoved) {
            if (bChoise && true_select) {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                for (auto& s : ResponseTexts) {
                    sf::FloatRect bounds = s.getGlobalBounds();
                    if (bounds.contains(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y))) {
                        s.setFillColor(HoverColor);
                    }
                    else {
                        s.setFillColor(Text.getColor());
                    }
                }
            }
        }
    }

    void DialogBox::SetCharacterSize(float text_size, float name_size)
    {
        text_size = text_size > 0 ? text_size : 1;
        Text.setCharacterSize(text_size);
        if(name_size == -1) CharacterName.setCharacterSize(text_size);
        else CharacterName.setCharacterSize(name_size);

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
        bPrinting = false;
        true_select = false;
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
        if (!ResponseTexts.empty()) {
            for (auto& rt : ResponseTexts) {
                rt.setColor(text_color);
            }
        }
    }

    void DialogBox::SetTextHoverColor(const sf::Color& color)
    {
        HoverColor = color;
    }

    void DialogBox::SetBackgroundShape(const sf::Vector2f& background_size, const sf::Vector2f& position, float corner_radius,  const sf::Color& background_color, float outline_thickness, const sf::Color& outline_color)
    {
        Background = thor::Shapes::roundedRect(background_size, corner_radius, background_color, outline_thickness, outline_color);
        Background.setPosition(position);
        BackgroundSize = background_size;
    }

    void DialogBox::PlayPrintAnimation()
    {
        bPlayPrintAnim = true;
    }

    void DialogBox::StopPrintAnimation()
    {
        bPlayPrintAnim = false;
        SetFullText();
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

    void DialogBox::SetFullText()
    {
        TextPos = WideText.size();
        sf::String wrapped(WideText);
        WrapText(wrapped, BackgroundSize.x - (Offset * 2.0f), *Text.getFont(), Text.getCharacterSize(), false);
        Text.setString(wrapped);
        bPrinting = false;
        true_callback = true;
    }
    
}

