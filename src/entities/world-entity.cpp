#include <Box2D/Box2D.h>
#include "game-object.h"
#include "platform.h"
#include <iostream>

using namespace Entities;
using namespace std;


bool WorldEntity::isTouchingType(string type)
{
    if (this->m_body->GetContactList() == nullptr) return false;

    for (b2ContactEdge* contact = this->m_body->GetContactList(); contact; contact = contact->next)
    {
        auto other = contact->other;
        if (other == nullptr) continue;

        GameObject<void*>* data = (GameObject<void*>*)contact->other->GetUserData();

        if (data->getObjectType() == type) return true;

    }
    return false;
}

bool WorldEntity::isTouchingAnything()
{
    return this->m_body->GetContactList() != nullptr
        && this->m_body->GetContactList()->other != nullptr;
}

b2Body* WorldEntity::getBody()
{
    return this->m_body;
}
