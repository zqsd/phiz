#include <cassert>
#include <SDL.h>
#include <SDL_video.h>
#include <GL/glew.h>
#include <GL/GLU.h>
#include <iostream>
#include <cmath>

#include "World.hpp"
#include "Body/FixedPoint.hpp"
#include "Body/Particle.hpp"
#include "Link/HookSpringDamper.hpp"

using namespace Phiz;

int main(int argc, char* argv[])
{
    int width = 1024,
        height = 768;
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
    World world;
	const float h = 1.0f / 50.0f;
	const float alpha = 0.01f, beta = 0.001f;
	const float k = -alpha / (h * h),
				z = beta / h;
	const unsigned n_w = 40,
	               n_h = 40;
	Body* grid[n_w][n_h];

    // cloth
	for(int i = 0; i < n_w; i++) {
		world.add(grid[i][0] = new FixedPoint(glm::vec3((float)i - (float)n_w / 2.0f, (float)n_h / 2.0f, (float)n_h / 2.0f)));
		for(int j = 1; j < n_h; j++) {
			world.add(grid[i][j] = new Particle(glm::vec3((float)i - (float)n_w / 2.0f, (float)n_h / 2.0f, (float)(n_h - j) - (float)n_h / 2.0f)));
		}
    }

	// horizontal links
	for(int i = 0; i < n_w - 1; i++) {
		for(int j = 0; j < n_h; j++) {
			world.add((HookSpring*)new HookSpringDamper(grid[i][j], grid[i + 1][j], k, z));
		}
	}
	// vertical links
	for(int i = 0; i < n_w; i++) {
		for(int j = 0; j < n_h - 1; j++) {
			world.add((HookSpring*)new HookSpringDamper(grid[i][j], grid[i][j + 1], k, z));
		}
	}
	// diagonal links
	for(int i = 0; i < n_w - 1; i++) {
		for(int j = 0; j < n_h - 1; j++) {
			world.add((HookSpring*)new HookSpringDamper(grid[i + 1][j], grid[i][j + 1], k, z));
			world.add((HookSpring*)new HookSpringDamper(grid[i][j], grid[i + 1][j + 1], k, z));
		}
	}
	// double horizontal links
	for(int i = 0; i < n_w - 2; i++) {
		for(int j = 0; j < n_h; j++) {
			world.add((HookSpring*)new HookSpringDamper(grid[i][j], grid[i + 2][j], k, z));
		}
	}
	// double vertical links
	for(int i = 0; i < n_w; i++) {
		for(int j = 0; j < n_h - 2; j++) {
			world.add((HookSpring*)new HookSpringDamper(grid[i][j], grid[i][j + 2], k, z));
		}
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	GLUquadric* quadric = gluNewQuadric();
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
        gluLookAt(n_w * std::sin(rot_x), 0.0, n_w * std::cos(rot_x),
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);

        // run physic simulation
        world.step(h);

        // draw
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POINTS);
        for(std::vector<Body*>::const_iterator it = world.bodies().begin(); it != world.bodies().end(); it++) {
            Body* body = *it;
            glVertex3f(body->cposition().x, body->cposition().y, body->cposition().z);
        }
        glEnd();
        
		glColor3f(0.6f, 0.6f, 0.6f);
        glBegin(GL_LINES);
        for(std::vector<Link*>::const_iterator it = world.links().begin(); it != world.links().end(); it++) {
            Link* link = *it;
            const Body* a = link->a();
            const Body* b = link->b();

            glVertex3f(a->cposition().x, a->cposition().y, a->cposition().z);
            glVertex3f(b->cposition().x, b->cposition().y, b->cposition().z);
        }
        glEnd();

		glColor3f(0.0f, 0.0f, 0.75f);
		gluSphere(quadric, (float)n_w / 4.0f, 32, 32);


        SDL_GL_SwapBuffers();
        t_prev = t;
    }
    
	return 0;
}
