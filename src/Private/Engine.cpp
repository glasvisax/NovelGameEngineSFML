#include "Engine.h"
#include "Logger.h"
#include "Script.h"
#include "Config.h"

#include <fstream>
#include <sstream>
#include <string>

Engine::Engine(int argc, char* argv[]) {

	resRoot = "D:/prog/cpp/GameProject/game"; // default game root
	
	for (int i = 0; i < argc; i++) {
		std::string opt(argv[i]);

		//If opt is game, then set resources root
		if (opt == "-game") {
			//Check for bounds
			if (i+1 < argc) {
				resRoot = argv[i+1];
				LOGGER->Log("Engine", "Game root is set to '%s'", resRoot.c_str());
			}
		}
	}
}

int Engine::start()
{
	Config cfg;
	opts = cfg.parse(resRoot + "/app.vanilla2d");

	LOGGER->Log("Engine","App Name: %s",opts.title.c_str());
	LOGGER->Log("Engine","Window Size: %d x %d", opts.width, opts.height);
	LOGGER->Log("Engine","FPS Limit: %d", opts.fps);

	//Parse game script
	LOGGER->Log("Engine","Parsing game script...");
	Script script;

	//Error check
	if (!script.open(resRoot + "/script.vanilla2d")) {
		LOGGER->Log("Engine","ERROR: script file cannot be opened!");
		return 1;
	}

	statements = script.parse();
	
	LOGGER->Log("Engine","Loaded %d statements", statements.size());

	//Create the window and enter the loop
	LOGGER->Log("Engine","Creating window...");
	
	window.create(sf::VideoMode(opts.width, opts.height), opts.title, sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(opts.fps);

	LOGGER->Log("Engine","Creating Game instance...");
	Game game(statements, opts, resRoot);

	while (window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {

			//If Close Button is clicked, exit
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			//Let game handle all other events
			game.handleInput(event, window);
		}

		//Update game logic, animations
		game.update();


		//Render everything
		window.clear();
		game.render(window);
		window.display();
	}

	LOGGER->Log("Engine","Window has been closed, exiting...");
	LOGGER->Log("Engine","ENGINE SHUTDOWN");

	return 0;
}
