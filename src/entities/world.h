#ifndef _H_WORLD
#define _H_WORLD

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <list>
#include "world-entity.h"
#include "objective.h"
#include <TGUI/TGUI.hpp>


using sf::View;
using sf::Font;
using sf::RenderTarget;

using tgui::Gui;

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
        tgui::Gui*             m_gui;
        int                    m_playerPoints;
        sf::Font               m_scoreFont;
        float                  m_timestep;
        float                  m_velocityIter;
        float                  m_positionIter;

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

        void setTimestep(float time);
        void pause();
        void resume();

        bool getIsPaused();

        void setGui(tgui::Gui* gui);

    };

}

#endif
