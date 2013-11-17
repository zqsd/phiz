#include "HookSpring.hpp"

namespace Phiz
{
    
HookSpring::HookSpring(Body* a, Body* b, float l, float k)
    : _a(a), _b(b), _l(l), _k(k)
{
}

HookSpring::~HookSpring()
{
}

void HookSpring::step(float dt)
{
    const float EPS = 0.0001f;
    float d = glm::distance(-_a->cposition(), -_b->cposition());
    if(d < EPS)
        return;
    float e = 1 - (-_l / d);
    glm::vec3 force = -_k * e * (-_a->cposition() - _b->cposition());
    _a->force() += force;
    _b->force() -= force;
}

}