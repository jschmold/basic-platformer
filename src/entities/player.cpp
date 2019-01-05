#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "player.h"
#include "world-entity.h"
#include "game-object.h"
#include "platform.h"
#include "list"

using namespace Entities;
using namespace sf;
using namespace std;

Player::Player(float       density,
               float       friction,
               b2World*    world,
               Vector2f    startPos,
               View*       view)
{
    // physics
    this->m_world    = world;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(startPos.x, startPos.y);

    this->m_body = world->CreateBody(&bodyDef);
    GameObject<Player>::Create("player", this, this->m_body);

    b2PolygonShape physShape;
    physShape.SetAsBox(0.4f, 0.4f);

    b2FixtureDef fixtureDef;
    fixtureDef.friction = friction;
    fixtureDef.density  = density;
    fixtureDef.shape    = &physShape;

    this->m_fixture = this->m_body->CreateFixture(&fixtureDef);

    // visuals
    this->m_visShape = new RectangleShape();
    this->m_visShape->setSize(Vector2f(0.4f, 0.4f));
    this->m_visShape->setFillColor(Color::Green);
    this->m_visShape->setOrigin(0.2f, 0.2f);
    this->m_visShape->setPosition(startPos);

    this->m_view = view;
    this->m_view->setCenter(0.4f, 0.4f);
}

void Player::onThink()
{
    auto pos = this->m_body->GetPosition();
    this->m_visShape->setPosition(pos.x, pos.y);
    this->m_view->setCenter(pos.x, pos.y);

    if (Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::LShift))
        this->move(-this->m_speed * 1.4);
    else if (Keyboard::isKeyPressed(Keyboard::A))
        this->move(-this->m_speed);

    if (Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::LShift))
        this->move(this->m_speed * 1.4);
    else if (Keyboard::isKeyPressed(Keyboard::D))
        this->move(this->m_speed);

    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
        cout << this->isTouchingType("platform");
    }
}

void Player::onDraw(RenderTarget* target)
{
    target->draw(*this->m_visShape);
}

Player::~Player()
{
    this->m_body->DestroyFixture(this->m_fixture);
    this->m_world->DestroyBody(this->m_body);

    this->m_body = nullptr;
    this->m_fixture = nullptr;
}

void Player::move(float amt)
{
    this->m_body->ApplyForceToCenter(b2Vec2(amt, 0), true);
}

void Player::jump()
{
    if (this->isTouchingType("platform"))
        this->m_body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -6.f), true);
}

void Player::onKeyRelease(Keyboard::Key key)
{
    if (key == Keyboard::Space) this->jump();
}

void Player::collectObjective(World* world, Objective *objective)
{
    this->m_visShape->setFillColor(Color::Blue);
    world->addPoints(objective->getPointValue());
    world->destroy(objective);
}

void Player::onCollide(World* world, GameObject<WorldEntity>* other)
{
    auto objType = other->getObjectType();
    if (objType == "objective") this->collectObjective(world, (Objective*)other->getObject());
}


