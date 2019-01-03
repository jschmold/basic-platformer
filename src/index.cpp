#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "entities/entities.h"

using namespace std;
using namespace Entities;
using namespace sf;

int main(int argc, char* argv[])
{
    RenderWindow* window = new RenderWindow(VideoMode(1280, 720), "Game 4");

    World* world = new World(window, b2Vec2(0.0f, 0.2f));

    Player* ply  = new Player(4.f, 0.2f, world, Vector2f(0.f, -10.f), *world);
    Platform* mainFloor = new Platform(world,
                                       Vector2f(-0.f, 0.f),
                                       Vector2f(10.f, .5f),
                                       Color::Red);
    world->addDrawableEntity(ply);
    world->addWorldEntity(ply);
    world->addWorldEntity(mainFloor);
    world->addDrawableEntity(mainFloor);

    while(window->isOpen())
    {
        Event evt;
        while(window->pollEvent(evt))
        {
            switch(evt.type)
            {
                case Event::KeyReleased: {
                    if (evt.key.code == Keyboard::Escape) window->close();
                    ply->onKeyRelease(evt.key.code);
                    break;
                }
                default: break;
            }
        }

        window->clear(Color::Black);
        world->onThink();
        world->onDraw(window);
        window->display();
    }

    delete world;
    delete window;
    delete ply;
    delete mainFloor;

    return 0;
}
