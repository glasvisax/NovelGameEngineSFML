#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>

#include <string>
#include <functional>

namespace GUI
{
    class DialogBox : public sf::Drawable {

    public:
        DialogBox();

        void SetBackgroundShape(const sf::Vector2f& background_size,
            const sf::Vector2f& position,
            float corner_radius = 10.0f, 
            const sf::Color& background_color = sf::Color(128, 128, 128, 200),
            float outline_thickness = 0.0f,
            const sf::Color& outline_color = sf::Color::Black);

        void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

        void HandleInput(sf::Event& e, sf::RenderWindow& window);

    public:

        void SetCharacterSize(float size);

        void SetText(const std::wstring& text, const std::wstring& name = L"");

        void SetFont(const sf::Font& font);

        void SetTextColor(const sf::Color& text_color = sf::Color::Black);
        
        void SetTimeToAddChar(float time) { TimeToAddChar = time; }

    public:

        void SetChoices(const std::vector<std::wstring>& responses);

        int GetSelectedResponse() const { return CurrentResponse; }

    private:

        bool bChoise = false;
        sf::Font Font;
        mutable sf::Text Text;
        sf::Text CharacterName;
        std::wstring WideText;

        sf::ConvexShape Background;
        sf::Vector2f BackgroundSize;
        mutable sf::Clock TextClock;
        mutable size_t TextPos = 0;

        float TimeToAddChar = 30.0f;
        bool bHaveName = false;

    public:

        std::vector<std::wstring> Responses;
        mutable std::vector<sf::Text> ResponseTexts;
        int CurrentResponse = -1;

        template <typename T>
        void BindOnChoose(T* object, void (T::* method)(unsigned int))
        {
            OnChooseListener = [object, method](unsigned int value) { (object->*method)(value); };
        }

        template <typename T>
        void BindOnRenderEnd(T* object, void (T::* method)())
        {
            OnTextRenderEnd = [object, method]() { (object->*method)(); };
        }
    private:

        std::function<void(unsigned int)> OnChooseListener;
        std::function<void()> OnTextRenderEnd;
        int WrapText(sf::String& string, unsigned width, const sf::Font& font, unsigned charicter_size, bool bold) const;
        mutable bool bPrinting = false;
    };
}