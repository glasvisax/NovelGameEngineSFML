#include "Engine.h"
#include <iostream>

int main(int argc, char* argv[])
{
	std::string root = argv[0];
	std::replace(root.begin(), root.end(), '\\', '/');
	std::string::iterator it = (root.begin() + root.find("Main"))-1;

	root.erase(it, root.end());
	Engine engine(root);
	return engine.Start();
}