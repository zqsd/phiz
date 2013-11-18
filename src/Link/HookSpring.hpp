#ifndef __PHIZ_HOOKSPRING__
#define __PHIZ_HOOKSPRING__

#include "Link.hpp"

namespace Phiz
{
    class HookSpring : public Link
    {
    public:
        /**
         * \brief Creates a spring between object a and b.
         * \param a first object
         * \param b second object
         * \param k spring stiffness
         * \param l rest length
         */
        HookSpring(Body* a, Body* b, float k, float l);

        /**
        * \brief Creates a spring between object a and b with default rest state.
        * \param a first object
        * \param b second object
        * \param k spring stiffness
        */
        HookSpring(Body* a, Body* b, float k);
        virtual ~HookSpring();

        virtual void step(float dt) override;
    protected:
        float _l;
        float _k;
    };
}

#endif /*__PHIZ_HOOKSPRING__*/