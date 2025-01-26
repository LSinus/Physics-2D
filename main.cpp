#include <SFML/Graphics.hpp>
#include "physicsWorld.h"
#include "solver.h"
#include <sstream>


void createObject(PhysicsWorld* world, float radius, float x, float y, std::vector<sf::CircleShape*>* shapes) {
    PhysicsObject* obj = new PhysicsObject(radius, x, y);
    sf::CircleShape* shape = new sf::CircleShape(radius);
    shape->setFillColor(sf::Color::White);
    shape->setOrigin(shape->getRadius(), shape->getRadius());
    shape->setPosition(x, y);

    world->addObject(obj);
    shapes->push_back(shape);

}

int main()
{
    // create the window (remember: it's safer to create it in the main thread due to OS limitations)
    sf::RenderWindow window(sf::VideoMode({800, 700}), "Physics-2D");

    sf::Font font;


    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(200);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10.f, 10.f);

    sf::Clock clock;
    sf::Time deltaTime;
    float frameTime;
    float fps = 0.f;

    std::vector<sf::CircleShape*> shapes;

    Solver solver;
    PhysicsWorld world(solver);
    window.setFramerateLimit(60);

    sf::CircleShape bg(300.f);
    bg.setFillColor(sf::Color::Blue);
    bg.setOrigin(bg.getRadius(), bg.getRadius());
    bg.setPointCount(200);
    bg.setPosition(400.f, 350.f);

    while (window.isOpen())
    {
        deltaTime = clock.restart();
        frameTime = deltaTime.asSeconds();

        fps = 1.f / frameTime;
        std::stringstream ss;
        ss << "FPS: " << static_cast<int>(fps);
        fpsText.setString(ss.str());

        for (int i = 0; i < shapes.size(); i++) {
            shapes[i]->setPosition(sf::Vector2f(world.objects[i]->position_current.x, world.objects[i]->position_current.y));
        }


        world.update(frameTime);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                createObject(&world, 30.f, 250.f, 300.f, &shapes);
            }
        }

        window.clear(sf::Color::Black);
        window.draw(fpsText);
        window.draw(bg);

        for (int i = 0; i < shapes.size(); i++) {
           window.draw(*shapes[i]);
        }

        window.display();
    }

}
