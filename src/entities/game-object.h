#ifndef _H_GAME_OBJECT
#define _H_GAME_OBJECT

#include <string>
#include <iostream>
#include <Box2D/Box2D.h>

using namespace std;

namespace Entities
{
    template <class T>
    class GameObject
    {
    private:

        GameObject(string type, T* value)
        {
            this->m_type = new string(type);
            this->m_value = value;
        }

        ~GameObject()
        {
            delete this->m_type;
        }

    protected:
        string*   m_type = nullptr;
        T*        m_value = nullptr;

    public:

        static void Create(string type, T* value, b2Body* body)
        {
            auto obj = new GameObject(type, value);
            body->SetUserData(obj);
        }

        T* getObject()
        {
            return this->m_value;
        }

        string getObjectType()
        {
            return *(this->m_type);
        }
    };
}

#endif
