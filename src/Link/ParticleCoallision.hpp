#ifndef __PHIZ_PARTICLECOALLISION__
#define __PHIZ_PARTICLECOALLISION__

#include "Link.hpp"
#include "../Body/Particle.hpp"

namespace Phiz
{
    class ParticleCoallision : public Link
    {
    public:
        /**
        * \brief Creates a coallision condition between two objects.
        * \param a first object
        * \param b second object
        * \param k stiffness
        * \param z damping factor
        */
        ParticleCoallision(Body* a, Body* b, float k, float z);
        virtual ~ParticleCoallision();

        virtual void step(float dt) override;
    protected:
        float _k;
        float _z;
    };

}

#endif /*__PHIZ_PARTICLECOALLISION__*/