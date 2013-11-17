#include "Body.hpp"

namespace Phiz
{

Body::Body(glm::vec3 position, float mass)
    : _position(position), _mass(mass), _speed(0.0f), _force(0.0f)
{
}

Body::~Body()
{
}

}