#include "platform.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace Entities;

Platform::Platform(b2World* world, Vector2f position, Vector2f size, Color color)
{
    this->m_world = world;

    this->m_visShape = new RectangleShape();
    this->m_visShape->setFillColor(color);
    this->m_visShape->setSize(Vector2f(size.x * 2, size.y * 2));
    this->m_visShape->setOrigin(size.x, size.y);
    this->m_visShape->setPosition(position);
    float xOrigin = (size.x - position.x),
          yOrigin = (size.y - position.y);

    b2PolygonShape shape;
    shape.SetAsBox(size.x, size.y);

    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x, position.y);
    this->m_body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtDef;
    fixtDef.shape = &shape;
    fixtDef.density = 1.0f;
    fixtDef.friction = 0.3f;

    this->m_body->CreateFixture(&fixtDef);
}

Platform::~Platform()
{
    delete this->m_visShape;
    this->m_world->DestroyBody(this->m_body);
}

void Platform::onThink() {}

void Platform::onDraw(RenderTarget *target)
{
    target->draw(*this->m_visShape);
}
