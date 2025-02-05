#include <SFML/Graphics.hpp>
#include <iostream>
#include "physicsWorld.h"
#include "external/imgui/imgui.h"
#include "external/imgui-sfml/imgui-SFML.h"
#include "utils.h"


int main(){
    sf::RenderWindow window(sf::VideoMode({800, 750}), "Physics-2D");
    if (!ImGui::SFML::Init(window, true)) {
        std::cerr << "Failed to initialize IMGUI!" << std::endl;
        return -1;
    }

    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    sf::Clock clock;
    sf::Time deltaTime;
    float frameTime;


    std::vector<std::unique_ptr<sf::CircleShape>> shapes;

    PhysicsWorld world;
    window.setFramerateLimit(60);

    sf::CircleShape bg(300.f);
    bg.setFillColor(sf::Color::Blue);
    bg.setOrigin({bg.getRadius(), bg.getRadius()});
    bg.setPointCount(200);
    bg.setPosition({400.f, 350.f});

    //createObject(world, shapes, 10.f, 250.f, 400.f, true);
    float radius = 10.0f;
    sf::Clock deltaClock;
    while (window.isOpen())
    {

        const auto& world_objects = world.getObjects();
        deltaTime = clock.restart();
        frameTime = deltaTime.asSeconds();

        for (int i = 0; i < shapes.size(); i++) {
            shapes[i]->setPosition(sf::Vector2f(
                world_objects[i]->getPosition().x,
                world_objects[i]->getPosition().y
            ));
        }

        world.update(frameTime);


        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
                window.close();

            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
                if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                    createObject(world, shapes, radius, 330.f, 100.f);
                }

                if (keyPressed->scancode == sf::Keyboard::Scancode::L) {
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



        }

        ImGui::NewFrame();
        ImGui::Begin("Info");
        ImGui::Text("FPS: %f", 1/frameTime);
        ImGui::Text("Objects: %d", world.getObjects().size());
        ImGui::End();

        ImGui::Begin("USAGE");
        ImGui::Text("Use Spacebar to spawn balls, Use L to try the chain");
        ImGui::End();

        ImGui::Begin("Settings");
        ImGui::SliderFloat("Radius:", &radius, 10.0f, 40.0f);
        if (ImGui::Button("Reset")) {
            world.reset();
            shapes.clear();
        }

        ImGui::End();


        window.clear(sf::Color::Black);
        window.draw(bg);

        for (int i = 0; i < shapes.size(); i++) {
           window.draw(*shapes[i]);
        }

        ImGui::SFML::Render(window);

        window.display();

    }

    ImGui::SFML::Shutdown();

}
