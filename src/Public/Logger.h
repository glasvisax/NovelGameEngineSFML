#pragma once

#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

#ifdef __linux__
int _vscprintf (const char * format, va_list pargs); 
#endif

#define LOGGER Logger::GetLogger()
class Logger
{
public:
    void Log(const std::string& tag, std::string& sMessage);
    void Log(const std::string& tag, const char * format, ...);

   Logger& operator<<(const string& sMessage);

    static Logger* GetLogger();
private:
    Logger();

    static const std::string m_sFileName;

    static Logger* m_pThis;

    static ofstream m_Logfile;

	static sf::Clock m_clock;
};

