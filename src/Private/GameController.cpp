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
	if (bGameStarted && bWaitClick && e.mouseButton.button == sf::Mouse::Left && e.type == sf::Event::MouseButtonReleased) {
		NextStatement();
		bWaitClick = false;
	}
}

void GameController::NextStatement() 
{
	//TODO анимации дл€ спрайтов/ фонов. јудио
	Scene->SetTextCharacterSize(25.0f, 30.0f);
	
	switch (frame) 
	{
		case 0: 
		{
			Scene->SetText(L"zov сво ликвидирован", L"власов");
			Scene->ShowSprite("milk_chan");
			Scene->ShowGame();

			frame++;



			break;
		}
		case 1:
		{
			Scene->SetText(L"машала брат", L"дорнан");
			Scene->HideSprite("milk_chan");
			
			Scene->SetBackgroundSprite("2.png");
			Scene->ShowSprite("dornan");

			frame++;



			break;
		}
		case 2:
		{
			Scene->SetText(L"как сам чувак", L"власов");
			Scene->HideSprite("dornan");	
			Scene->SetBackgroundColor(sf::Color::White);
			Scene->ShowSprite("milk_chan");

			frame++;


			break;
		}
		case 3:
		{
			Scene->HideSprite("milk_chan");
			Scene->SetText(L"потихоньку братиш выбери плиз за кого ты", L"дорнан");
			Scene->SetBackgroundSprite("2.png");
			Scene->ShowSprite("dornan");

			frame++;


			break;
		}
		case 4:
		{
			Scene->SetTextCharacterSize(25.0f, 30.0f);
			Scene->HideSprite("dornan");
			Scene->SetChoices({ L"роа", L"упа" });
			Scene->SetBackgroundSprite("2.png");
			Scene->SetBackgroundColor(sf::Color::White);
			Scene->ShowSprite("milk_chan");
			
			frame++;


			break;
		}
		case 5:
		{
			if (ChosenResponse == 0) {
				
				Scene->SetTextCharacterSize(40.0f, 20.0f);
				Scene->SetText(L"базовичок ты наш слон€рский ””’!!!", L"milk_chan");

			}
			else if(ChosenResponse == 1) {
				Scene->SetText(L"хохол попалс€", L"milk_chan");
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

void GameController::OnGameStart()
{
	bGameStarted = true;
	NextStatement();
}

void GameController::OnGameExit()
{
	Window.close();
}

void GameController::OnWaitingClick()
{
	bWaitClick = true;
}

void GameController::OnChoose(unsigned int choise)
{

	ChosenResponse = choise;
	NextStatement();
	bWaitClick = true;
}

void GameController::Update() 
{
	/*
	DialogBox.update();

	//Delay logic
	if (delay > 0 && delayClock.getElapsedTime().asMilliseconds() > delay) {
		bHideText = false;
		delay = 0;
		nextStatement();
	}

	if (bFadeOn) {
		sf::Color c = fadeRect.getFillColor();

		//If fade animation is finished, continue executing statements
		if (fade < 0 && fade + c.a < 0) {
			bFadeOn = false;
			bHideText = false;
			nextStatement();
			return;
		} else if (fade > 0 && fade + c.a > 255) {
			fade = 0; // We do not set bFadeOn to false to allow executing next statements without losing fade rect state
			bHideText = false;
			nextStatement();
			return;
		} else {
			//If animation is in process, set rect color
			c.a += fade;
			fadeRect.setFillColor(c);
		}
	}
	*/
}


/*
void GameController::Render(sf::RenderWindow& window) 
{
	//window.draw(*Scene);
	//window.draw(Background);
	//window.draw(DialogBox);
	//window.draw(MainMenu);

	
	
	
	if (!bPlay) 
	{
		MainMenu.render(window);
	}
	//MainMenu.draw(window);
	
	window.draw(Background);
	window.draw(MainCharacterSprite);

	if (bFadeOn) window.draw(fadeRect);

	//Draw only if text is not hidden
	if (!bHideText) {
		window.draw(TextBoxSprite);
		window.draw(text);
	}


	//if (debug) window.draw(debugText);

	//fpsCounter.update();
	
}
*/
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