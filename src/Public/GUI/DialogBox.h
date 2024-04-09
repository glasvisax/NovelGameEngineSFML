#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <string>

namespace GUI
{
    class DialogBox : public sf::Drawable {
    public:

        DialogBox();
    public:

        void SetCharacterSize(float size);

        void SetText(const std::wstring& text);

        void SetCharacterName(const std::wstring& name);

        void SetTextFont(const sf::Font& font);

        void SetTextColor(const sf::Color& text_color = sf::Color::Black);

        void SetPosition(sf::Vector2f pos);
        
        void SetBackgroundShape(const sf::Vector2f& background_size,
            float corner_radius = 10.0f,
            const sf::Color& background_color = sf::Color(128, 128, 128, 200),
            float outline_thickness = 0.0f,
            const sf::Color& outline_color = sf::Color::Black);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void update();

        void ToggleCharacter();
        
        void SetTimeToAddChar(float time) { TimeToAddChar = time; }
    private:

        sf::Font Font;
        sf::Text Text;
        sf::Text CharacterName;
        std::wstring WideText;

        sf::ConvexShape Background;
        sf::Vector2f BackgroundSize;
        sf::Clock TextClock;
        size_t TextPos = 0;

        float TimeToAddChar = 30.0f;
        bool bHaveName = false;

    private:

        void LocateText();
        sf::String WrapText(
            sf::String string, 
            unsigned width, 
            const sf::Font& font, 
            unsigned charicterSize, 
            bool bold );
    };
}