#include "Config.h"
#include "ConfigParser.h"
#include <cassert>
#include <string>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const std::string TITLE = "GameController";

ConfigOptions Config::Parse(std::string filename) 
{
	ConfigOptions opts;
	opts.width = WINDOW_WIDTH;
	opts.height = WINDOW_HEIGHT;
	opts.title = TITLE;

	ConfigParser settings;
	assert(settings.LoadFromFile(filename) && "couldn't load settings");

    settings.Get("width", opts.width);

    settings.Get("height", opts.height);

    settings.Get("title", opts.title);

	settings.Get("code", opts.code_file);

	settings.Get("content_folders", opts.content_folders);

	return opts;
}