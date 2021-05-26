# Planets
A C++ simulation of Newton's Law of Gravitation. Made by me

# Running
To run the program you can specify the bodies in the simulated space/universe through the .planets file or by changing the code. 
To use the .planets file simply change this line the `main.cpp` file to the desired .planets file:
```cpp
Physics::Universe universe = Physics::Universe("YOURPLANETSFILE.planets");
```
This repository provides a few examples in the `Examples/` directory and can be passed into the code and simulated.

## Programatically adding bodies to the universe
To add a body using the C++ code use this method call in the `main.cpp` before the SFML `while (window.IsOpen())` loop.
```cpp
Physics::Universe::NewBody(float mass, Vector2 position0, Vector2 velocity0, sf::Color color);
```
NOTE: The color parameter is optional.

Here is an example of adding an example body at the center that moves downwards:
```cpp
Physics::Universe::NewBody(100.f, {0.f, 0.f}, {0.f, 0.f}, sf::Color::Red);
```

# Making a custom .planets file
The .planets file provides data of the bodies to the simulation. In the .planets files, mass, position, velocity and colour are provided and all are optional
as they have a default value in the parser.

Every line is a body and each line must start with a B then the data of the body. Each data is separated by a semicolon. Order of the data does not matter.

Here is an example of a body in the .planets file, the values given are the default values of each data.
```
B mass = 1.0; position = (0,0); velocity = (0,0); color = (0, 255, 0)
```

Comments can be provided in the .planets file by adding a # symbol before the comment.
```
# This is an example body
B mass = 100.0; position = (200,0); velocity = (0,-100); color = (210, 150, 20)
```
