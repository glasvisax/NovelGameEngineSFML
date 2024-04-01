#include "Logger.h"

#ifdef __linux__
int _vscprintf (const char * format, va_list pargs) 
{
    int retval;
    va_list argcopy;
    va_copy(argcopy, pargs);
    retval = vsnprintf(NULL, 0, format, argcopy);
    va_end(argcopy);
    return retval;
}
#endif

const string Logger::m_sFileName = "engine.log";
Logger* Logger::m_pThis = nullptr;
ofstream Logger::m_Logfile;
sf::Clock Logger::m_clock;

Logger::Logger() {}
Logger* Logger::GetLogger(){
    if (m_pThis == nullptr){
        m_pThis = new Logger();
        m_Logfile.open(m_sFileName.c_str(), ios::out);
    }
    return m_pThis;
}
 
void Logger::Log(const std::string& tag, const char * format, ...)
{
    char* sMessage = NULL;
    int nLength = 0;
    va_list args;
    va_start(args, format);
    nLength = _vscprintf(format, args) + 1;
    sMessage = new char[nLength];
    vsprintf(sMessage, format, args);
    m_Logfile << "[" << tag << " at " << m_clock.getElapsedTime().asSeconds() << "s] " << sMessage << "\n";
    va_end(args);
 
    delete [] sMessage;
}
 
void Logger::Log(const std::string& tag, std::string& sMessage)
{
    m_Logfile << "[" << tag << " at " <<  m_clock.getElapsedTime().asSeconds() << "s] " << sMessage << "\n";
}
 
Logger& Logger::operator<<(const string& sMessage)
{
   m_Logfile << "[" << "Default" << " at " <<  m_clock.getElapsedTime().asSeconds() << "s] " << sMessage << "\n";
    return *this;
}
