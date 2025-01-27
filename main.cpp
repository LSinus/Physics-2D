#include <SFML/Graphics.hpp>
#include "physicsWorld.h"



void createObject(PhysicsWorld& world, float radius, float x, float y, std::vector<std::unique_ptr<sf::CircleShape>>& shapes) {
    // Create physics object
    auto physicsObj = std::make_unique<PhysicsObject>(radius, x, y);

    // Create graphics object
    auto shape = std::make_unique<sf::CircleShape>(radius);
    shape->setFillColor(sf::Color::White);
    shape->setOrigin(shape->getRadius(), shape->getRadius());
    shape->setPosition(x, y);

    // Add to world and shapes vector
    world.addObject(std::move(physicsObj));
    shapes.push_back(std::move(shape));
}

int main()
{
    // create the window (remember: it's safer to create it in the main thread due to OS limitations)
    sf::RenderWindow window(sf::VideoMode({800, 700}), "Physics-2D");

    sf::Clock clock;
    sf::Time deltaTime;
    float frameTime;
    float fps = 0.f;

    std::vector<std::unique_ptr<sf::CircleShape>> shapes;

    PhysicsWorld world;
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

        const auto& world_objects = world.getObjects();
        for (int i = 0; i < shapes.size(); i++) {
            shapes[i]->setPosition(sf::Vector2f(
                world_objects[i]->getPosition().x,
                world_objects[i]->getPosition().y
            ));
        }


        world.update(frameTime);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                createObject(world, 30.f, 250.f, 300.f, shapes);
            }
        }

        window.clear(sf::Color::Black);
        window.draw(bg);

        for (int i = 0; i < shapes.size(); i++) {
           window.draw(*shapes[i]);
        }

        window.display();
    }

}
