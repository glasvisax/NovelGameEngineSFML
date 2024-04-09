#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class Character 
{
    public:

        Character(const std::wstring& name, const sf::Texture& texture) :
            Name(name), Texture(texture) {}

        void SetSprite(const std::string& sprite_name) {
            if (Sprites.count(sprite_name) > 0) {
                CurrentSprite = Sprites[sprite_name];
            }
            else {
                // ��������� ������, ���� ������ �� ������
                // ...
            }
        }

        void AddSprite(const std::string& name, const sf::IntRect& rect) {
            Sprites[name] = sf::Sprite(Texture, rect);
        }

        void draw(sf::RenderWindow& window) const {
            window.draw(CurrentSprite);
        }

        // ... ������ ������ (��������, ��� ����������������, �������� � �.�.)

    private:
        std::wstring Name;
        sf::Texture Texture; 
        std::map<std::string, sf::Sprite> Sprites; 
        sf::Sprite CurrentSprite;
};