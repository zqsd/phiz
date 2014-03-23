#include "FixedPoint.hpp"

namespace Phiz
{

FixedPoint::FixedPoint(glm::vec3 position, float radius)
    : Body(position, radius)
{
}

FixedPoint::~FixedPoint()
{
}

void FixedPoint::step(float dt)
{
    //_force = glm::vec3(0.0f);
}

}