#ifndef __PHIZ_DAMPER__
#define __PHIZ_DAMPER__

#include "Link.hpp"

namespace Phiz
{
    class Damper : public Link
    {
    public:
        /**
        * \brief Creates a damper.
        * \param a first object
        * \param b second object
        * \param z damping factor
        */
        Damper(Body* a, Body* b, float z);
        virtual ~Damper();

        virtual void step(float dt);
    protected:
        float _z;
    };

}

#endif /*__PHIZ_DAMPER__*/
