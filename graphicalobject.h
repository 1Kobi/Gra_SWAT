#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"


class GraphicalObject : public sf::Sprite
{

public:
    GraphicalObject(sf::Texture *texture, sf::Vector2f pos = sf::Vector2f(0, 0), bool is_repeated = true, sf::IntRect wielkosc=sf::IntRect(0,0,1280,720),
                    sf::Vector2f skala=sf::Vector2f(0.5f,0.5f))
    {
        if (!texture) {
            throw("Zły wskaźnik tekstury");
        }

        texture->setRepeated(is_repeated);
        setTexture(*texture);
        setScale(skala);
        setPosition(pos);
        setTextureRect(wielkosc);
    }

};

#endif // GRAPHICALOBJECT_H
