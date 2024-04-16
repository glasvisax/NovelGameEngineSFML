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

	MainMenu.SetBoxPosition(sf::Vector2f(Options.width / 2, Options.height / 2));
	MainMenu.SetFont(TextFont); // Ў–»‘“ ” ј«џ¬ј“№ ќЅя«ј“≈Ћ№Ќќ!!!!!!!!!!!!!
	MainMenu.AddButton(L"Play");
	MainMenu.AddButton(L"Options");
	MainMenu.AddButton(L"Exit");

	DialogBox.SetBackgroundShape(sf::Vector2f(Options.width - 100.0f, Options.height / 4), sf::Vector2f(50, Options.height - Options.height / 4));
	DialogBox.SetFont(TextFont); 
	DialogBox.SetCharacterSize(24.0f);

	AddSprite("milk_chan", "milk_chan.png", {50, 45});
	AddSprite("dornan", "dornan.png", { 50, 45 });

	// сначала добавл€ем спрайты потом показываем / пр€чем
	// ShowSprite("dornan");
	// ShowSprite("milk_chan");
	// HideSprite("milk_chan");
}

void SceneController::BeginPlay()
{
	assert(Game && "SceneController is nullptr");

	auto play_btn = MainMenu.GetButtonByText("Play");
	if (play_btn) { play_btn->BindOnClick(Game, &GameController::OnGameStart); }

	auto exit_btn = MainMenu.GetButtonByText("Exit");
	if (exit_btn) { exit_btn->BindOnClick(Game, &GameController::OnGameExit); }

	DialogBox.BindOnChoose(Game, &GameController::OnChoose);
	DialogBox.BindOnRenderEnd(Game, &GameController::OnWaitingClick);
	
}

void SceneController::Tick(float DeltaTime)
{
	Render();
}

void SceneController::Render()
{
	Window.draw(Background);
	if (!bPlay) {
		Window.draw(MainMenu);
	}
	else {
		for (auto& s : ShownSprites) {
			Window.draw(s->Sprite);
		}
		Window.draw(DialogBox);
	}
}

void SceneController::HandleInput(sf::Event e)
{
	if (!bPlay) {
		MainMenu.HandleInput(e, Window);
	}
	else {
		DialogBox.HandleInput(e, Window);
	}
}

void SceneController::ShowGame()
{
	//DialogBox.SetText(L"—ъешь ещЄ этих м€гких французских булок, да выпей же чаю —ъешь ещЄ этих м€гких французских булок, да выпей же чаю —ъешь ещЄ этих м€гких французских булок, да выпей же чаю");
	//DialogBox.SetChoices({ L"–оа", L"m8l", L"8th - ћоим богам, подобен ветер, что наполн€ет паруса завоеваний, и не дает поко€ жаждущим исканий, коварных норн расставленные сети",  L"сво", });
	bPlay = true;
}

sf::Texture SceneController::GetImageTexture(const std::string& file_name)
{
	sf::Texture texture;
	bool load = false;
	for (auto& texturePath : Options.content_folders)
	{

		std::string path = Root + texturePath + '/' + file_name;

		if (texture.loadFromFile(path))
		{
			load = true;
			break;
		}
	}

	assert(load && "Not Found Image");

	return texture;
}

void SceneController::AddSprite(const std::string& sprite_name, const std::string& file_name, const sf::Vector2u& position, bool user_scale, float scale)
{ 
	Sprites.emplace_back(sprite_name, GetImageTexture(file_name));
	float curr_scale = scale;
	sf::Vector2u curr_pos = position;
	auto& sprite = Sprites.back().Sprite;

	auto& bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2, bounds.height / 2);

	curr_pos.x = (curr_pos.x > 100) ? 100 : curr_pos.x;
	curr_pos.y = (curr_pos.y > 100) ? 100 : curr_pos.y;

	auto tpos = sf::Vector2f(
		static_cast<float>(Options.width * curr_pos.x) / 100.f,
		static_cast<float>(Options.height) - (static_cast<float>(Options.height * curr_pos.y) / 100.f));

	sprite.setPosition(tpos);

	if (!user_scale) {
		auto& size = sprite.getTexture()->getSize();
		auto win_max_wd = Options.width - (Options.width / 3);
		auto win_max_ht = Options.height - (Options.height / 3);
		if (size.x > win_max_wd || size.y > win_max_ht) {
			if (size.x > size.y) {
				curr_scale = win_max_wd / static_cast<float>(size.x);
			}
			else {
				curr_scale = win_max_ht / static_cast<float>(size.y);
			}
		}
	}
	sprite.scale(curr_scale, curr_scale);

}

void SceneController::ShowSprite(const std::string& sprite_name)
{
	if (Sprites.empty()) return;
	for (auto& sp : Sprites) {
		if (sp.Name == sprite_name) {
			ShownSprites.push_back(&sp);
			break;
		}
	}
}

void SceneController::HideSprite(const std::string& sprite_name)
{
	if (ShownSprites.empty()) return;
	for (auto it = ShownSprites.begin(); it != ShownSprites.end(); ++it) {
		if ((*it)->Name == sprite_name) { 
			it = ShownSprites.erase(it);
			break;
		}

	}
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

void SceneController::SetText(const std::wstring& text, const std::wstring& name )
{
	DialogBox.SetText(text, name);
}

void SceneController::SetChoices(const std::vector<std::wstring>& options)
{
	DialogBox.SetChoices(options);
}

void SceneController::SetBackgroundSprite(const std::string& file_name)
{
	BackgroundTexture = GetImageTexture(file_name);
	Background.setTexture(BackgroundTexture);

}

