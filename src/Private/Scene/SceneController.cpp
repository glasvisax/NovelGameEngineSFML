#include "Scene/SceneController.h"
#include <Thor/Animations.hpp>

#include <cassert>
#include <string>
#include <filesystem>

SceneController::SceneController(const std::string& root, const ConfigOptions& opts, sf::RenderWindow& window)
	: Root(root)
	, Options(opts)
	, Window(window)
{
	std::string font_file = GetFilePath(opts.main_font);
	assert(TextFont.loadFromFile(font_file) && "couldn't load font");

	Backgrounds.reserve(opts.backgrounds_amount);
	Menus.reserve(opts.menus_amount);
	Sprites.reserve(opts.sprites_amount);

	sf::Texture default_tt;
	default_tt.create(Options.width, Options.height);
	SetTextureColor(default_tt, sf::Color::White);
	Backgrounds.emplace_back(default_tt);
	Backgrounds.front().ItemName = "default";
	Background.second = &Backgrounds.front();
}

void SceneController::StartScene()
{
	DialogBox.OnChoiceSelected = ToNextFrameEvent;
	DialogBox.OnTextRendered = [this]() mutable -> void { bWaitNextInput = true; };
	GlobalHandler();
}

void SceneController::GlobalHandler()
{
	while (Window.isOpen()) {

		sf::Event event;
		while (Window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				Window.close();
			}
			HandleInput(event);
		}

		Update();
		Render();
	}
}

void SceneController::Exit()
{
	Window.close();
}

void SceneController::HandleInput(sf::Event e)
{
	for (auto& m : Menus) {
		if (m.bShowing) {
			m.HandleInput(e, Window);
			return;
		}
	}

	for (auto& i : Sprites) {
		if (i.bShowing) {
			i.HandleInput(e, Window);
		}
	}

	if (DialogBox.bShowing) {
		DialogBox.HandleInput(e, Window);
	}

	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
		if (EscapePressEvent) EscapePressEvent();
	}

	if (e.mouseButton.button == sf::Mouse::Left && e.type == sf::Event::MouseButtonReleased && bWaitNextInput) {
		assert(ToNextFrameEvent && "ToNextFrameEvent must be binded");
		ToNextFrameEvent();
		bWaitNextInput = false;

	}
}

void SceneController::Update()
{
	if (Background.first) Background.first->Update(Window);
	Background.second->Update(Window);

	for (auto& i : Menus) {
		if (i.bShowing) {
			i.Update(Window);
			return;
		}
	}

	for (auto& i : Sprites) {
		if (i.bShowing) {
			i.Update(Window); 
		}
	}

	if (DialogBox.bShowing) { 
		DialogBox.Update(Window); 
	}
}

void SceneController::Render()
{
	Window.clear(); 

	if (Background.first) Window.draw(*Background.first);
	Window.draw(*Background.second);

	for (auto& i : Sprites) {
		if (i.bShowing) {
			Window.draw(i);
		}
	}

	if (DialogBox.bShowing) {
		Window.draw(DialogBox);
	}

	for (auto& i : Menus) {
		if (i.bShowing) {
			Window.draw(i);
		}
	}

	Window.display();
}

void SceneController::AddBackground(const std::string& bg_name, const std::string& file_name)
{
	Backgrounds.emplace_back(GetImageTexture(file_name));
	Backgrounds.back().ItemName = bg_name;

	auto& sprite = Backgrounds.back().GetSFMLSprite();
	sprite.setPosition(sf::Vector2f(0.0f, 0.0f));
}

void SceneController::ShowBackground(const std::string& bg_name, float fade_time)
{
	if (Backgrounds.empty()) return;
	for (auto& bg : Backgrounds) {
		if (bg.ItemName == bg_name) {

			if (fade_time > 0) {
				Background.first = Background.second;
				Background.second = &bg;

				Background.second->PlayFadeIn();
				Background.second->OnFadeInEnd = [this]() mutable -> void { Background.first = nullptr; };
			} else {
				Background.first = nullptr;
				Background.second = &bg;
			}
		}
	}
}

void SceneController::SetBackgroundColor(const ColorWrapper& color, float fade_time)
{
	SceneSprite& bg = Backgrounds.front();
	SetTextureColor(bg.GetSFMLTexture(), color.ToSFMLColor());

	if (fade_time > 0) {
		Background.first = Background.second;
		Background.second = &bg;
		Background.second->OnFadeInEnd = [this]() mutable -> void { Background.first = nullptr; };
		Background.second->PlayFadeIn();
	}
	else {
		Background.second = &bg;
	}
}

