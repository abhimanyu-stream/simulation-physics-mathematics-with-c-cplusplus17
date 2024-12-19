#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct Particle
{
    float x, y;   // Position
    float vx, vy; // Velocity
    float radius; // Radius of the particle
    sf::Color color;
};

bool checkCollision(const Particle &p1, const Particle &p2)
{
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (p1.radius + p2.radius);
}

void moveParticle(Particle &p, float boundaryX, float boundaryY)
{
    p.x += p.vx;
    p.y += p.vy;

    // Bounce off walls
    if (p.x - p.radius < 0 || p.x + p.radius > boundaryX)
        p.vx = -p.vx;
    if (p.y - p.radius < 0 || p.y + p.radius > boundaryY)
        p.vy = -p.vy;
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int numPairs = 5;
    const float boundaryX = 800.0f; // Window width
    const float boundaryY = 600.0f; // Window height
    const float particleRadius = 10.0f;
    const float maxVelocity = 2.0f;

    std::vector<Particle> particles;
    for (int i = 0; i < numPairs * 2; ++i)
    {
        particles.push_back({static_cast<float>(std::rand() % static_cast<int>(boundaryX)),
                             static_cast<float>(std::rand() % static_cast<int>(boundaryY)),
                             static_cast<float>((std::rand() % 100) / 100.0f * maxVelocity - maxVelocity / 2),
                             static_cast<float>((std::rand() % 100) / 100.0f * maxVelocity - maxVelocity / 2),
                             particleRadius,
                             sf::Color::White});
    }

    sf::RenderWindow window(sf::VideoMode(static_cast<int>(boundaryX), static_cast<int>(boundaryY)), "Particle Simulation");
    window.setFramerateLimit(60);

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

        // Update particles
        for (size_t i = 0; i < particles.size(); ++i)
        {
            moveParticle(particles[i], boundaryX, boundaryY);

            for (size_t j = i + 1; j < particles.size(); ++j)
            {
                if (checkCollision(particles[i], particles[j]))
                {
                    particles[i].color = sf::Color::Red;
                    particles[j].color = sf::Color::Red;
                }
            }
        }

        // Render particles
        window.clear();
        for (const auto &particle : particles)
        {
            sf::CircleShape circle(particle.radius);
            circle.setPosition(particle.x - particle.radius, particle.y - particle.radius);
            circle.setFillColor(particle.color);
            window.draw(circle);
        }
        window.display();
    }

    return 0;
}
