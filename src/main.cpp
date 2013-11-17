#include <cassert>
#include <SDL.h>
#include <SDL_video.h>
#include <GL/glew.h>
#include <iostream>

#include "World.hpp"
#include "Body/FixedPoint.hpp"
#include "Body/Particle.hpp"
#include "Link/HookSpring.hpp"

using namespace Phiz;

int main(int argc, char* argv[])
{
	assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
	assert(SDL_SetVideoMode(800, 600, 0, SDL_OPENGL) != NULL);
	assert(glewInit() == GLEW_OK);
	
    glClearColor(0.f, 0.f, 0.f, 1.f);

    World world(0.01f);
    
    Body* fp = new FixedPoint(glm::vec3(0.0f, 0.0f, 0.0f));
    world.add(fp);

    Body* p0 = new Particle(glm::vec3(10.0f, 0.0f, 0.0f));
    world.add(p0);
    
    world.add(new HookSpring(fp, p0, 5.0f, 1.0f));
    
    Uint32 t_prev = SDL_GetTicks();
    bool running = true;
    while(running) {
        Uint32 t = SDL_GetTicks();
        float dt = (float)(0.001 * (double)(t - t_prev));

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = true;
            }
        }

        world.step(dt);

        glClear(GL_COLOR_BUFFER_BIT);

        std::cout << p0->position().x << " ; " << p0->position().y << " ; " << p0->position().z << std::endl;

        SDL_GL_SwapBuffers();
        t_prev = t;
    }
    
	return 0;
}