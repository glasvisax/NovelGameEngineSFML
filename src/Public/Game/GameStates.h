#pragma once

#include <SFML/Graphics.hpp>

#include "Scene/SceneController.h"
#include "Game/Script/Script.h"

#include <vector>

class SceneController;

class GameController 
{
public:

	GameController(const std::string& root, const ConfigOptions& opts, const std::vector<Statement>& statements, sf::RenderWindow& window);

	void SetSceneController(SceneController* scene);

public:
	void StartGame();
	void StartNovel();
	void GoToMainMenu();
	void ContinueNovel();


private:
	void NextStatement();
	const ConfigOptions& Options;
	const std::string& Root;
	const std::vector<Statement>& Statements;
	SceneController* Scene = nullptr;

private:
	unsigned int frame = 0;
};

