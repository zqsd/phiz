#include "HookSpringDamper.hpp"

namespace Phiz
{

HookSpringDamper::HookSpringDamper(Body* a, Body* b, float k, float z)
	: HookSpring(a, b, k), Damper(a, b, z)
{
}

HookSpringDamper::~HookSpringDamper()
{
}

void HookSpringDamper::step(float dt)
{
	HookSpring::step(dt);
	Damper::step(dt);
}

}