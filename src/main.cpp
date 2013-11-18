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
    int width = 800,
        height = 600;
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    assert(SDL_SetVideoMode(width, height, 0, SDL_OPENGL) != NULL);
    assert(glewInit() == GLEW_OK);
	
    // init opengl
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glPointSize(16.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (float)width / (float)height, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 15.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // init physic scene
    World world(0.01f);
    Body* fp = new FixedPoint(glm::vec3(0.0f, 0.0f, 0.0f));
    world.add(fp);

    for(int i = 1; i < 5; i++) {
        Body* p0 = new Particle(glm::vec3(4.0f * (float)i, 0.0f, 0.0f));

        world.add(p0);
        world.add(new HookSpring(fp, p0, -0.1f));

        fp = p0;
    }
    
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

        // run physic simulation
        world.step(dt);

        // draw
        //FIXME: stream vbos rather than fixed pipeline
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POINTS);
        for(std::vector<Body*>::const_iterator it = world.bodies().cbegin(); it != world.bodies().cend(); it++) {
            Body* body = *it;
            glVertex3f(body->cposition().x, body->cposition().y, body->cposition().z);
        }
        glEnd();
        
        glBegin(GL_LINES);
        for(std::vector<Link*>::const_iterator it = world.links().cbegin(); it != world.links().cend(); it++) {
            Link* link = *it;
            const Body* a = link->a();
            const Body* b = link->b();

            glVertex3f(a->cposition().x, a->cposition().y, a->cposition().z);
            glVertex3f(b->cposition().x, b->cposition().y, b->cposition().z);
        }
        glEnd();

        SDL_GL_SwapBuffers();
        t_prev = t;
    }
    
	return 0;
}