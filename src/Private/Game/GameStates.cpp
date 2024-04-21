#include <GameController.h>
#include <SceneController.h>
#include <string>
#include <cassert>
#include <GUI/GUI.h>

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

void GameController::Next()
{
	// ...
	NextStatement();
}

void GameController::NextStatement()
{
	Scene->SetTextCharacterSize(25.0f, 30.0f);
	
	switch (frame) 
	{
		case 0: 
		{
			Scene->SetText(L"zov ��� ������������", true, L"������");
			Scene->ShowSprite("milk_chan", true);
			Scene->StartGame();

			frame++;

			break;
		}
		case 1:
		{
			Scene->HideSprite("milk_chan", true);

			Scene->SetText(L"������ ���� ������������������������������������", true, L"������");
			Scene->ShowBackground("2");
			Scene->ShowSprite("dornan", true);

			frame++;

			break;
		}
		case 2:
		{
			Scene->HideSprite("dornan", true);	

			Scene->SetText(L"��� ��� ����� �����������������������", true, L"������");
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

			Scene->SetText(L"���������� ������ ������ ���� �� ���� ��", false, L"������");
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
			Scene->SetChoices({ L"���", L"���" });
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
				Scene->SetText(L"��������� �� ��� ���������� ���!!!", false, L"milk_chan");

			}
			else if(ChosenResponse == 1) {
				Scene->SetText(L"����� �������", false, L"milk_chan");
			}
			frame = 4;
			
		}

	}

	return;
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