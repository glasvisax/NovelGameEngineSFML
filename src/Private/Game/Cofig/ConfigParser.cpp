#include "Game/Config/ConfigParser.h"

#include <locale>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool ConfigParser::LoadFromFile(const std::string& filename)
{
    m_data.clear();
    m_filename = filename;
    return Read();
}

bool ConfigParser::Read()
{
    std::ifstream in(m_filename);
    if(!in.is_open())
    {
        std::cerr << "Error: Unable to open settings file \"" << m_filename << "\" for reading!" << std::endl;
        return false;
    }

    std::string line;
    while(std::getline(in, line))
    {
        // parse line
        std::pair<std::string, std::string> keyValuePair = ParseLine(line);

        if(!keyValuePair.first.empty())
        {
            // if the line is not empty or a comment save it to the map
            m_data[keyValuePair.first] = keyValuePair.second;
        }
    }

    in.close();
    return true;
}

std::pair<std::string, std::string> ConfigParser::ParseLine(const std::string &line) const
{
    if(line.size() > 0 && line[0] != '#')
    {
        size_t index = 0;
        // trim leading whitespace
        while(std::isspace(line[index], m_locale))
            index++;
        // get the key string
        const size_t beginKeyString = index;
        while(!std::isspace(line[index], m_locale) && line[index] != '=')
            index++;
        const std::string key = line.substr(beginKeyString, index - beginKeyString);

        // skip the assignment
        while(std::isspace(line[index], m_locale) || line[index] == '=')
            index++;

        // get the value string
        const std::string value = line.substr(index, line.size() - index);

        // return the key value pair
        return std::make_pair(key, value);
    }

    // if this line is emtpy or a comment, return an empty pair
    return std::make_pair(std::string(), std::string());
}
