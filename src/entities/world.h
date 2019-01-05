#ifndef _H_WORLD
#define _H_WORLD

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <list>
#include "world-entity.h"
#include "objective.h"


using namespace sf;
using namespace std;

namespace Entities
{

    const float PhysicsTimestep    = 1.f / 60.f;
    const float VelocityIterations = 10;
    const float PositionIterations = 5;

    class World : public b2World
    {
    private:
        list<WorldEntity*>*    m_entities;
        RenderTarget*          m_renderer;
        View*                  m_view;
        int                    m_playerPoints;
        Font                   m_scoreFont;

    public:
        World(RenderTarget* render, b2Vec2 grav);
        ~World();

        operator View*();

        void addWorldEntity(WorldEntity* ent);
        void removeWorldEntity(WorldEntity* ent);

        void onThink();
        void onDraw(RenderTarget* target);

        void addPoints(int count);

        void destroy(WorldEntity* obj);
    };

}

#endif
