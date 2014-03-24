#include "World.hpp"
#include <algorithm>
#include <iostream>

#ifdef SMP
#include <thread>
#include <future>
#endif

namespace Phiz
{

World::World()
{
#ifdef SMP
	_cores = std::max(std::thread::hardware_concurrency(), (unsigned)1);
#endif
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

void World::step(float h)
{
#ifdef SMP
	std::vector<std::future<void>> results(_cores);

	unsigned linksCount = _links.size();
	for(unsigned i = 0; i < _cores; i++) {
		unsigned i_start = i * linksCount / _cores,
			     i_stop = (i + 1) * linksCount / _cores;
		results[i] = std::async(std::launch::async, [this, &h, i_start, i_stop]() {
			for(unsigned i = i_start; i < i_stop; i++) {
				_links[i]->step(h);
			}
		});
	}
	for(unsigned i = 0; i < _cores; i++) {
		results[i].wait();
	}

	unsigned bodiesCount = _bodies.size();
	for(unsigned i = 0; i < _cores; i++) {
		unsigned i_start = i * bodiesCount / _cores,
		         i_stop = (i + 1) * bodiesCount / _cores;
		results[i] = std::async(std::launch::async, [this, &h, i_start, i_stop]() {
			for(unsigned i = i_start; i < i_stop; i++)
				_bodies[i]->step(h);
		});
	}
	for(unsigned i = 0; i < _cores; i++) {
		results[i].wait();
	}
#else
	for(unsigned i = 0; i < _links.size(); i++) {
		_links[i]->step(h);
	}

	for(unsigned i = 0; i < _bodies.size(); i++) {
		_bodies[i]->step(h);
	}
#endif
}

}
