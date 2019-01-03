#ifndef _H_WORLD_ENTITY
#define _H_WORLD_ENTITY

#include <SFML/Graphics.hpp>

using sf::RenderTarget;

namespace Entities
{
    class WorldEntity
    {
    public:
        virtual void onThink() = 0;
        virtual void onDraw(RenderTarget* target) = 0;
    };
}

#endif
