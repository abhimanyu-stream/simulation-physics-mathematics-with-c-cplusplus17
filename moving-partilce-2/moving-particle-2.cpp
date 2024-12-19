#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
/***
a C++ simulation program that moves slow particles in pairs, allowing them to collide. The program will be set up for Windows using CMake, MinGW, and g++.
I'll also provide a CMakeLists.txt file and a preset.json configuration for convenience


 */
struct Particle
{
    float x, y;   // Position
    float vx, vy; // Velocity
    float radius; // Radius of the particle
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
    if (p.x < 0 || p.x > boundaryX)
        p.vx = -p.vx;
    if (p.y < 0 || p.y > boundaryY)
        p.vy = -p.vy;
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int numPairs = 5;
    const float boundaryX = 100.0f;
    const float boundaryY = 100.0f;
    const float particleRadius = 1.0f;
    const float maxVelocity = 0.1f;

    std::vector<Particle> particles;
    for (int i = 0; i < numPairs * 2; ++i)
    {
        particles.push_back({static_cast<float>(std::rand() % 100),
                             static_cast<float>(std::rand() % 100),
                             static_cast<float>((std::rand() % 100) / 100.0f * maxVelocity - maxVelocity / 2),
                             static_cast<float>((std::rand() % 100) / 100.0f * maxVelocity - maxVelocity / 2),
                             particleRadius});
    }

    for (int t = 0; t < 1000; ++t)
    {
        std::cout << "Time Step " << t << ":\n";
        for (size_t i = 0; i < particles.size(); ++i)
        {
            moveParticle(particles[i], boundaryX, boundaryY);

            for (size_t j = i + 1; j < particles.size(); ++j)
            {
                if (checkCollision(particles[i], particles[j]))
                {
                    std::cout << "Collision detected between particles " << i << " and " << j << "\n";
                }
            }
            std::cout << "Particle " << i << ": (" << particles[i].x << ", " << particles[i].y << ")\n";
        }
    }

    return 0;
}
