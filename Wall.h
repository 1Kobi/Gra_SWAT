#ifndef WALL_H
#define WALL_H
#include "graphicalobject.h"

class Wall : public GraphicalObject
{
private:

public:
    Wall(sf::IntRect rect, sf::Vector2f pos, sf::Vector2f scale, sf::Texture* texture, bool is_repeated)
        : GraphicalObject(texture, pos, is_repeated, rect, scale)
    {}
};

#endif // WALL_H
