#include <math.h>
#include <Physics.hpp>

namespace Physics {

sf::Vector2f Zero() {
    return sf::Vector2f(0.f, 0.f);
}

sf::Vector2f Scale(const sf::Vector2f &v, const float &c) {
    return sf::Vector2f(v.x * c, v.y * c);
}

sf::Vector2f Normalise(const sf::Vector2f &v) {
    return Scale(v, 1. / sqrt(v.x * v.x + v.y * v.y));
}

float Distance(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    return sqrt(dx * dx + dy * dy);
}

}  // namespace Physics