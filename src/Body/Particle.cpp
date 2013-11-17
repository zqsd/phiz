#include "Particle.hpp"

namespace Phiz
{

Particle::Particle(glm::vec3 position, float mass)
    : Body(position, mass)
{
}

Particle::~Particle()
{
}

void Particle::step(float h)
{
    _speed += (h / -_mass) * -_force;
    _position += h * -_speed;
    _force = glm::vec3(0.0f);
}

}