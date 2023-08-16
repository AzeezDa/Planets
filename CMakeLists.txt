cmake_minimum_required(VERSION 3.22)
project(Planets VERSION 0.2 
                DESCRIPTION "Simulation of Newton's Law of Gravitation"
                LANGUAGES CXX)

set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
	lua
	GIT_REPOSITORY https://github.com/walterschell/Lua.git
	GIT_TAG v5.4.5
)
FetchContent_MakeAvailable(lua)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(${CMAKE_PROJECT_NAME} main.cpp 
	src/Universe.cpp 
	src/Vector2.cpp
	src/Body.cpp 
	src/ViewManager.cpp 
	src/Configuration.cpp
	)
	
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src/)
target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics lua_static)
