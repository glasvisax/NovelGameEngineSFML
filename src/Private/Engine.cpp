#include "Engine.h"
#include "GameController.h"
#include "SceneController.h"
#include "Script.h"
#include "Config.h"
#include <cassert>

Engine::Engine()
{
	Root = "D:/prog/cpp/GameProject/game"; // default game root
}

int Engine::Start()
{
	Config config;
	ConfigOptions options = config.Parse(Root + "/config.vn");

	Script script;
	assert(script.open(Root + options.code_file) && "couldn't open script");

	std::vector<Statement> statements = std::vector<Statement>(); //script.parse();

	sf::RenderWindow window;
	window.create(sf::VideoMode(options.width, options.height), options.title, sf::Style::Titlebar | sf::Style::Close);
	
	GameController game(Root, options, statements, window);
	SceneController scene(Root, options, window);

	game.SetSceneController(&scene);
	scene.SetGameController(&game);
	scene.StartScene();

	sf::Clock timer;

	while (window.isOpen()) {

		sf::Event event;
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			scene.HandleInput(event);
		}
		float time = timer.getElapsedTime().asMicroseconds();
		scene.Tick(time);

		timer.restart();
	}

	return 0;

}
