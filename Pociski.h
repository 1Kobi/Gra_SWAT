#ifndef POCISKI_H
#define POCISKI_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Time.hpp"
#include <cmath>

class Pociski : public sf::RectangleShape
{
private:
    sf::Vector2f kierunek;
    float predkosc;
    int obrazenia;
public:
    Pociski(sf::Vector2f &pozycja, float &v, sf::Vector2f &kier, int &obrazenia)
        : sf::RectangleShape(sf::Vector2f(6.f, 3.f)), predkosc(v), obrazenia(obrazenia)
    {
        setSize(sf::Vector2f(6.f, 3.f));
        setFillColor(sf::Color::Black);
        setPosition(pozycja);
        predkosc=v;
        kierunek=kier/std::sqrt(kier.x * kier.x + kier.y * kier.y);
        setRotation(std::atan2(kier.y, kier.x) * 180 / M_PI);
        setPosition(getPosition().x+kierunek.x*100.f,getPosition().y+kierunek.y*100.f);
    }

    void lot(const sf::Time &czas)
    {
        move(kierunek*predkosc*czas.asSeconds());
    }

    bool isOffScreen() const
    {
        sf::Vector2f position = getPosition();
        return position.x < -40 || position.x > 1540 ||
               position.y < 0 || position.y > 1320;
    }

    int get_dmg()
    {
        return obrazenia;
    }
};

#endif // POCISKI_H
