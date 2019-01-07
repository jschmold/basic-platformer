#include "world.h"
#include "objective.h"
#include <SFML/Graphics.hpp>
#include "game-object.h"


using namespace Entities;
using namespace sf;


World::World(RenderTarget* renderer, b2Vec2 gravity) : b2World(gravity)
{
    this->m_timestep = Entities::PhysicsTimestep;
    this->m_velocityIter = Entities::VelocityIterations;
    this->m_positionIter = Entities::PositionIterations;

    this->m_entities  = new list<WorldEntity*>();

    this->m_renderer  = renderer;

    this->m_view      = new View(FloatRect(0, 0, 1.f, 1.f));
    this->m_view->setSize(64.f, 36.f);
    this->m_view->setViewport(FloatRect(0.f, 0.f, 1.f, 1.f));

    if (!this->m_scoreFont.loadFromFile("./res/Thasadith-Regular.ttf"))
        throw "Unable to load font file";
}

World::~World()
{
    for (auto i = this->m_entities->begin() ; i != this->m_entities->end() ; i++)
        delete (*i);

    delete this->m_view;
    delete this->m_entities;

    this->m_view = nullptr;
    this->m_entities = nullptr;
}

void World::onThink()
{
    this->Step(this->m_timestep,
               this->m_velocityIter,
               this->m_positionIter);

    for (auto cont = this->GetContactList() ; cont; cont = cont->GetNext())
    {
        auto objA = (GameObject<WorldEntity>*)cont->GetFixtureA()->GetBody()->GetUserData();
        auto objB = (GameObject<WorldEntity>*)cont->GetFixtureB()->GetBody()->GetUserData();

        objA->getObject()->onCollide(this, objB);
        objB->getObject()->onCollide(this, objA);
    }

    for (auto i = this->m_entities->begin() ; i != this->m_entities->end() ; i++)
        (*i)->onThink();
}

World::operator View*()
{
    return this->m_view;
}

void World::addWorldEntity(WorldEntity* ent)
{
    this->m_entities->push_back(ent);
}

void World::removeWorldEntity(WorldEntity* ent)
{
    this->m_entities->remove(ent);
}


void World::onDraw(RenderTarget* target)
{
    target->setView(target->getDefaultView());
    target->clear(Color::Transparent);

    if (this->m_gui != nullptr)
    {
        // this is segfaulting
        this->m_gui->setTarget(*target);
        this->m_gui->draw();
    }


    Text text;
    text.setFont(this->m_scoreFont);
    text.setString("Points: " + to_string(this->m_playerPoints));
    text.setCharacterSize(36.f);


    text.setPosition(0, 0);
    text.setFillColor(Color::White);

    target->draw(text);
    target->setView(*this->m_view);

    if (this->m_entities->size() < 1) return;

    for(auto i = this->m_entities->begin(); i != this->m_entities->end(); i++) {
        WorldEntity* ent = *i;
        if (ent == nullptr) continue;
        ent->onDraw(target);
    }

}

void World::addPoints(int count)
{
    this->m_playerPoints += count;
}


void World::destroy(WorldEntity* obj)
{
    this->DestroyBody(obj->getBody());
    this->removeWorldEntity(obj);
}

bool World::getIsPaused()
{
    return this->m_timestep == 0;
}

void World::pause()
{
    this->m_timestep = 0;
}

void World::resume()
{
    this->m_timestep = Entities::PhysicsTimestep;
}

void World::setTimestep(float time)
{
    this->m_timestep = time;
}

void World::setGui(tgui::Gui* gui)
{
    this->m_gui = gui;
}
