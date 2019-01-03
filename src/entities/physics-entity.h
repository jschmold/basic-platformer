#ifndef _H_ENTITIES
#define _H_ENTITIES

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace Entities
{
    class PhysicsEntity
    {
    protected:
        b2World*            m_world;
        b2Body*             m_body;
    };
}

#endif
