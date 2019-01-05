#ifndef _H_GAME_OBJECT
#define _H_GAME_OBJECT

#include <string>

using std::string;

namespace Entities
{
    template <class T>
    class GameObject
    {
    protected:
        string    m_type;
        T*        m_value;
    public:
        GameObject(T* value, string type)
        {
            this->m_value = value;
            this->m_type = type;
        }

        T* getObject()
        {
            return this->m_value;
        }
        string getType()
        {
            return this->m_type;
        }
    };
}

#endif
