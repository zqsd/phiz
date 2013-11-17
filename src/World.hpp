#ifndef __PHIZ_WORLD__
#define __PHIZ_WORLD__

#include <vector>

#include "Body/Body.hpp"
#include "Link/Link.hpp"

namespace Phiz
{

class World
{
public:
    World(float step);
    ~World();
	
    void step(float dt);
    void add(Body* body);
    void add(Link* body);
protected:
    float _step;
    std::vector<Body*> _bodies;
    std::vector<Link*> _links;
};

}

#endif /*__PHIZ_ENGINE__*/