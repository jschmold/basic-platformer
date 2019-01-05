#ifndef _H_WORLD_ENTITY
#define _H_WORLD_ENTITY

#include <SFML/Graphics.hpp>
#include "game-object.h"
#include <iostream>
#include "string"
#include "list"

using namespace sf;
using namespace std;

namespace Entities
{
    class World;

    class WorldEntity
    {
    public:

    protected:
        b2World*            m_world;
        b2Body*             m_body;
        b2Fixture*          m_fixture;

    public:
        virtual void onCollide(World* world, GameObject<WorldEntity>* other) = 0;
        virtual void onThink() = 0;
        virtual void onDraw(RenderTarget* target) = 0;
        bool isTouchingType(string type);

        bool isTouchingAnything();
        b2Body* getBody();

        template <class T> list<GameObject<T>*>* getAllTouchingOfType(string type)
        {
            auto lst = new list<GameObject<T>*>();

            for(auto edge = this->m_body->GetContactList(); edge != nullptr; edge = edge->next)
                {
                    GameObject<void*>* data = (GameObject<void*>*)edge->other->GetUserData();
                    if (data == nullptr) cout << "WARNING! Missing game object data";
                    if (data != nullptr && data->getObjectType() == type)
                        lst->push_back((GameObject<T>*)data);
                }
            return lst;
        }
    };
}

#endif
