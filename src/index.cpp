#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <TGUI/TGUI.hpp>

#include "entities/entities.h"


using namespace std;
using namespace Entities;
using namespace sf;

void pauseGame(World* world, tgui::Button::Ptr btn, Sprite* img)
{
    if (world->getIsPaused()) {
        world->resume();
        btn->setText("Pause");
        img->setColor(Color::Transparent);
    } else {
        world->pause();
        btn->setText("Resume");
        img->setColor(Color::Red);
    }
}

Sprite pauseButton()
{
    RenderTexture* text = new RenderTexture();
    if(!text->create(24, 32)) throw "Unable to create pause texture";
    text->clear(Color::Transparent);

    RectangleShape rect(Vector2f(10.f, 32.f));
    rect.setFillColor(Color::Red);
    rect.setPosition(0, 0);
    text->draw(rect);

    rect.setPosition(14.f, 0);
    text->draw(rect);

    text->display();

    Sprite spr(text->getTexture());
    spr.setTextureRect(IntRect(24, 0, 48, 32.f));
    return spr;
}

int main(int argc, char* argv[])
{
    RenderWindow* window = new RenderWindow(VideoMode(1280, 720), "Game 4");

    auto closeWindow = [window]() {
      window->close();
    };

    World* world = new World(window, b2Vec2(0.0f, 0.2f));

    Player* ply  = new Player(4.f,
                              0.2f,
                              world,
                              Vector2f(0.f, -10.f),
                              *world);

    Platform* mainFloor = new Platform(world,
                                       Vector2f(-0.f, 0.f),
                                       Vector2f(10.f, .5f),
                                       Color::Red);

    auto windowSize = window->getSize();

    Sprite pauseImage = pauseButton();
    pauseImage.setColor(Color::Transparent);
    pauseImage.setTextureRect(IntRect(0, 0, 24, 32));
    pauseImage.setPosition((windowSize.x / 2) - (12 * 4), (windowSize.y / 2) - (16 * 4));
    pauseImage.setScale(4.f, 4.f);

    Objective* coin = new Objective(Vector2f(2.f, -4.f), 1, world);

    tgui::Gui* gui = new tgui::Gui();
    world->setGui(gui);

    tgui::Button::Ptr pauseBtn = tgui::Button::create();
    pauseBtn->setSize("10%", "5%");
    pauseBtn->setPosition("&.width - 10%", "0");
    pauseBtn->setText("Pause");
    pauseBtn->connect("pressed", pauseGame, world, pauseBtn, &pauseImage);

    gui->add(pauseBtn);

    world->addWorldEntity(ply);
    world->addWorldEntity(mainFloor);
    world->addWorldEntity(coin);

    while(window->isOpen())
    {
        Event evt;
        while(window->pollEvent(evt))
        {
            switch(evt.type)
            {
                case Event::KeyReleased: {
                    if (evt.key.code == Keyboard::Q) window->close();
                    if (evt.key.code == Keyboard::Escape) {
                        pauseGame(world, pauseBtn, &pauseImage);
                    }
                    if (world->getIsPaused() != true) ply->onKeyRelease(evt.key.code);
                    break;
                }
                default: break;
            }
        }
        gui->handleEvent(evt);

        world->onThink();
        world->onDraw(window);

        window->setView(window->getDefaultView());
        window->draw(pauseImage);

        window->display();
    }

    gui->removeAllWidgets();

    delete world;
    delete window;
    delete gui;

    return 0;
}
