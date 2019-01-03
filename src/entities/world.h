#ifndef _H_WORLD
#define _H_WORLD

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "world-entity.h"
#include <list>

using namespace sf;
using namespace std;

namespace Entities
{
    const float PhysicsTimestep = 1.f / 60.f;
    const float VelocityIterations = 10;
    const float PositionIterations = 5;

    class World : public b2World
    {
    private:
        View*                  m_view;
        list<WorldEntity*>*    m_entities;
        list<WorldEntity*>*    m_drawables;
        RenderTarget*          m_renderer;

    public:
        World(RenderTarget* render, b2Vec2 grav);
        ~World();

        operator View*();

        void addWorldEntity(WorldEntity* ent);
        void removeWorldEntity(WorldEntity* ent);

        void addDrawableEntity(WorldEntity* ent);
        void removeDrawableEntity(WorldEntity* ent);

        void onThink();
        void onDraw(RenderTarget* target);
    };

}

#endif
