#include "ParticleCoallision.hpp"

namespace Phiz
{

ParticleCoallision::ParticleCoallision(Body* a, Body* b, float k, float z)
    : Link(a, b), _k(k), _z(z)
{
}

ParticleCoallision::~ParticleCoallision()
{
}

void ParticleCoallision::step(float dt)
{
    Particle* a = (Particle*)_a;
    Particle* b = (Particle*)_b;
    const float EPS = 0.0001f;
    float d2 = glm::dot(_a->cposition(), _b->cposition());
    float d0 = a->cradius() + b->cradius();
    if(d2 > std::pow(d0 * (1.0f + EPS), 2.0f))
        return;
    float d = std::sqrt(d2);
    float e = 1.0f - (d0 / d);
    glm::vec3 force = -_k * e * (_a->cposition() - _b->cposition()) - _z * (_a->cspeed() - _b->cspeed());
    _a->force() -= force;
    _b->force() += force;
}

}