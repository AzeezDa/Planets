#include <Managers.hpp>
#include <Physics.hpp>
#include <algorithm>
#include <cstring>
#include <fstream>

namespace Physics {

Universe::Universe(const std::string &path) {
    std::string line;
    std::ifstream file(path);

    if (file.is_open()) {
        while (std::getline(file, line)) {
            // Check first character: B is body, # is comment
            if (line[0] != 'B')
                continue;

            float mass = 10.0f;
            sf::Vector2f position, velocity;
            sf::Color color = sf::Color::Green;

            // Split values by semicolons
            std::vector<std::string> commands = Physics::Managers::SplitStringIgnoreSpace(line.substr(1), ';');

            // Split each value by equals sign
            for (size_t i = 0; i < commands.size(); i++) {
                std::vector<std::string> values = Physics::Managers::SplitStringIgnoreSpace(commands[i], '=');
                if (!std::strcmp(values[0].c_str(), "mass")) {
                    mass = std::stof(values[1]);
                    continue;
                }
                if (!std::strcmp(values[0].c_str(), "position")) {
                    std::vector<std::string> coordinates = Physics::Managers::SplitStringIgnoreSpace(values[1].substr(1, values[1].length() - 2), ',');
                    position = sf::Vector2f(std::stof(coordinates[0]), std::stof(coordinates[1]));
                    continue;
                }
                if (!std::strcmp(values[0].c_str(), "velocity")) {
                    std::vector<std::string> coordinates = Physics::Managers::SplitStringIgnoreSpace(values[1].substr(1, values[1].length() - 2), ',');
                    velocity = sf::Vector2f(std::stof(coordinates[0]), std::stof(coordinates[1]));
                    continue;
                }
                if (!std::strcmp(values[0].c_str(), "color")) {
                    std::vector<std::string> colorData = Physics::Managers::SplitStringIgnoreSpace(values[1].substr(1, values[1].length() - 2), ',');
                    color = sf::Color(std::stoi(colorData[0]), std::stoi(colorData[1]), std::stoi(colorData[2]));
                    continue;
                }
            }

            bodies.emplace_back(mass, position, velocity, color);
        }
    }
}

void Universe::Update(const float &elapsedTime) {
    for (auto &b : bodies) {
        if (!b.ToBeRemoved) {
            b.Update(elapsedTime, bodies);
        }
    }

    // Remove the collided bodies
    bodies.erase(std::remove_if(bodies.begin(), bodies.end(), [](Body b) { return b.ToBeRemoved; }), bodies.end());
}

void Universe::Draw(sf::RenderWindow &window) {
    for (auto &body : bodies) {
        body.Draw(window);
    }
}

}  // namespace Physics