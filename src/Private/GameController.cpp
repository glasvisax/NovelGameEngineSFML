#include <GameController.h>
#include <SceneController.h>
#include <string>
#include <cassert>
#include <GUI/GUI.h>

GameController::GameController(const std::string& root, const ConfigOptions& opts, const std::vector<Statement>& statements, sf::RenderWindow& window)
	: Root(root)
	, Options(opts)
	, Statements(statements)
	, Window(window)
{

}

void GameController::SetSceneController(SceneController* scene)
{
	this->Scene = scene;
}

void GameController::HandleInput(sf::Event e)
{
	if (bHandleInput && e.mouseButton.button == sf::Mouse::Left && e.type == sf::Event::MouseButtonReleased) 
	{
		Next();
	}
}

void GameController::StopHandlingInput()
{
	bHandleInput = false;
}

void GameController::StartHandlingInput()
{
	bHandleInput = true;
}

void GameController::OnExitGame()
{
	Window.close();
}

void GameController::Next()
{
	StopHandlingInput();
	NextStatement();
	Scene->StartHandlingInput();
}

void GameController::NextStatement()
{
	//TODO анимации для спрайтов/ фонов. Аудио
	Scene->SetTextCharacterSize(25.0f, 30.0f);
	
	switch (frame) 
	{
		case 0: 
		{
			Scene->SetText(L"zov сво ликвидирован", L"власов");
			Scene->ShowSprite("milk_chan", true);
			Scene->ShowGame();

			frame++;

			break;
		}
		case 1:
		{
			// TODO пофиксить
			Scene->HideSprite("milk_chan", true);

			Scene->SetText(L"машала брат ээээээээээээээээээээээээээээээээээээ", L"дорнан");
			Scene->ShowBackground("2");
			Scene->ShowSprite("dornan", true);

			frame++;

			break;
		}
		case 2:
		{
			Scene->HideSprite("dornan", true);	

			Scene->SetText(L"как сам чувак эээээээээээээээээээээээ", L"власов");
			Scene->SetBackgroundColor(sf::Color::White);
			Scene->ShowSprite("milk_chan", true);
			Scene->PlayAudioChannel("channel_0", true);
			Scene->SetAudioChannelVolume("channel_0", 0.5f);
			frame++;


			break;
		}
		case 3:
		{
			Scene->HideSprite("milk_chan", true);

			Scene->SetText(L"потихоньку братиш выбери плиз за кого ты", L"дорнан");
			Scene->ShowBackground("2", true);
			Scene->ShowSprite("dornan", true);

			frame++;


			break;
		}
		case 4:
		{
			//Scene->StopAudioChannel("channel_0");

			Scene->PlayAudioChannel("channel_1");
			Scene->SetAudioChannelVolume("channel_1", 0.7f);
			Scene->HideSprite("dornan", true);

			Scene->SetTextCharacterSize(25.0f, 30.0f);
			Scene->SetChoices({ L"роа", L"упа" });
			Scene->SetBackgroundColor(sf::Color::White);
			Scene->ShowSprite("milk_chan", true);
			
			frame++;


			break;
		}
		
		case 5:
		{
			static int my_counter = 0;

			if (ChosenResponse == 0) {
				Scene->SetTextCharacterSize(40.0f, 20.0f);
				Scene->SetText(L"базовичок ты наш слонярский УУХ!!!", L"milk_chan");

			}
			else if(ChosenResponse == 1) {
				Scene->SetText(L"хохол попался", L"milk_chan");
			}
			frame = 4;
			
		}

	}

	return;
}

void GameController::BeginPlay()
{
	assert(Scene && "SceneController is nullptr");
}

void GameController::Tick(float DeltaTime)
{
}

void GameController::SetCurrentChoice(unsigned int choise)
{
	ChosenResponse = choise;
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