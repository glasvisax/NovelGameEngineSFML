#pragma once 

#include <string>
#include <map>
#include <vector>
#include <sstream>

class ConfigParser 
{
public:
    ConfigParser() {};
    ~ConfigParser() {};

    bool LoadFromFile(const std::string& filename);
    
    template<typename T>
    void Get(const std::string& key, T & value) const;

    template<typename T>
    void Get(const std::string& key, std::vector<T> &value) const;
    
private:
    
    template<typename T>
    T ConvertToType(const std::string &input) const 
    {
        T value;
        std::stringstream ss(input);
        ss >> value;

        return value;
    };

    bool Read();

    std::pair<std::string, std::string> ParseLine(const std::string& line) const;

    std::string m_filename;
    std::map<std::string, std::string> m_data;
    const std::locale m_locale;
};

template<>
inline bool ConfigParser::ConvertToType<bool>(const std::string &input) const {
    return input == "TRUE" ? true : false;
}

template<>
inline char ConfigParser::ConvertToType<char>(const std::string &input) const {
    return input[0];
}

template<>
inline std::string ConfigParser::ConvertToType<std::string>(const std::string &input) const {
    return input;
}

template<typename T>
inline void ConfigParser::Get(const std::string& key, T &value) const {
    auto it = m_data.find(key);
    
    if (it != m_data.end()){
        value = ConvertToType<T>(it->second);
    }
}

template<typename T>
inline void ConfigParser::Get(const std::string& key, std::vector<T> &value) const 
{
    
    auto it = m_data.find(key);
    if (it != m_data.end()){
        
        std::string output;
        std::istringstream parser(it->second);
        
        value.clear();
        
        //split by comma
        while (getline(parser, output, ',')){
            output.erase(remove(output.begin(), output.end(), ' '), output.end());
            value.push_back(ConvertToType<T>(output));
        }
    }
}
