#include "Scene/SceneController.h"
#include <Thor/Animations.hpp>

#include <cassert>
#include <string>
#include <filesystem>

// êîñòûëü :)
std::vector<SceneSprite*> to_unshow;

SceneController::SceneController(const std::string& root, const ConfigOptions& opts, sf::RenderWindow& window)
	: Root(root)
	, Options(opts)
	, Window(window)
{
	assert(TextFont.loadFromFile(Root + "/fonts/script.ttf") && "couldn't load font");

	sf::Texture default_tt;
	default_tt.create(Options.width, Options.height);
	SetTextureColor(sf::Color::White, default_tt);
	Backgrounds.emplace_back("default", default_tt);

	AddBackground("2", "2.png");

	Background = &Backgrounds.front();

	MainMenu.SetBoxPosition(sf::Vector2f(Options.width / 2, Options.height / 2));
	MainMenu.SetFont(TextFont); // ØÐÈÔÒ ÓÊÀÇÛÂÀÒÜ ÎÁßÇÀÒÅËÜÍÎ!!!!!!!!!!!!!
	MainMenu.AddButton(L"Play");
	MainMenu.AddButton(L"Options");
	MainMenu.AddButton(L"Exit");

	DialogBox.SetBackgroundShape(sf::Vector2f(Options.width - 100.0f, Options.height / 4), sf::Vector2f(50, Options.height - Options.height / 4), 2.0f, sf::Color::Black, 5.f, sf::Color(32.f, 115.f, 49.f));
	DialogBox.SetFont(TextFont); 
	DialogBox.SetCharacterSize(24.0f);
	DialogBox.SetTextColor(sf::Color(32.f, 115.f, 49.f));

	AddSprite("milk_chan", "milk_chan.png", {50, 45});
	AddSprite("dornan", "dornan.png", { 50, 49 });

	AddAudioChannel("channel_0", "1.ogg");
	AddAudioChannel("channel_1", "2.mp3");
}

void SceneController::StartScene()
{
	bStart = true;
	auto play_btn = MainMenu.GetButtonByText("Play");
	if (play_btn) { play_btn->BindOnClick(this, &SceneController::ToNextFrame); }

	auto exit_btn = MainMenu.GetButtonByText("Exit");
	if (exit_btn) { exit_btn->BindOnClick(this, &SceneController::Exit); }

	DialogBox.BindOnChoose(this, &SceneController::OnChoiceSelected);
	DialogBox.BindOnRenderEnd(this, &SceneController::WaitNextInput);
}

void SceneController::HandleInput(sf::Event e)
{
	if (e.mouseButton.button == sf::Mouse::Left && e.type == sf::Event::MouseButtonReleased && bWaitNextInput){
		ToNextFrame();
		bWaitNextInput = false;
		return;
	}

	if (!bPlay) {
		MainMenu.HandleInput(e, Window);
	}
	else {
		DialogBox.HandleInput(e, Window);
	}
}

void SceneController::StartGame()
{
	bPlay = true;
}

void SceneController::Tick(float DeltaTime)
{
	if (FormerBackground) FormerBackground->update();
	Background->update();
	if (bPlay) {
		for (auto& s : ShownSprites) {
			s->update();
		}
		DialogBox.update(Window);
	}

	if (!to_unshow.empty()) {
		for (auto& us : to_unshow) {
			HideSprite(us->GetName(), false);
		}
		to_unshow.clear();
	}
	Render();
}

void SceneController::Exit()
{
	Window.close();
}

void SceneController::ToNextFrame()
{
	Game->Next();
}

void SceneController::WaitNextInput()
{
	bWaitNextInput = true;
}

void SceneController::OnChoiceSelected(unsigned int choice)
{
	Game->SetCurrentChoice(choice);
	ToNextFrame();
}

void SceneController::Render()
{
	Window.clear();
	if(FormerBackground) Window.draw(*FormerBackground);
	Window.draw(*Background);

	if (!bPlay) {
		Window.draw(MainMenu);
	}
	else {
		for (auto& s : ShownSprites) {
			Window.draw(*s);
		}
		Window.draw(DialogBox);
	}
	Window.display();
}

sf::Texture SceneController::GetImageTexture(const std::string& file_name)
{
	sf::Texture texture;
	std::string path = GetFilePath(file_name);
	assert(texture.loadFromFile(path) && "Not Found Image");
	return texture;
}

