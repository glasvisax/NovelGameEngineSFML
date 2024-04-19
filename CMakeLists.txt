cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GameProject LANGUAGES CXX)

FILE(GLOB_RECURSE headers src/Public/*.h src/Public/GUI/*.h)

FILE(GLOB_RECURSE sources src/Private/*.cpp src/*.cpp src/Private/GUI/*.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "D:/SFML/install/lib/cmake/SFML")

set(THOR_ROOT "D:/Thor/install")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "D:/Thor/install/cmake/Modules")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/exec)

add_executable(Main ${sources} ${headers})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

find_package(Thor 2 MODULE REQUIRED)

target_link_libraries(Main sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${THOR_LIBRARY})

target_include_directories(Main PUBLIC ${SFML_INCLUDE_PATH})

target_include_directories(Main PUBLIC ${THOR_INCLUDE_DIR})

target_include_directories(Main PRIVATE src/Private PUBLIC src/Public)

source_group(TREE D:/prog/cpp/GameProject/src FILES ${sources} ${headers})
