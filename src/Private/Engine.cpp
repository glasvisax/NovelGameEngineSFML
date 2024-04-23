#include "Engine.h"
#include "Game/GameStates.h"
#include "Scene/SceneController.h"
#include "Game/Script/Script.h"
#include "Game/Config/Config.h"
#include <cassert>

int Engine::Start()
{
	Config config;
	ConfigOptions options = config.Parse(Root + "/config.txt");

	Script script;
	assert(script.open(Root + options.code_file) && "couldn't open script");

	std::vector<Statement> statements = std::vector<Statement>(); //script.parse();

	sf::RenderWindow window;
	window.create(sf::VideoMode(options.width, options.height), options.title, sf::Style::Titlebar | sf::Style::Close);
	
	GameController game(Root, options, statements, window);
	SceneController scene(Root, options, window);

	game.SetSceneController(&scene);
	game.StartGame();

	return 0;

}
