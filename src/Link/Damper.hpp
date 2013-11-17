#ifndef __PHIZ_DAMPER__
#define __PHIZ_DAMPER__

#include "Link.hpp"

namespace Phiz
{
    class Damper : public Link
    {
    public:
        Damper();
        virtual ~Damper();

        virtual void step(float dt) = 0;
    protected:
    };

}

#endif /*__PHIZ_DAMPER__*/