#ifndef __PHIZ_BODY__
#define __PHIZ_BODY__

#include <glm/glm.hpp>

namespace Phiz
{
    class Body
    {
    public:
        Body(glm::vec3 position, float mass = 1.0f);
        virtual ~Body();

        virtual void step(float dt) = 0;

        glm::vec3& position() { return _position; }
        const glm::vec3& cposition() const { return _position; }
       
        glm::vec3& speed() { return _speed; }
        const glm::vec3& cspeed() const { return _speed; }

        glm::vec3& force() { return _force; }
        const glm::vec3& cforce() const { return _force; }
    protected:
        glm::vec3 _position;
        glm::vec3 _speed;
        glm::vec3 _force;
        float _mass;
    };

}

#endif /*__PHIZ_BODY__*/