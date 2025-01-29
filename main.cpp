#include <SFML/Graphics.hpp>
#include <iostream>
#include "physicsWorld.h"



std::shared_ptr<PhysicsObject> createObject(PhysicsWorld& world, std::vector<std::unique_ptr<sf::CircleShape>>& shapes,  float radius, float x, float y, bool isStatic = false, sf::Color color = sf::Color::White) {
    // Create physics object
    auto physicsObj = std::make_shared<PhysicsObject>(radius, x, y, isStatic);

    // Create graphics object
    auto shape = std::make_unique<sf::CircleShape>(radius);
    shape->setFillColor(color);
    shape->setOrigin(shape->getRadius(), shape->getRadius());
    shape->setPosition(x, y);

    // Add to world and shapes vector
    world.addObject(physicsObj);
    shapes.push_back(std::move(shape));

    return physicsObj;
}

int main()
{
    // create the window (remember: it's safer to create it in the main thread due to OS limitations)
    sf::RenderWindow window(sf::VideoMode({800, 700}), "Physics-2D");

    sf::Clock clock;
    sf::Time deltaTime;
    float frameTime;
    float fps = 0.f;

    sf::Font font;
    if (!font.loadFromFile("../font/arial.ttf")) {
        std::cerr << "Failed to load font!\n";
        return EXIT_FAILURE;
    }
    sf::Text fpsCounter;
    fpsCounter.setFont(font);
    fpsCounter.setString("Frametime:");
    fpsCounter.setCharacterSize(16);
    fpsCounter.setFillColor(sf::Color::White);
    fpsCounter.setPosition(10, 10);

    sf::Text objCounter;
    objCounter.setFont(font);               // Set the font
    objCounter.setString("Objects:");    // Set the string
    objCounter.setCharacterSize(16);        // Size in pixels
    objCounter.setFillColor(sf::Color::White); // Text color
    objCounter.setPosition(10, 30);

    sf::Text totalEnergy;
    totalEnergy.setFont(font);               // Set the font
    totalEnergy.setString("Objects:");    // Set the string
    totalEnergy.setCharacterSize(16);        // Size in pixels
    totalEnergy.setFillColor(sf::Color::White); // Text color
    totalEnergy.setPosition(10, 50);

    std::vector<std::unique_ptr<sf::CircleShape>> shapes;

    PhysicsWorld world;
    window.setFramerateLimit(60);

    sf::CircleShape bg(300.f);
    bg.setFillColor(sf::Color::Blue);
    bg.setOrigin(bg.getRadius(), bg.getRadius());
    bg.setPointCount(200);
    bg.setPosition(400.f, 350.f);

    //createObject(world, shapes, 10.f, 250.f, 400.f, true);

    while (window.isOpen())
    {

        const auto& world_objects = world.getObjects();

        deltaTime = clock.restart();
        frameTime = deltaTime.asSeconds();
        fps = 1 / frameTime;
        fpsCounter.setString("Frametime: " + std::to_string(deltaTime.asMilliseconds()) + "ms");
        objCounter.setString("Objects: " + std::to_string(world_objects.size()));
        totalEnergy.setString("Objects: " + std::to_string(world.getTotalEnergy()));


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
                createObject(world, shapes, 10.f, 330.f, 100.f);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L) {
                int i;
                auto obj1 = createObject(world, shapes, 15.f, 250.f, 450.f, true, sf::Color::Red);
                for (i = 1; i <= 10; i++) {
                    auto obj2 = createObject(world, shapes, 15.f, 250.f + i*30.f, 450.f, false, sf::Color::Red);
                    world.addLink(obj1, obj2);
                    obj1 = obj2;
                }
                auto obj = createObject(world, shapes, 15.f, 250.f +i*30.f, 450.f, true, sf::Color::Red);
                world.addLink(obj1, obj);

            }
        }

        window.clear(sf::Color::Black);
        window.draw(bg);

        for (int i = 0; i < shapes.size(); i++) {
           window.draw(*shapes[i]);
        }

        window.draw(fpsCounter);
        window.draw(objCounter);
        //window.draw(totalEnergy);
        window.display();
    }

}
