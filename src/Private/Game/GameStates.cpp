#include <Game/GameStates.h>
#include <Scene/SceneController.h>
#include <string>
#include <cassert>

GameController::GameController(const std::string& root, const ConfigOptions& opts, const std::vector<Statement>& statements, sf::RenderWindow& window)
	: Root(root)
	, Options(opts)
	, Statements(statements)
{

}

void GameController::SetSceneController(SceneController* scene)
{
	this->Scene = scene;
}

void GameController::StartGame()
{
	assert(Scene && "Scene is nullptr");

	auto& db = Scene->SetupDialogBox(sf::Vector2f(90, 30), sf::Vector2f(50, 15), 2.0f, sf::Color::Black, 3.0f, sf::Color(32.f, 115.f, 49.f));
	db.SetCharacterSize(27.0f, 35.0f);
	db.SetTextColor(sf::Color(32.f, 115.f, 49.f));

	Scene->AddBackground("2", "2.png");

	Scene->AddSprite("milk_chan", "milk_chan.png", { -30, 45 }, 0.5);
	Scene->AddSprite("dornan", "dornan.png", { 130, 49 });

	Scene->AddChannel("channel_0", "1.ogg");
	Scene->AddChannel("channel_1", "2.mp3");

	auto& mm = Scene->AddMenu(sf::Vector2f(50, 50), { L"Play", L"Options", L"Exit" }, "Main_Menu");

	auto play_mm = mm.GetButtonByText(L"Play");
	if (play_mm) { play_mm->BindOnClick(this, &GameController::StartNovel); }

	auto exit_mm = mm.GetButtonByText(L"Exit");
	if (exit_mm) { exit_mm->BindOnClick(Scene, &SceneController::Exit); }

	auto& em = Scene->AddMenu(sf::Vector2f(50, 50), { L"Continue", L"Main Menu", L"Exit" }, "Escape_Menu");

	auto continue_em = em.GetButtonByText(L"Continue");
	if (continue_em) { continue_em->BindOnClick(this, &GameController::ContinueNovel); }

	auto exit_em = em.GetButtonByText(L"Exit");
	if (exit_em) { exit_em->BindOnClick(Scene, &SceneController::Exit); }

	auto main_menu_em = em.GetButtonByText(L"Main Menu");
	if (main_menu_em) { main_menu_em->BindOnClick(this, &GameController::GoToMainMenu); }

	Scene->ToNextFrameEvent = [this]() { NextStatement(); };
	Scene->EscapePressEvent = [this]() {
		Scene->PausePlayingChannels();
		Scene->ShowMenu("Escape_Menu");
		};

	Scene->ShowMenu("Main_Menu");
	Scene->StartScene();
}

void GameController::StartNovel()
{
	Scene->HideMenu("Main_Menu");
	Scene->ShowDialogBox();
	NextStatement();
}

void GameController::GoToMainMenu()
{
	Scene->SetBackgroundColor(sf::Color::White);
	Scene->StopAllChannels();
	Scene->HideAllSprites();
	Scene->HideDialogBox();
	frame = 0;
	Scene->ShowMenu("Main_Menu");
}

void GameController::ContinueNovel()
{
	Scene->UnPausePlayingChannels();
	Scene->HideMenu("Escape_Menu");
	frame--;
	NextStatement();
}

void GameController::NextStatement()
{
	switch (frame) 
	{
		case 0: 
		{
			Scene->SetText(L"zov сво ликвидирован дорово чувак", L"власов", true);
			
			Scene->ShowSprite("milk_chan", true);
			
			Scene->PlaySpriteMoveAnim("milk_chan", sf::Vector2f{ 30, 45 }, 1.0f);

			frame++;

			break;
		}
		case 1:
		{
			Scene->ShowBackground("2", 2.0f);

			Scene->SetText(L"машала брат", L"дорнан", true);
			
			Scene->ShowSprite("dornan");

			Scene->PlaySpriteMoveAnim("dornan", sf::Vector2f(75.0f, 49.0f), 1.0f);

			frame++;

			break;
		}
		case 2:
		{	
			Scene->SetBackgroundColor(sf::Color::White, 2.0f);

			Scene->SetText(L"как сам чел", L"власов", true);

			Scene->PlayChannel("channel_0", true);

			Scene->SetChannelVolume("channel_0", 0.7f);

			frame++;

			break;
		}
		case 3:
		{

			Scene->SetText(L"потихоньку братиш\n выбери плиз за кого ты", L"дорнан", true);

			Scene->ShowBackground("2", 2.0f);

			frame++;

			break;
		}
		case 4:
		{
			Scene->HideSprite("dornan", 1.0f);

			Scene->HideSprite("milk_chan", 1.0f);

			Scene->PlayChannel("channel_1");

			Scene->SetChannelVolume("channel_1", 0.7f);

			Scene->SetChoices({ L"роа", L"упа" });

			Scene->SetBackgroundColor(sf::Color::White);
			
			frame++;

			break;
		}
		
		case 5:
		{
			Scene->ShowSprite("dornan", 1.0f);

			Scene->ShowSprite("milk_chan", 1.0f);

			unsigned int ChosenResponse = Scene->GetCurrentResponse();
			if (ChosenResponse == 0) {
				Scene->SetText(L"базовичок ты наш слон€рский ””’!!!", L"milk_chan", true);
			}
			else if(ChosenResponse == 1) {
				Scene->SetText(L"хохол попалс€", L"milk_chan", true);
			}

			frame = 4;
			
		}

	}

	return;
}


/*
sf::Color parseColor(std::string str) {
	std::istringstream ss(str);

	int r = 0;
	int g = 0;
	int b = 0;
	int a = 0;
	ss >> r;
	ss >> g;
	ss >> b;
	ss >> a;

	sf::Color newColor(r, g, b, a);
	return newColor;
}
*/