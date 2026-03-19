#ifndef BACKGROUND_H
#define BACKGROUND_H
#include"graphicalobject.h"

class Background : public GraphicalObject
{
private:
    std::vector<Background> tla;
public:
    Background(sf::Texture* texture, sf::Vector2f pos, bool is_repeated, sf::IntRect kwadrat)
        : GraphicalObject(texture, pos, is_repeated, kwadrat)
    {}

};

#endif // BACKGROUND_H
