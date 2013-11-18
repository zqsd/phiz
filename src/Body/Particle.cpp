#include "Particle.hpp"

namespace Phiz
{

Particle::Particle(glm::vec3 position, float mass, float radius)
    : Body(position, mass), _radius(radius)
{
}

Particle::~Particle()
{
}

void Particle::step(float h)
{
    _force += h * glm::vec3(0.0f, 9.81f, 0.0f); // gravity

    _speed += (h / -_mass) * -_force;
    _position += h * -_speed;
    _force = glm::vec3(0.0f);
}

}