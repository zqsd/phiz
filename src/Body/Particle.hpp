#ifndef __PHIZ_BODY_PARTICLE__
#define __PHIZ_BODY_PARTICLE__

#include "Body.hpp"

namespace Phiz
{
    class Particle : public Body
    {
    public:
        Particle(glm::vec3 position, float mass = 1.0f);
        virtual ~Particle();

        virtual void step(float dt) override;
    protected:
    };

}

#endif /*__PHIZ_BODY_PARTICLE__*/