#include <cassert>
#include <SDL.h>
#include <SDL_video.h>
#include <GL/glew.h>
#include <iostream>
#include <cmath>

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
    glPointSize(4.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (float)width / (float)height, 0.1, 100.0);



    // init physic scene
    World world(0.01f); // 10ms
    const int size = 20;
    const float k = -100.0f;
    Body* line[size * 2 + 1][size * 2 + 1];

    // cloth
    for(int i = 0; i <= size; i++) {
        for(int j = 0; j <= size; j++) {
            line[i][j] = NULL;
        }
    }
    line[0][0] = new FixedPoint(glm::vec3(-10.0f, 10.0f, 0.0f));
    world.add(line[0][0]);
    line[0][size] = new FixedPoint(glm::vec3(10.0f, 10.0f, 0.0f));
    world.add(line[0][size]);
    for(int i = 0; i <= size; i++) {
        for(int j = 0; j <= size; j++) {
            if(line[i][j] == NULL) {
                float x = ((float)j / (float)size - 0.5f) * 20.0f,
                      y = -((float)i / (float)size - 0.5f) * 20.0f;
                Body* p = new Particle(glm::vec3(x, y, 0.0f));
                line[i][j] = p;
                world.add(p);
            }
        }
    }
    for(int i = 0; i <= size; i++) {
        for(int j = 0; j <= size; j++) {
            if(i > 0)
                world.add(new HookSpring(line[i][j], line[i - 1][j], k));
            if(j > 0)
                world.add(new HookSpring(line[i][j], line[i][j - 1], k));
        }
    }
    
    float rot_x = 0.0f;
    Uint32 t_prev = SDL_GetTicks();
    bool running = true;
    while(running) {
        Uint32 t = SDL_GetTicks();
        float dt = (float)(0.001 * (double)(t - t_prev));

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            } else if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
            } else if(event.type == SDL_MOUSEMOTION) {
                rot_x = 3.14159f * (float)event.motion.x / (float)width;
            }
        }

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(15.0 * std::sin(rot_x), 0.0, 15.0 * std::cos(rot_x),
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);

        // run physic simulation
        world.step(dt);

        // draw
        //FIXME: stream vbos rather than fixed pipeline
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POINTS);
        for(std::vector<Body*>::const_iterator it = world.bodies().begin(); it != world.bodies().end(); it++) {
            Body* body = *it;
            glVertex3f(body->cposition().x, body->cposition().y, body->cposition().z);
        }
        glEnd();
        
        glBegin(GL_LINES);
        for(std::vector<Link*>::const_iterator it = world.links().begin(); it != world.links().end(); it++) {
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
