#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

struct WaterParticle
{
    float x, y;            // Position
    sf::CircleShape shape; // Visual representation
};

void createWaterParticle(std::vector<WaterParticle> &particles, float x, float y, float radius)
{
    WaterParticle particle;
    particle.x = x;
    particle.y = y;
    particle.shape = sf::CircleShape(radius);
    particle.shape.setPosition(x, y);
    particle.shape.setFillColor(sf::Color::Blue);
    particles.push_back(particle);
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Simulation and window properties
    const float windowWidth = 800.0f;
    const float windowHeight = 600.0f;
    const float vesselWidth = 300.0f;
    const float vesselHeight = 500.0f;
    const float vesselX = (windowWidth - vesselWidth) / 2.0f;
    const float vesselY = windowHeight - vesselHeight;
    const float particleRadius = 5.0f;
    const float fillSpeed = 3.0f;     // Number of particles per frame
    const float overflowSpeed = 1.0f; // Speed at which overflow particles fall

    // SFML window
    sf::RenderWindow window(sf::VideoMode(static_cast<int>(windowWidth), static_cast<int>(windowHeight)), "Water Filling Simulation");
    window.setFramerateLimit(60);

    // Vessel (container)
    sf::RectangleShape vessel(sf::Vector2f(vesselWidth, vesselHeight));
    vessel.setPosition(vesselX, vesselY);
    vessel.setFillColor(sf::Color::Transparent);
    vessel.setOutlineColor(sf::Color::White);
    vessel.setOutlineThickness(2);

    // Water particles
    std::vector<WaterParticle> waterParticles;
    float fillLevel = windowHeight; // Start from the bottom of the screen

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Fill the vessel
        if (fillLevel > vesselY)
        {
            for (int i = 0; i < fillSpeed; ++i)
            {
                float x = vesselX + static_cast<float>(std::rand() % static_cast<int>(vesselWidth));
                createWaterParticle(waterParticles, x, fillLevel - particleRadius, particleRadius);
            }
            fillLevel -= particleRadius;
        }

        // Simulate overflow
        for (auto &particle : waterParticles)
        {
            if (particle.y < vesselY)
            {
                particle.y += overflowSpeed;
                particle.shape.setPosition(particle.x, particle.y);
            }
        }

        // Render everything
        window.clear();
        window.draw(vessel);
        for (const auto &particle : waterParticles)
        {
            window.draw(particle.shape);
        }
        window.display();
    }

    return 0;
}
