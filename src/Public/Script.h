#pragma once

#include <iostream>
#include <fstream>
#include <vector>

enum StatementType {
	MUSIC,
	DELAY,
	BACKGROUND,
	TEXT,
	FONT,
	TEXT_COLOR,
	FADE
};

struct Statement {
	StatementType type;
	std::string content; // This is used to store filenames, because SFML loadFromFile() does not support std::wstring 
	std::wstring wtext; // This is set when statement is TEXT, so it can store Unicode characters
};

class Script
{
public:
	bool open(std::string filename);
	std::vector<Statement> parse();
private:
	std::wifstream m_file;
	
};

