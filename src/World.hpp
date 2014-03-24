#ifndef __PHIZ_WORLD__
#define __PHIZ_WORLD__

#include <vector>

#include "Body/Body.hpp"
#include "Link/Link.hpp"

#define SMP

namespace Phiz
{

class World
{
public:
    /**
     * \brief simulates the world by steps of _step maximum
     * \param total time to simulate
    */
    World();
    ~World();
	
    /**
     \brief simulates the world by steps of _step maximum
     \param dt total time to simulate
     */
    void step(float h);
    void add(Body* body);
    void add(Link* body);
    const std::vector<Body*>& bodies() const { return _bodies; }
    const std::vector<Link*>& links() const { return _links; }
protected:
#ifdef SMP
	unsigned _cores;
#endif
    std::vector<Body*> _bodies;
    std::vector<Link*> _links;
};

}

#endif /*__PHIZ_ENGINE__*/
