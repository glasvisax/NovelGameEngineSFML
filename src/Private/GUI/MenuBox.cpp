#include "GUI/MenuBox.h"
#include <cassert>
#include <algorithm> 
namespace GUI
{
    GUI::Button& MenuBox::AddButton(std::wstring text) 
    {
        BoxSize = sf::Vector2f(ButtonSize.x, BoxSize.y + ButtonSize.y + Space);

        Buttons.emplace_back(text, Font, sf::Vector2f(), ButtonStyle::Save, ButtonSize, FontSize);
        Buttons.back().SetOrigin(sf::Vector2f(ButtonSize.x / 2, ButtonSize.y / 2));
        LocateButtons();
        return Buttons.back();
    }


    void MenuBox::HandleInput(sf::Event& event, sf::RenderWindow& window)
    {
        for (auto& Button : Buttons)
        {
            Button.HandleInput(event, window);
        }
    }

    void MenuBox::draw(sf::RenderTarget& window, sf::RenderStates states) const
    {
        for (const auto& Button : Buttons)
        {
            window.draw(Button);
        }
    }

    Button* MenuBox::GetButtonByText(const std::string& text)
    {
        for (auto& btn : Buttons) {
            if (std::string(btn.GetText().getString()) == text) {
                return &btn;
            }
        }
        return nullptr;
    }

    void MenuBox::LocateButtons()
    {
        if (Buttons.empty()) return;

        float totalHeight = BoxSize.y - (Buttons.size() - 1) * Space;
        float startY = Position.y - totalHeight / 2.0f;

        for (size_t i = 0; i < Buttons.size(); ++i) {
            Buttons[i].SetPosition(sf::Vector2f(Position.x, startY + i * (ButtonSize.y + Space)));
        }
    }

}
