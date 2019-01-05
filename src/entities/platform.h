#ifndef _H_PLATFORM_ENTITY
#define _H_PLATFORM_ENTITY

#include <SFML/Graphics.hpp>
#include "world-entity.h"
#include "game-object.h"
#include "world.h"

namespace Entities
{
    class Platform : public WorldEntity
    {
    private:
        RectangleShape* m_visShape;

    public:
        Platform(b2World* world, Vector2f position, Vector2f size, Color color);
        virtual ~Platform();

        virtual void onDraw(RenderTarget* target);
        virtual void onThink();
        virtual void onCollide(World* world, GameObject<WorldEntity>* other);
    };
}

#endif
