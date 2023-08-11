cmake_minimum_required(VERSION 3.22)
project(Planets VERSION 0.2 
                DESCRIPTION "Simulation of Newton's Law of Gravitation"
                LANGUAGES CXX)

find_package(SFML 2 REQUIRED COMPONENTS window graphics)

add_executable(${CMAKE_PROJECT_NAME} main.cpp 
	src/Body.cpp 
	src/Managers.cpp 
	src/Universe.cpp 
	src/Vector2.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src/)
target_link_libraries(${CMAKE_PROJECT_NAME} sfml-window sfml-graphics)