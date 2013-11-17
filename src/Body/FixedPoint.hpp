#ifndef __PHIZ_BODY_FIXEDPOINT__
#define __PHIZ_BODY_FIXEDPOINT__

#include "Body.hpp"

namespace Phiz
{
    class FixedPoint : public Body
    {
    public:
        FixedPoint(glm::vec3 position);
        virtual ~FixedPoint();

        virtual void step(float dt) override;
    protected:
    };

}

#endif /*__PHIZ_FIXEDPOINT__*/