#ifndef __PHIZ_LINK__
#define __PHIZ_LINK__

namespace Phiz
{
    class Link
    {
    public:
        Link();
        virtual ~Link();

        virtual void step(float dt) = 0;
    protected:
    };

}

#endif /*__PHIZ_LINK__*/