GUI::MenuBox& SceneController::AddMenu(const sf::Vector2f& pos, const std::vector<std::wstring>& buttons, std::string name)
{
	Menus.emplace_back();
	auto& curr_menu = Menus.back();

	auto tpos = sf::Vector2f(
		static_cast<float>(Options.width * pos.x) / 100.f,
		static_cast<float>(Options.height) - (static_cast<float>(Options.height * pos.y) / 100.f));
	curr_menu.SetBoxPosition(tpos);
	curr_menu.SetFont(TextFont); 
	curr_menu.ItemName = name;
	for (auto& bt : buttons) {
		curr_menu.AddButton(bt);
	}
	return curr_menu;
}

void SceneController::ShowMenu(const std::string& name)
{
	for (auto& m : Menus) {
		if (m.ItemName == name) {
			m.bShowing = true;
		}
		else {
			m.bShowing = false;
		}
	}
}

void SceneController::HideMenu(const std::string& name)
{
	for (auto& m : Menus) {
		if (m.ItemName == name) {
			m.bShowing = false;
			break;
		}
	}
}

void SceneController::AddSprite(const std::string& sprite_name, const std::string& file_name, const sf::Vector2f& position, float scale)
{
	Sprites.emplace_back(GetImageTexture(file_name));
	Sprites.back().ItemName = sprite_name;
	float curr_scale = scale;
	auto& sprite = Sprites.back().GetSFMLSprite();

	auto& bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2, bounds.height / 2);

	auto tpos = sf::Vector2f(
		static_cast<float>(Options.width * position.x) / 100.f,
		static_cast<float>(Options.height) - (static_cast<float>(Options.height * position.y) / 100.f));

	sprite.setPosition(tpos);

	if (curr_scale != 1.0f) {
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

void SceneController::ShowSprite(const std::string& sprite_name, float fade_time)
{
	if (Sprites.empty()) return;
	for (auto& sp : Sprites) {
		if (sp.ItemName == sprite_name) {
			sp.bShowing = true;
			if (fade_time > 0.0f) {
				sp.PlayFadeIn(fade_time);
			}
			break;
		}
	}
}

void SceneController::HideSprite(const std::string& sprite_name, float fade_time)
{
	if (Sprites.empty()) return;

	for (auto& sp : Sprites) {
		if (sp.ItemName == sprite_name) {
			sp.bShowing = false;
			if (fade_time > 0.0f) {
				sp.PlayFadeOut();
				sp.OnFadeOutEnd = [&sp]() mutable -> void { sp.bShowing = false; };
			}
			break;
		}
	}

}

void SceneController::SetSpritePosition(const std::string& sprite_name, sf::Vector2f pos)
{
	if (Sprites.empty()) return;

	for (auto& sp : Sprites) {
		if (sp.ItemName == sprite_name) {
			if (sp.bShowing) {

				auto tpos = sf::Vector2f(
					static_cast<float>(Options.width * pos.x) / 100.f,
					static_cast<float>(Options.height) - (static_cast<float>(Options.height * pos.y) / 100.f));

				sp.SetPosition(tpos);
			}
			break;
		}
	}
}

void SceneController::PlaySpriteMoveAnim(const std::string& sprite_name, sf::Vector2f pos, float time)
{
	if (Sprites.empty()) return;

	for (auto& sp : Sprites) {
		if (sp.ItemName == sprite_name) {
			if (sp.bShowing) {

				auto tpos = sf::Vector2f(
					static_cast<float>(Options.width * pos.x) / 100.f,
					static_cast<float>(Options.height) - (static_cast<float>(Options.height * pos.y) / 100.f));

				sp.PlayMoveAnimation(tpos, time);
			}
			break;
		}
	}
}

void SceneController::HideAllSprites()
{
	if (Sprites.empty()) return;

	for (auto& sp : Sprites) {
		sp.bShowing = false;
	}
}

void SceneController::SetTextureColor(sf::Texture& texture, const sf::Color& color)
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

void SceneController::SetupDialogBox(const sf::Vector2f& size_percent, const sf::Vector2f& position_percent, float corner_radius, const ColorWrapper& background_color, float outline_thickness, const ColorWrapper& outline_color)
{
	sf::Vector2f size(Options.width * size_percent.x / 100.f, Options.height * size_percent.y / 100.f);
	
	auto tpos = sf::Vector2f(
		static_cast<float>((Options.width * position_percent.x) / 100.f) - (size.x/2),
		static_cast<float>((Options.height) - (static_cast<float>(Options.height * position_percent.y) / 100.f) - (size.y / 2)));

	DialogBox.SetBackgroundShape(size, tpos, corner_radius, background_color.ToSFMLColor(), outline_thickness, outline_color.ToSFMLColor());
	DialogBox.SetFont(TextFont);
}

void SceneController::SetText(const std::wstring& text, const std::wstring& name, bool print_anim)
{
	DialogBox.SetText(text, name);
	if (print_anim) DialogBox.PlayPrintAnimation();
	else DialogBox.StopPrintAnimation();
}

void SceneController::SetChoices(const std::vector<std::wstring>& options)
{
	DialogBox.SetChoices(options);
}

unsigned int SceneController::GetCurrentResponse()
{
	return DialogBox.GetSelectedResponse();
}

void SceneController::SetDialogBoxTextColor(const ColorWrapper& color)
{
	DialogBox.SetTextColor(color.ToSFMLColor());
}

void SceneController::SetDialogBoxHoverTextColor(const ColorWrapper& color)
{
	DialogBox.SetTextHoverColor(color.ToSFMLColor());
}

void SceneController::SetDialogBoxCharSize(float text_size, float name_size)
{
	DialogBox.SetCharacterSize(text_size, name_size);
}

void SceneController::SetDialogBoxPrintTime(float time_milsec)
{
	DialogBox.SetTimeToAddChar(time_milsec);
}

void SceneController::ShowDialogBox()
{
	DialogBox.bShowing = true;
}

void SceneController::HideDialogBox()
{
	DialogBox.bShowing = false;
}


std::string SceneController::GetFilePath(const std::string& file_name)
{
	for (auto& folder : Options.content_folders){
		std::string path = Root + folder + '/' + file_name;
		if (std::filesystem::exists(path)){
			return path;
		}
	}
	assert(false && strcat("File not found: ", file_name.c_str()));
	return "";
}

sf::Texture SceneController::GetImageTexture(const std::string& file_name)
{
	sf::Texture texture;
	std::string path = GetFilePath(file_name);
	assert(texture.loadFromFile(path) && "Not Found Image");
	return texture;
}

void SceneController::AddChannel(const std::string& name, const std::string& file_name) 
{
	if (AudioChannels.find(name) == AudioChannels.end()) {
		std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
		if (music->openFromFile(GetFilePath(file_name))) {
			AudioChannels[name] = music;
		}
	}
}

void SceneController::PlayChannel(const std::string& name, bool loop) 
{
	if (AudioChannels.empty()) return;

	if (AudioChannels.find(name) != AudioChannels.end()) {
		AudioChannels[name]->setLoop(loop);
		AudioChannels[name]->play();
	}
}

void SceneController::StopChannel(const std::string& name)
{
	if (AudioChannels.empty()) return;

	if (AudioChannels.find(name) != AudioChannels.end()) {
		AudioChannels[name]->stop();
	}
}

void SceneController::SetChannelVolume(const std::string& name, float volume) 
{
	if (AudioChannels.empty()) return;

	if (AudioChannels.find(name) != AudioChannels.end()) {
		AudioChannels[name]->setVolume(volume);
	}
}

void SceneController::ReloadChannel(const std::string& name, const std::string& file_name)
{
	if (AudioChannels.empty()) return;

	if (AudioChannels.find(name) != AudioChannels.end()) {
		AudioChannels[name]->stop();
		if (AudioChannels[name]->openFromFile(GetFilePath(file_name))) {
			AudioChannels[name]->play();
		}
	}
}

void SceneController::PausePlayingChannels()
{
	if (AudioChannels.empty()) return;

	for (auto& i : AudioChannels)
	{
		if (i.second->getStatus() == sf::SoundSource::Playing) {
			i.second->pause();
		}
	}
}

void SceneController::UnPausePlayingChannels()
{
	if (AudioChannels.empty()) return;

	for (auto& i : AudioChannels)
	{
		if (i.second->getStatus() == sf::SoundSource::Paused) {
			i.second->play();
		}
	}
}
void SceneController::StopAllChannels()
{
	if (AudioChannels.empty()) return;

	for (auto& i : AudioChannels)
	{
		i.second->stop();
		
	}
}

sf::Color ColorWrapper::ToSFMLColor() const
{
	sf::Color cl = sf::Color(r, g, b, a);
	return cl;
}
