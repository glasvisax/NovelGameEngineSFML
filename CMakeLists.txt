cmake_minimum_required(VERSION 3.16)

project(GameProject LANGUAGES CXX)

FILE(GLOB_RECURSE headers src/Public/*.h src/Public/GUI/*.h)

FILE(GLOB_RECURSE sources src/Private/*.cpp src/*.cpp src/Private/GUI/*.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "D:/SFML/install/lib/cmake/SFML")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/exec)

add_executable(Main ${sources} ${headers})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

target_link_libraries(Main sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

target_include_directories(Main PUBLIC D:/SFML/install/include)

target_include_directories(Main PUBLIC src/Private PUBLIC src/Public)

source_group(TREE D:/prog/cpp/GameProject/src FILES ${sources} ${headers})
