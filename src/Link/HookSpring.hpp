#ifndef __PHIZ_HOOKSPRING__
#define __PHIZ_HOOKSPRING__

#include "../Body/Body.hpp"
#include "Link.hpp"

namespace Phiz
{
    class HookSpring : public Link
    {
    public:
        HookSpring(Body* a, Body* b, float l, float k);
        virtual ~HookSpring();

        virtual void step(float dt) override;
    protected:
        Body* _a;
        Body* _b;
        float _l;
        float _k;
    };
}

#endif /*__PHIZ_HOOKSPRING__*/