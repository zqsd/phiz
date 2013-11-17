#ifndef __PHIZ_PARTICLECOALLISION__
#define __PHIZ_PARTICLECOALLISION__

#include "Link.hpp"

namespace Phiz
{
    class ParticleCoallision : public Link
    {
    public:
        ParticleCoallision();
        virtual ~ParticleCoallision();

        virtual void step(float dt) = 0;
    protected:
    };

}

#endif /*__PHIZ_HOOKSPRING__*/