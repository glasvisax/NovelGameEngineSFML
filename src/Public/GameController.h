#pragma once

#include <SFML/Graphics.hpp>
#include "SceneController.h"

#include "Script.h"
#include <vector>
#include "BaseController.h"

class SceneController;

class GameController : public BaseController
{
public:
	enum class CharacterPosition
	{
		LEFT,
		CENTER,
		RIGHT
	};

	GameController(const std::string& root, const ConfigOptions& opts, const std::vector<Statement>& statements, sf::RenderWindow& window);

	void SetSceneController(SceneController* scene);

public:

	void HandleInput(sf::Event e);
	void Update();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void OnGameStart();
	void OnGameExit();
	void OnWaitingClick();
	void OnChoose(unsigned int choise);

private:

	void NextStatement();
	const ConfigOptions& Options;
	const std::string& Root;
	const std::vector<Statement>& Statements;
	sf::RenderWindow& Window;

	SceneController* Scene = nullptr;
	
	unsigned int frame = 0; // Like instruction pointer

	bool bGameStarted = false;
	bool bWaitClick = false;
	unsigned int ChosenResponse = 0;
};

