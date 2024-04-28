#include "Main/Engine.h"
#include "Game/GameStates.h"
#include "Scene/SceneController.h"

void Engine::Start(const std::string& root)
{
	ConfigOptions opts;
	GameStates::GetConfigOptions(opts);

	sf::RenderWindow window;
	window.create(sf::VideoMode(opts.width, opts.height), opts.title, sf::Style::Titlebar | sf::Style::Close);
	
	SceneController scene(root, opts, window);
	GameStates game(&scene);

	game.StartGame();
}
