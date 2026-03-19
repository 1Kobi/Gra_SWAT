#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
using namespace std;
#include "Gra.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Gra", sf::Style::Fullscreen, settings);

    sf::Texture tekstura_sciana;
    if (!tekstura_sciana.loadFromFile("sciana.jpg")){
        return -1;
    }
    sf::Texture tekstura_podloga;
    if (!tekstura_podloga.loadFromFile("Wood_11-512x512.png"))
    {
        return -1;
    }
    sf::Texture tekstura_asfalt;
    if (!tekstura_asfalt.loadFromFile("asfalt.png"))
    {
        return -1;
    }

    Gra gra(window, tekstura_sciana, tekstura_podloga, tekstura_asfalt);

    gra.uruchom();

    return 0;
}
