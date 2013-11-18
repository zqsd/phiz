#ifndef __PHIZ_BODY_PARTICLE__
#define __PHIZ_BODY_PARTICLE__

#include "Body.hpp"

namespace Phiz
{
    class Particle : public Body
    {
    public:
        Particle(glm::vec3 position, float mass = 1.0f, float radius = 1.0f);
        virtual ~Particle();

        virtual void step(float dt) override;
        const float& cradius() const { return _radius; }
        float& radius() { return _radius; };
    protected:
        float _radius;
    };

}

#endif /*__PHIZ_BODY_PARTICLE__*/