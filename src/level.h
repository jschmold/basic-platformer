#ifndef _H_LEVEL
#define _H_LEVEL

#include "entities/world.h"
#include <SFML/Graphics.hpp>
#include <map>

using namespace std;


using sf::Sprite;
using sf::Texture;
using Entities::World;

namespace Game
{

    class Level
    {

    public:
        typedef bool (*completionFunction)(Level*, World*);

    protected:
        map<string, Sprite*>   m_sprites;
        map<string, Texture*>  m_textures;

        World*                 m_world      = nullptr;
        completionFunction     m_completion = nullptr;

    public:
        Level();
        ~Level();

        void     addSprite (string name, Sprite* sprite);
        void     removeSprite (string name);
        Sprite*  getSprite (string name);

        void     addTexture (string name, Texture* txt);
        void     removeTexture (string name);
        Texture* getTexture (string name);

        World*   getWorld ();
        void     setWorld (World* world);
    };
}

#endif
