#include <SFML/Graphics.hpp>

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(400, 600), "Water Overflow Simulation");

    // Define the cup (a rectangle with a border)
    sf::RectangleShape cup(sf::Vector2f(200, 300));
    cup.setPosition(100, 200);
    cup.setFillColor(sf::Color::Transparent);
    cup.setOutlineThickness(5);
    cup.setOutlineColor(sf::Color::White);

    // Define the water (another rectangle)
    sf::RectangleShape water(sf::Vector2f(200, 0)); // Initially no height
    water.setPosition(100, 500);
    water.setFillColor(sf::Color::Blue);

    // Water level increment
    float waterLevel = 0;
    const float maxWaterLevel = 300; // Matches the cup height
    const float increment = 0.5f;

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update water level
        if (waterLevel < maxWaterLevel + 50)
        { // Overflow
            waterLevel += increment;
            water.setSize(sf::Vector2f(200, waterLevel));
            water.setPosition(100, 500 - waterLevel);
        }

        // Clear and draw
        window.clear(sf::Color::Black);
        window.draw(cup);
        window.draw(water);
        window.display();
    }

    return 0;
}
