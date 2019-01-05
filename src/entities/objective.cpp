#include "world-entity.h"
#include "world.h"
#include "objective.h"
#include "game-object.h"


using namespace Entities;
using namespace sf;

Objective::Objective(Vector2f position,
                     int val,
                     World* world)
{
    this->m_value = val;
    this->m_world = world;

    this->m_visShape = new RectangleShape(Vector2f(0.8f, 1.f));
    this->m_visShape->setFillColor(Color(255, 255, 102));
    this->m_visShape->setOutlineColor(Color(255, 255, 40));
    this->m_visShape->setOutlineThickness(0.2f);
    this->m_visShape->setOrigin(Vector2f(0.4f, 0.5f));
    this->m_visShape->setPosition(position);

    b2PolygonShape circle;
    circle.SetAsBox(0.8f, 1.0f);

    b2BodyDef body;
    body.gravityScale = 0.f;
    body.position = b2Vec2(position.x, position.y);

    this->m_body = world->CreateBody(&body);
    GameObject<Objective>::Create("objective", this, this->m_body);


    b2FixtureDef fixDef;
    fixDef.shape = &circle;
    fixDef.density = 0.0f;
    fixDef.friction = 1;
    fixDef.isSensor = true;

    this->m_fixture = this->m_body->CreateFixture(&fixDef);
}

Objective::~Objective()
{
    delete this->m_visShape;
    this->m_world->DestroyBody(this->m_body);
    this->m_world->removeWorldEntity(this);
}

int Objective::getPointValue()
{
    return this->m_value;
}

void Objective::onThink() {}

void Objective::onDraw(RenderTarget* target)
{
    target->draw(*this->m_visShape);
}

void Objective::onCollide(World* world, GameObject<WorldEntity>* other) {}
