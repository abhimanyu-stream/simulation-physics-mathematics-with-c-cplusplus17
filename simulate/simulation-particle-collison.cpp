#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Particle
{
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Particle(float radius, const sf::Vector2f &position, const sf::Vector2f &velocity)
        : velocity(velocity)
    {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void update(float deltaTime)
    {
        // Update position based on velocity
        shape.move(velocity * deltaTime);

        // Check for collisions with the window edges
        if (shape.getPosition().x <= 0 || shape.getPosition().x + shape.getRadius() * 2 >= 800)
        {
            velocity.x = -velocity.x; // Reverse X velocity
        }

        if (shape.getPosition().y <= 0 || shape.getPosition().y + shape.getRadius() * 2 >= 600)
        {
            velocity.y = -velocity.y; // Reverse Y velocity
        }
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }
};

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Simulation");

    // Create a particle at position (400, 300) with an initial velocity
    Particle particle(20.f, sf::Vector2f(400.f, 300.f), sf::Vector2f(200.f, 150.f));

    // Clock to track time for deltaTime
    sf::Clock clock;

    // Main loop
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the particle
        particle.update(deltaTime.asSeconds());

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw the particle
        particle.draw(window);

        // Display the window content
        window.display();
    }

    return 0;
}
