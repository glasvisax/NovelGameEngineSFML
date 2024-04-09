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
	GameController(const std::string& root, const ConfigOptions& opts, const std::vector<Statement>& statements, sf::RenderWindow& window);

	void SetSceneController(SceneController* scene);

public:

	void HandleInput(sf::Event e);
	void Update();
	void NextStatement();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void OnGameStart();
	void OnExitGame();

private:
	const ConfigOptions& Options;
	const std::string& Root;
	const std::vector<Statement>& Statements;
	sf::RenderWindow& Window;

	SceneController* Scene = nullptr;
	
	size_t ip = -1; // Like instruction pointer

};

