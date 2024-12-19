#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<iostream>

class Fish
{
public:
    Fish(float x, float y, sf::Color color, float size)
        : position(x, y), color(color), size(size)
    {
        if (!texture.loadFromFile("assets/assets/fish.jpg"))
        {
            std::cout << "Error: Unable to load fish texture." << std::endl;
        }
        else
        {
            std::cout << "Fish texture loaded successfully." << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setPosition(position);

        if (texture.getSize().x > 0 && texture.getSize().y > 0)
        {
            sprite.setScale(size / texture.getSize().x, size / texture.getSize().y);
        }
        else
        {
            std::cerr << "Error: Invalid fish texture dimensions." << std::endl;
        }
    }

    void update()
    {
        // Fish swimming logic (random movement)
        position.x += (rand() % 3 - 1); // Random horizontal movement
        position.y += (rand() % 3 - 1); // Random vertical movement
        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Color color;
    float size;
};

class Bubble
{
public:
    Bubble(float x, float y) : position(x, y)
    {
        circle.setRadius(10);
        circle.setFillColor(sf::Color(255, 255, 255, 150)); // Semi-transparent white
        circle.setPosition(position);
    }

    void update()
    {
        position.y -= 1; // Move bubble upwards
        circle.setPosition(position);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(circle);
    }

private:
    sf::CircleShape circle;
    sf::Vector2f position;
};
/**
class Environment
{
public:
    Environment()
    {
        // Load assets for environment (grass, stone, etc.)
        if (!grassTexture.loadFromFile("assets/assets/grass.png") ||
            !stoneTexture.loadFromFile("assets/assets/stone.png"))
        {
            // Handle asset loading error
        }
    }

    void addBubble(float x, float y)
    {
        bubbles.push_back(Bubble(x, y));
    }

    void update()
    {
        // Update bubbles
        for (auto &bubble : bubbles)
        {
            bubble.update();
        }
    }

    void draw(sf::RenderWindow &window)
    {
        // Draw grass and stone
        sf::Sprite grassSprite(grassTexture);
        grassSprite.setPosition(0, 500);
        window.draw(grassSprite);

        sf::Sprite stoneSprite(stoneTexture);
        stoneSprite.setPosition(300, 520);
        window.draw(stoneSprite);

        // Draw bubbles
        for (auto &bubble : bubbles)
        {
            bubble.draw(window);
        }
    }

private:
    sf::Texture grassTexture, stoneTexture;
    std::vector<Bubble> bubbles;
};
 */
class Environment
{
public:
    Environment()
    {
        // Load assets for environment (grass, stone, etc.)
        if (!grassTexture.loadFromFile("assets/assets/grass.png") ||
            !stoneTexture.loadFromFile("assets/assets/stone.png"))
        {
            // Handle asset loading error
        }
    }

    void addBubble(float x, float y)
    {
        bubbles.push_back(Bubble(x, y));
    }

    void update()
    {
        // Update bubbles
        for (auto &bubble : bubbles)
        {
            bubble.update();
        }
    }

    void draw(sf::RenderWindow &window)
    {
        // Draw grass spanning the window width
        sf::Sprite grassSprite(grassTexture);
        grassSprite.setPosition(0, 500);
        float grassScaleX = static_cast<float>(window.getSize().x) / grassTexture.getSize().x;
        grassSprite.setScale(grassScaleX, 1); // Scale only the width, keep height the same
        window.draw(grassSprite);

        // Draw stone
        sf::Sprite stoneSprite(stoneTexture);
        stoneSprite.setPosition(300, 520);
        window.draw(stoneSprite);

        // Draw bubbles
        for (auto &bubble : bubbles)
        {
            bubble.draw(window);
        }
    }

private:
    sf::Texture grassTexture, stoneTexture;
    std::vector<Bubble> bubbles;
};

int main()
{
    srand(time(0)); // Seed for random number generation

    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fish Simulation");

    // Create some fish
    std::vector<Fish> fish;
    fish.push_back(Fish(100, 100, sf::Color::Red, 50));
    fish.push_back(Fish(200, 200, sf::Color::Blue, 60));
    fish.push_back(Fish(300, 300, sf::Color::Green, 40));

    // Create environment (bubbles, grass, stone)
    Environment environment;
    environment.addBubble(150, 400);
    environment.addBubble(200, 420);

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the simulation
        for (auto &f : fish)
        {
            f.update();
        }
        environment.update();

        // Clear the window
        window.clear(sf::Color::Cyan); // Water color

        // Draw the environment and fish
        environment.draw(window);
        for (auto &f : fish)
        {
            f.draw(window);
        }

        // Display everything
        window.display();
    }

    return 0;
}
