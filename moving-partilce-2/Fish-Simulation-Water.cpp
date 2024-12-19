#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// Fish class to represent individual fish
class Fish
{
public:
    string color;
    int size;
    int position;

    Fish(string c, int s, int p) : color(c), size(s), position(p) {}

    void swim(int width)
    {
        position = (position + 1) % width; // Swim right and wrap around
    }

    string getDisplay()
    {
        return color + string(size, '>');
    }
};

// Bubble class to represent bubbles
class Bubble
{
public:
    int position;

    Bubble(int p) : position(p) {}

    void rise(int height)
    {
        position = (position - 1 + height) % height; // Rise up and wrap around
    }

    string getDisplay()
    {
        return "o";
    }
};

// Environment setup
void displayEnvironment(vector<Fish> &fishes, vector<Bubble> &bubbles, int width, int height)
{
    vector<string> grid(height, string(width, ' '));

    // Add grasses and stones
    for (int i = 0; i < width; i++)
    {
        if (rand() % 10 < 2)
        {
            grid[height - 1][i] = '"'; // Grass
        }
        else if (rand() % 10 < 1)
        {
            grid[height - 1][i] = 'O'; // Stone
        }
    }

    // Place bubbles
    for (Bubble &bubble : bubbles)
    {
        if (bubble.position >= 0 && bubble.position < height)
        {
            grid[bubble.position][rand() % width] = bubble.getDisplay()[0];
        }
    }

    // Place fishes
    for (Fish &fish : fishes)
    {
        string display = fish.getDisplay();
        for (int i = 0; i < fish.size; i++)
        {
            int pos = (fish.position + i) % width;
            grid[rand() % (height - 1)][pos] = display[i];
        }
    }

    // Display the grid
    for (const string &row : grid)
    {
        cout << row << endl;
    }
}

int main()
{
    srand(time(0));

    int width = 40;
    int height = 20;

    // Create fishes
    vector<Fish> fishes = {
        Fish("Red", 3, 5),
        Fish("Blue", 2, 10),
        Fish("Green", 4, 15),
    };

    // Create bubbles
    vector<Bubble> bubbles = {
        Bubble(18),
        Bubble(16),
        Bubble(14),
    };

    // Run simulation
    while (true)
    {
        system("clear"); // Clear screen ("cls" on Windows, "clear" on Unix)

        // Update fishes and bubbles
        for (Fish &fish : fishes)
        {
            fish.swim(width);
        }
        for (Bubble &bubble : bubbles)
        {
            bubble.rise(height);
        }

        // Display environment
        displayEnvironment(fishes, bubbles, width, height);

        // Wait before next frame
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    return 0;
}
