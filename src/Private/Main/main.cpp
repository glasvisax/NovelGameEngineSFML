#include "Main/Engine.h"

#include <iostream>
#include <algorithm>
#include <windows.h>
#include <shellapi.h>


std::string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    if (pos == std::string::npos) {
        return "";
    } else {
        return std::string(buffer).substr(0, pos);
    }
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    std::string root = ExePath();
    std::replace(root.begin(), root.end(), '\\', '/');

    Engine engine;
    engine.Start(root);
    
    return 0;
}
