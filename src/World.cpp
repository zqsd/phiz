#include "World.hpp"
#include <algorithm>

namespace Phiz
{

World::World(float step)
    : _step(step)
{
    //SDL_GetCPUCount
    //SDL_Thread *thread;
    //thread = SDL_CreateThread( TestThread, "TestThread", (void *)NULL);
    //SDL_mutex *SDL_CreateMutex(void);
    //int SDL_mutexP(SDL_mutex *mutex); lock
    //int SDL_mutexV(SDL_mutex *mutex); unlock
}

World::~World()
{
}

void World::add(Body* body)
{
    _bodies.push_back(body);
}

void World::add(Link* link)
{
    _links.push_back(link);
}

void World::step(float remain)
{
    for(; remain > 0.0f;) {
        float dt = std::min(_step, remain);

        for(std::vector<Link*>::const_iterator it = _links.cbegin(); it != _links.cend(); it++) {
            Link* link = *it;
            link->step(dt);
        }
        for(std::vector<Body*>::const_iterator it = _bodies.begin(); it != _bodies.end(); it++) {
            Body* body = *it;
            body->step(dt);
        }

        remain -= dt;
    }
}

}