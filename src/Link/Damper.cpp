#include "Damper.hpp"

namespace Phiz
{

Damper::Damper(Body* a, Body* b, float z)
    : Link(a, b), _z(z)
{
}

Damper::~Damper()
{
}

void Damper::step(float dt)
{
    glm::vec3 force = -_z * (_a->cspeed() - _b->cspeed());
    _a->force() += force;
    _b->force() -= force;
}

}