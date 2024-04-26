#include "Engine.h"

#include <iostream>
#include <algorithm>

int main(int argc, char* argv[])
{
	std::string root = argv[0];
	std::replace(root.begin(), root.end(), '\\', '/');
	root.erase((root.begin() + root.find("Main")) - 1, root.end());

	Engine engine;
	engine.Start(root);
}