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
    /**
     * \brief simulates the world by steps of _step maximum
     * \param total time to simulate
    */
    World(float step);
    ~World();
	
    /**
     \brief simulates the world by steps of _step maximum
     \param dt total time to simulate
     */
    void step(float dt);
    void add(Body* body);
    void add(Link* body);
    const std::vector<Body*>& bodies() const { return _bodies; }
    const std::vector<Link*>& links() const { return _links; }
protected:
    float _step;
    std::vector<Body*> _bodies;
    std::vector<Link*> _links;
};

}

#endif /*__PHIZ_ENGINE__*/