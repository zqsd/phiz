#include "Body.hpp"

namespace Phiz
{

Body::Body(glm::vec3 position, float radius, float mass)
    : _position(position), _mass(mass), _radius(radius), _speed(0.0f), _force(0.0f)
{
}

Body::~Body()
{
}

}