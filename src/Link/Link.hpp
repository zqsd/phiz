#ifndef __PHIZ_LINK__
#define __PHIZ_LINK__

#include "../Body/Body.hpp"

namespace Phiz
{
    class Link
    {
    public:
        Link(Body* a, Body* b);
        virtual ~Link();

        virtual void step(float dt) = 0;
        const Body* a() const { return _a; }
        const Body* b() const { return _b; }
    protected:
        Body* _a;
        Body* _b;
    };

}

#endif /*__PHIZ_LINK__*/