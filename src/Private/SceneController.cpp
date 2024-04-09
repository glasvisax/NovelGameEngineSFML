#include "SceneController.h"
#include <cassert>
#include "GameController.h"


SceneController::SceneController(const std::string& root, const ConfigOptions& opts, sf::RenderWindow& window)
	: Root(root)
	, Options(opts)
	, Window(window)
{
	assert(TextFont.loadFromFile(Root + "/fonts/script.ttf") && "couldn't load font");

	BackgroundTexture.create(Options.width, Options.height);
	SetBackgroundColor(sf::Color::White);

	MainMenu.SetPosition(sf::Vector2f(Options.width / 2, (Options.height / 2)));
	MainMenu.AddButton("Play", TextFont, GUI::style::save, 20, sf::Vector2f(Options.width / 3, 50.0f));
	MainMenu.AddButton("Options", TextFont, GUI::style::save, 20, sf::Vector2f(Options.width / 3, 50.0f));
	MainMenu.AddButton("Exit", TextFont, GUI::style::save, 20, sf::Vector2f(Options.width / 3, 50.0f));

	DialogBox.SetBackgroundShape(sf::Vector2f(Options.width - 100.0f, Options.height / 5), 50.0f);
	DialogBox.SetTextFont(TextFont);
	DialogBox.SetPosition(sf::Vector2f(50, Options.height - Options.height / 5));
	DialogBox.SetCharacterName(L"Ћиза");
	DialogBox.SetCharacterSize(24.0f);
	//DialogBox.SetText(L"—ъешь ещЄ этих м€гких французских булок, да выпей же чаю —ъешь ещЄ этих м€гких французских булок, да выпей же чаю —ъешь ещЄ этих м€гких французских булок, да выпей же чаю");
}

void SceneController::SetGameController(GameController* game)
{
	this->Game = game;
}

void SceneController::Render() 
{
	Window.draw(Background);
	if (!bPlay) {
		Window.draw(MainMenu);
	} else {
		Window.draw(DialogBox);
		
	}
	
}

void SceneController::BeginPlay()
{

}

void SceneController::Tick(float DeltaTime)
{
	Render();
	if (bPlay)DialogBox.update();
}

void SceneController::HandleInput(sf::Event e)
{
	MainMenu.HandleInput(e, Window);
}

void SceneController::ShowGame()
{
	DialogBox.SetText(L"—ъешь ещЄ этих м€гких французских булок, да выпей же чаю —ъешь ещЄ этих м€гких французских булок, да выпей же чаю —ъешь ещЄ этих м€гких французских булок, да выпей же чаю");
	bPlay = true;
}

void SceneController::SetBackgroundColor(const sf::Color& color)
{
	sf::Vector2u backg_size = BackgroundTexture.getSize();
	unsigned int pixel_amnt = (backg_size.x * backg_size.y);

	sf::Uint32 digit_color = color.toInteger();
	sf::Uint32* pixels = new sf::Uint32[pixel_amnt];

	for (int i = 0; i < pixel_amnt; i++) {
		pixels[i] = digit_color;
	}

	BackgroundTexture.update(reinterpret_cast<sf::Uint8*>(pixels));
	Background.setTexture(BackgroundTexture);

	delete[] pixels;
}