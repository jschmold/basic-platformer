#include "level.h"
#include "entities/world.h"
#include <SFML/Graphics.hpp>
#include <map>

using namespace Game;

using sf::Sprite;
using sf::Texture;
using Entities::World;

Level::Level ()
{
};


// This cleans up all sprites and textures added
Level::~Level ()
{
    for (auto sprite = this->m_sprites.begin(); sprite != this->m_sprites.end(); sprite++)
    {
        this->m_sprites.erase(sprite);
    }

    for (auto texture = this->m_textures.begin(); texture != this->m_textures.end(); texture++)
    {
        this->m_textures.erase(texture);
    }
}


void Level::addSprite(string name, Sprite* sprite)
{
    if (this->m_sprites[name] != nullptr)
        throw "Sprite name already in use for this level";

    this->m_sprites[name] = sprite;
}

void Level::removeSprite (string name)
{
    auto sprite = this->m_sprites[name];
    if (sprite == nullptr) return;

    delete sprite;
    this->m_sprites.erase(name);
}
Sprite* Level::getSprite (string name)
{
    return this->m_sprites[name];
}

void Level::addTexture (string name, Texture* txt)
{
    if (this->m_textures[name] != nullptr)
        throw "Texture name already in use for this level";

    this->m_textures[name] = txt;
}

void Level::removeTexture (string name)
{
    auto texture = this->m_textures[name];
    if (texture == nullptr) return;

    delete texture;
    this->m_textures.erase(name);
}

Texture* Level::getTexture (string name)
{
    return this->m_textures[name];
}

World* Level::getWorld ()
{
    return this->m_world;
}

void Level::setWorld (World* world)
{
    this->m_world = world;
}
