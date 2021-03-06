#ifndef _H_PLAYER
#define _H_PLAYER

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "world-entity.h"
#include "objective.h"
#include "game-object.h"

using namespace sf;

namespace Entities
{

    class Player : public WorldEntity
    {
    protected:
        RectangleShape* m_visShape;
        View*           m_view;
        float           m_speed = 0.4f;
        bool            m_canJump = true;
    public:
        Player(float       density,
               float       friction,
               b2World*    world,
               Vector2f    startPos,
               View*       camera);

        virtual ~Player();

        virtual void onThink();
        virtual void onDraw(RenderTarget* target);
        virtual void onCollide(World* world, GameObject<WorldEntity>* other);

        void jump();

        // negative for left, positive for right
        void move(float amt);

        void onKeyRelease(Keyboard::Key key);
        void collectObjective(World* world, Objective* objective);
    };

}

#endif
