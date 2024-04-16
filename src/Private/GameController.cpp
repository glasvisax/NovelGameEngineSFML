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

}

void GameController::NextStatement() 
{



	/*
	//Stop if EOV (end-of-vector)
	if (ip + 1 == statements.size()) return;

	//Increment instruction pointer
	ip++;

	//Execute current statement
	Statement s = statements.at(ip);
	if (s.type == StatementType::BACKGROUND) {
		std::string path = root + "/img/" + s.content;
		if (!BackgroundTexture.loadFromFile(path)) {
			LOGGER->Log("GameController","ERROR: Failed to load Background %s at statement %d", s.content.c_str(), ip);
		} else {
			LOGGER->Log("GameController","Changed Background to %s", s.content.c_str());
		}
		Background.setTexture(BackgroundTexture);
		Background.setPosition(sf::Vector2f(0,0));

		nextStatement();
		return;
	}

	if (s.type == StatementType::TEXT) {
		DialogBox.SetText(s.wtext);
	}

	if (s.type == StatementType::DELAY) {
		delay = atoi(s.content.c_str());
		bHideText = true;
		delayClock.restart();
	}

	if (s.type == StatementType::FONT) {
		if (!TextFont.loadFromFile(root + "/fonts/"+s.content)) {
			LOGGER->Log("GameController","ERROR: Failed to load font %s at statement %d", s.content.c_str(), ip);
		} else {
			LOGGER->Log("GameController","Changed font to %s", s.content.c_str());
		}
		nextStatement();
	}

	if (s.type == StatementType::TEXT_COLOR) {
		sf::Color c = Utils::parseColor(s.content);
		text.setFillColor(c);
		//debugText.setFillColor(c);
		LOGGER->Log("GameController","Changed text color to RGBA(%d,%d,%d,%d)", c.r, c.g, c.b, c.a);
		nextStatement();
	}

	if (s.type == StatementType::MUSIC) {
		std::string path = root + "/music/" + s.content;
		if (!music.openFromFile(path)) {
			LOGGER->Log("GameController","ERROR: Failed to load music %s at statement %d", s.content.c_str(), ip);
		} else {
			LOGGER->Log("GameController","Changed music to %s", s.content.c_str());
		}
		music.setLoop(true);
		music.play();

		nextStatement();
		return;
	}

	if (s.type == StatementType::FADE) {
		std::stringstream ss(s.content);
		int n = 0;
		std::string way;

		ss >> way; //in or out
		ss >> n; //fade speed

		if (way == "in") {
			fade = n;
			bFadeOn = true;
			fadeRect.setFillColor(sf::Color(0,0,0,0));
			bHideText = true;
		} else if (way == "out"){
			fade = -n;
			bFadeOn = true;
			fadeRect.setFillColor(sf::Color(0,0,0,255));
			bHideText = true;
		} else {
			LOGGER->Log("GameController", "Unknown fade value at statements %d. Only 'in' and 'out' values are supported.", ip);
		}
	}
	*/
}

void GameController::BeginPlay()
{
	assert(Scene && "SceneController is nullptr");

	auto play_btn = Scene->GetMainMenu().GetButtonByText("Play");
	if(play_btn) { play_btn->BindOnClick(this, &GameController::OnGameStart); }

	//Scene->GetMainMenu().GetButtonByText("Options").BindOnClick(this, ...);

	auto exit_btn = Scene->GetMainMenu().GetButtonByText("Exit");
	if(exit_btn) { exit_btn->BindOnClick(this, &GameController::OnGameExit); }
}

void GameController::Tick(float DeltaTime)
{

}

void GameController::OnGameStart()
{
	Scene->ShowGame();
}

void GameController::OnGameExit()
{
	Window.close();
}

void GameController::OnNextFrame()
{

}

void GameController::OnChoose(unsigned int choise)
{

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