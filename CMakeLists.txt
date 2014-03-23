cmake_minimum_required(VERSION 2.8)
project(phiz)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

find_package(SDL REQUIRED)
if (NOT SDL_FOUND)
    message (FATAL_ERROR "SDL not found!")
endif (NOT SDL_FOUND)
include_directories(${SDL_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

add_executable(phiz
               src/main.cpp

               src/World.cpp src/World.hpp
               src/Body/Body.cpp src/Body/Body.hpp
               src/Body/FixedPoint.cpp src/Body/FixedPoint.hpp
               src/Body/Particle.cpp src/Body/Particle.hpp
               src/Link/Damper.cpp src/Link/Damper.hpp
               src/Link/HookSpring.cpp src/Link/HookSpring.hpp
               src/Link/HookSpringDamper.cpp src/Link/HookSpringDamper.hpp
               src/Link/Link.cpp src/Link/Link.hpp
               src/Link/ParticleCoallision.cpp src/Link/ParticleCoallision.hpp
               )
target_link_libraries(phiz
    ${SDL_LIBRARY}
    ${SDLMAIN_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
)
