#ifndef __PHIZ_HOOKSPRINGDAMPER__
#define __PHIZ_HOOKSPRINGDAMPER__

#include "HookSpring.hpp"
#include "Damper.hpp"

namespace Phiz
{

class HookSpringDamper : public HookSpring, public Damper
{
public:
	HookSpringDamper(Body* a, Body* b, float k, float z);
	virtual ~HookSpringDamper();

	virtual void step(float dt);
protected:
	float _z;
};

}

#endif /*__PHIZ_HOOKSPRINGDAMPER__*/
