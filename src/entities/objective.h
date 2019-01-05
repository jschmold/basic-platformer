#ifndef _H_OBJECTIVE
#define _H_OBJECTIVE

#include "world-entity.h"
#include "physics-entity.h"
#include "world.h"
#include "game-object.h"

namespace Entities
{
    class Objective : public WorldEntity, public PhysicsEntity, public GameObject<Objective>
    {
    private:
        int                m_value;
        World*             m_world;
        RectangleShape*    m_visShape;

    public:
        int getPointValue();

        Objective(Vector2f position, int val, World* world);
        virtual void onDraw(RenderTarget* target);
        virtual void onThink();
        virtual ~Objective();
    };
}

#endif
