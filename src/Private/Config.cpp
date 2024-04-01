#include "Config.h"
#include "Logger.h"
#include "ConfigParser.h"
#include <string>


// Default config options
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int FPS = 30;
const std::string TITLE = "Vanilla2D Application";

ConfigOptions Config::parse(std::string filename) {
	//Fill the struct with defaults
	ConfigOptions opts;
	opts.width = WINDOW_WIDTH;
	opts.height = WINDOW_HEIGHT;
	opts.fps = FPS;
	opts.title = TITLE;

	ConfigParser settings;
    if(!settings.loadFromFile(filename))
    {
        LOGGER->Log("ConfigParser", "ERROR: failed to open application config! Defaults are applied");
        return opts;
    }

    settings.get("width", opts.width);

    settings.get("height", opts.height);

    settings.get("title", opts.title);

	settings.get("fps", opts.fps);

	return opts;
}