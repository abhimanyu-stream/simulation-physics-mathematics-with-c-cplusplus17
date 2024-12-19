#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct WaterParticle
{
    float x, y;            // Position
    sf::CircleShape shape; // Rendered as a circle
};

void createParticle(std::vector<WaterParticle> &particles, float x, float y, float radius, sf::Color color)
{
    WaterParticle particle;
    particle.x = x;
    particle.y = y;
    particle.shape = sf::CircleShape(radius);
    particle.shape.setPosition(x, y);
    particle.shape.setFillColor(color);
    particles.push_back(particle);
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Window and vessel dimensions
    const float windowWidth = 800.0f;
    const float windowHeight = 600.0f;
    const float vesselWidth = 200.0f;
    const float vesselHeight = 400.0f;
    const float vesselX = (windowWidth - vesselWidth) / 2;
    const float vesselY = windowHeight - vesselHeight;

    // Water particle properties
    const float particleRadius = 5.0f;
    const float fillSpeed = 5.0f;      // Water filling speed (particles/frame)
    const float shakeAmplitude = 5.0f; // Maximum horizontal shaking
    const float shakeFrequency = 0.1f; // Oscillation speed

    // Overflow threshold
    const float overflowThreshold = vesselY;

    // Create window
    sf::RenderWindow window(sf::VideoMode(static_cast<int>(windowWidth), static_cast<int>(windowHeight)), "Water Simulation");
    window.setFramerateLimit(60);

    // Vessel rectangle
    sf::RectangleShape vessel(sf::Vector2f(vesselWidth, vesselHeight));
    vessel.setPosition(vesselX, vesselY);
    vessel.setFillColor(sf::Color::Transparent);
    vessel.setOutlineColor(sf::Color::White);
    vessel.setOutlineThickness(2);

    // Particles representing water
    std::vector<WaterParticle> waterParticles;

    // Time and simulation variables
    float fillLevel = windowHeight; // Initial fill level (start from bottom)
    float shakeTime = 0.0f;         // Time variable for sinusoidal shaking

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

        // Simulate filling water
        if (fillLevel > vesselY)
        {
            for (int i = 0; i < fillSpeed; ++i)
            {
                float x = vesselX + (std::rand() % static_cast<int>(vesselWidth));
                float y = fillLevel - particleRadius * 2;
                createParticle(waterParticles, x, y, particleRadius, sf::Color::Blue);
            }
            fillLevel -= particleRadius; // Lower the fill level
        }

        // Simulate shaking
        shakeTime += shakeFrequency;
        float offsetX = std::sin(shakeTime) * shakeAmplitude;

        // Update particle positions (simulate shaking and overflow)
        for (auto &particle : waterParticles)
        {
            particle.x += offsetX * (particle.y > overflowThreshold ? 1 : 0.1f); // Stronger shake above threshold
            if (particle.y < overflowThreshold)
            {
                particle.y -= 0.5f; // Simulate gravity pulling overflow particles down
            }
            particle.shape.setPosition(particle.x, particle.y);
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
