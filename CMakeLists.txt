cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(GameProject LANGUAGES CXX)

set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# -----------DEBUG - ON RELEASE CHANGE----------------

set(CMAKE_INSTALL_PREFIX D:/prog/cpp/GameProject/Engine)
set(THOR_ROOT D:/Thor/install)
set(SFML_ROOT D:/SFML/install)

#-----------------------------------------------------
set(SFML_DIR ${SFML_DIR}/lib/cmake/SFML)
set(SFML_INCLUDE_DIR ${SFML_ROOT}/include)

file(GLOB THOR_LIBS ${THOR_ROOT}/lib/*.lib)
file(GLOB THOR_DLLS ${THOR_ROOT}/bin/*.dll)
file(GLOB SFML_LIBS ${SFML_ROOT}/lib/*.lib)
file(GLOB SFML_DLLS ${SFML_ROOT}/bin/*.dll)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${THOR_ROOT}/cmake/Modules)

file(GLOB_RECURSE SCENE_SOURCES "src/Private/Scene//*.cpp" "src/Public/Scene//*.h")
file(GLOB_RECURSE GAME_SOURCES "src/Private/Game//*.cpp" "src/Public/Game//*.h")
file(GLOB_RECURSE MAIN_SOURCES "src/Private/Main//*.cpp" "src/Public/Main//*.h")

add_library(Game SHARED ${GAME_SOURCES})
add_library(Scene SHARED ${SCENE_SOURCES})
add_executable(Main WIN32 ${MAIN_SOURCES})

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
find_package(Thor 2 MODULE REQUIRED)

target_link_libraries(Scene PRIVATE sfml-system PRIVATE sfml-window PRIVATE sfml-graphics PRIVATE sfml-audio PRIVATE ${THOR_LIBRARY})
target_include_directories(Scene PUBLIC ${THOR_INCLUDE_DIR})
target_include_directories(Scene PUBLIC src/Public)

target_link_libraries(Game PUBLIC Scene)
target_include_directories(Game PUBLIC ${SFML_INCLUDE_DIR})
target_include_directories(Game PUBLIC ${THOR_INCLUDE_DIR})
target_include_directories(Game PUBLIC src/Public)

target_link_libraries(Main PRIVATE sfml-system PRIVATE sfml-window PRIVATE sfml-graphics PRIVATE sfml-audio PRIVATE Game PRIVATE Scene )
target_include_directories(Main PUBLIC ${SFML_INCLUDE_DIR})
target_include_directories(Main PUBLIC ${THOR_INCLUDE_DIR})
target_include_directories(Main PUBLIC src/Public)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src FILES ${SCENE_SOURCES} ${GAME_SOURCES} ${MAIN_SOURCES})

install(DIRECTORY ${SFML_INCLUDE_DIR}/SFML ${THOR_INCLUDE_DIR}/Thor ${THOR_INCLUDE_DIR}/Aurora src/Public DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install(FILES ${THOR_LIBS} ${SFML_LIBS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/libs)
install(FILES ${THOR_DLLS} ${SFML_DLLS} DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY src/Private/Game/ DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS Game Scene Main DESTINATION ${CMAKE_INSTALL_PREFIX})