std::string SceneController::GetFilePath(const std::string& file_name)
{
	for (auto& folder : Options.content_folders)
	{
		std::string path = Root + folder + '/' + file_name;

		if (std::filesystem::exists(path))
		{
			return path;
		}
	}

	assert(false && "File not found");
	return "";
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

void SceneController::AddBackground(const std::string& bg_name, const std::string& file_name)
{
	Backgrounds.emplace_back(bg_name, GetImageTexture(file_name));
	auto& sprite = Backgrounds.back().Sprite;
	sprite.setPosition(sf::Vector2f(0.0f, 0.0f));
}

void SceneController::ShowBackground(const std::string& bg_name, bool fade_anim)
{
	if (Backgrounds.empty()) return;
	for (auto& bg : Backgrounds) {
		if (bg.Name == bg_name) {
			if (fade_anim) {
				FormerBackground = Background;
				Background = &bg;
				Background->OnFadeInEnd = [this]() mutable -> void { FormerBackground = nullptr; };
				Background->PlayFadeIn();
			} else {
				Background = &bg;
			}
		}
	}
}

void SceneController::SetBackgroundColor(const sf::Color& color, bool fade_anim)
{
	static sf::Color prev_color = color;
	auto& bg = Backgrounds.front();
	if (prev_color != color) { 
		SetTextureColor(color, bg.Texture); 
		prev_color = color;
	}

	if (fade_anim) {
		FormerBackground = Background;
		Background = &bg;
		Background->OnFadeInEnd = [this]() mutable -> void { FormerBackground = nullptr; };
		Background->PlayFadeIn();
	}
	else {
		Background = &bg;
	}
}

void SceneController::ShowSprite(const std::string& sprite_name, bool fade_anim)
{
	if (Sprites.empty()) return;
	for (auto& sp : Sprites) {
		if (sp.Name == sprite_name) {

			ShownSprites.push_back(&sp);
			if (fade_anim) { 
				sp.PlayFadeIn(); 
				sp.PlayMoveAnimation(sf::Vector2f(100.f, 200.f), 30.f);
			}

			break;
		}
	}
}

void SceneController::HideSprite(const std::string& sprite_name, bool fade_anim)
{
	if (ShownSprites.empty()) return;

	auto it = std::find_if(ShownSprites.begin(), ShownSprites.end(), [&](const auto& sprite) { return sprite->Name == sprite_name; });
	if (it == ShownSprites.end()) return;
	if (fade_anim) {
		(*it)->PlayFadeOut();
		(*it)->OnFadeOutEnd = [this, it]() mutable { to_unshow.push_back(*it); };
	} else {
		ShownSprites.erase(it);
	}
}

void SceneController::SetTextureColor(const sf::Color& color, sf::Texture& texture)
{
	sf::Vector2u backg_size = texture.getSize();
	unsigned int pixel_amnt = (backg_size.x * backg_size.y);

	sf::Uint32 digit_color = color.toInteger();
	sf::Uint32* pixels = new sf::Uint32[pixel_amnt];

	for (int i = 0; i < pixel_amnt; i++) {
		pixels[i] = digit_color;
	}

	texture.update(reinterpret_cast<sf::Uint8*>(pixels));

	delete[] pixels;
}

void SceneController::SetText(const std::wstring& text, bool print_anim, const std::wstring& name)
{
	DialogBox.SetText(text, name);
	if (print_anim) DialogBox.PlayPrintAnimation();
	else DialogBox.StopPrintAnimation();
}

void SceneController::SetChoices(const std::vector<std::wstring>& options)
{
	DialogBox.SetChoices(options);
}

void SceneController::SetTextFont(const std::string& file_name)
{
	sf::Font font;
	if (!font.loadFromFile(file_name)) return;

	DialogBox.SetFont(font);
}

void SceneController::SetTextCharacterSize(float text_size, float name_size)
{
	DialogBox.SetCharacterSize(text_size, name_size);
}

void SceneController::SetTextColor(const sf::Color& color)
{
	DialogBox.SetTextColor(color);
}

void SceneController::SetTextHoverColor(const sf::Color& color)
{
	DialogBox.SetTextHoverColor(color);
}

void SceneController::AddAudioChannel(const std::string& name, const std::string& file_name) {
	if (AudioChannels.find(name) == AudioChannels.end()) {
		std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
		if (music->openFromFile(GetFilePath(file_name))) {
			AudioChannels[name] = music;
		}
	}
}

void SceneController::PlayAudioChannel(const std::string& name, bool loop) {
	if (AudioChannels.find(name) != AudioChannels.end()) {
		AudioChannels[name]->setLoop(loop);
		AudioChannels[name]->play();
	}
}

void SceneController::StopAudioChannel(const std::string& name) {
	if (AudioChannels.find(name) != AudioChannels.end()) {
		AudioChannels[name]->stop();
	}
}

void SceneController::SetAudioChannelVolume(const std::string& name, float volume) {
	if (AudioChannels.find(name) != AudioChannels.end()) {
		AudioChannels[name]->setVolume(volume);
	}
}

void SceneController::ReloadAudioChannel(const std::string& name, const std::string& file_name) {
	if (AudioChannels.find(name) != AudioChannels.end()) {
		AudioChannels[name]->stop();
		if (AudioChannels[name]->openFromFile(GetFilePath(file_name))) {
			AudioChannels[name]->play();
		}
	}
}