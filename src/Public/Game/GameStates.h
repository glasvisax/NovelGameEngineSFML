#pragma once

#include <SFML/Graphics.hpp>
#include "SceneController.h"

#include "Script.h"
#include <vector>

class SceneController;

class GameController 
{
public:

	GameController(const std::string& root, const ConfigOptions& opts, const std::vector<Statement>& statements, sf::RenderWindow& window);

	void SetSceneController(SceneController* scene);

public:

	void SetCurrentChoice(unsigned int choise);
	void Next();

private:
	
	void NextStatement();
	const ConfigOptions& Options;
	const std::string& Root;
	const std::vector<Statement>& Statements;
	SceneController* Scene = nullptr;

private:
	unsigned int frame = 0;
	unsigned int ChosenResponse = -1;
};

