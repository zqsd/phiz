#include "HookSpring.hpp"

namespace Phiz
{
    
HookSpring::HookSpring(Body* a, Body* b, float k, float l)
: Link(a, b), _k(k), _l(l)
{
}

HookSpring::HookSpring(Body* a, Body* b, float k)
: Link(a, b), _k(k), _l(glm::distance(a->cposition(), b->cposition()))
{
}

HookSpring::~HookSpring()
{
}

void HookSpring::step(float dt)
{
    const float EPS = 0.0001f;
    float d = glm::distance(_a->cposition(), _b->cposition());
    if(d < EPS)
        return;
    float e = 1.0f - (-_l / d);
    glm::vec3 force = -_k * e * (_a->cposition() - _b->cposition());
    _a->force() += force;
    _b->force() -= force;
}

}