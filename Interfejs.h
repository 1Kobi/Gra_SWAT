#ifndef INTERFEJS_H
#define INTERFEJS_H

#include "Gracz.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Window/Cursor.hpp"
#include <iostream>
using namespace std;

class Interfejs
{
private:
    //kursor
    sf::Texture cursorTexture;
    sf::Image cursorImage;
    unsigned int originalWidth;
    unsigned int originalHeight;
    sf::Image resizedImage;
    sf::Texture smallCursorTexture;
    sf::Cursor cursor;
    sf::Vector2f cel;

    //widok
    sf::View view;
    sf::FloatRect mapBounds;
    sf::Vector2f viewSize;
    sf::Vector2f viewCenter;
    float minX;
    float maxX;
    float minY;
    float maxY;
    sf::RectangleShape zycie;
    sf::RectangleShape zyciewroga;

public:
    Interfejs(sf::RenderWindow& window, Gracz &gracz):
        zycie(sf::Vector2f(gracz.get_hp()*100, 200))
    {
        if (!cursorTexture.loadFromFile("kursor.png")) {
            cout<<"Błąd pliku kursora"<<endl;
        }
        cursorImage = cursorTexture.copyToImage();
        originalWidth = cursorImage.getSize().x;
        originalHeight = cursorImage.getSize().y;
        resizedImage.create(originalWidth / 2, originalHeight / 2);

        zycie.setFillColor(sf::Color::Red);
        zycie.setPosition(120.f,800.f);

        for (unsigned int y = 0; y < originalHeight; y += 2) {
            for (unsigned int x = 0; x < originalWidth; x += 2) {
                sf::Color pixelColor = cursorImage.getPixel(x, y);
                resizedImage.setPixel(x / 2, y / 2, pixelColor);
            }
        }
        smallCursorTexture.loadFromImage(resizedImage);
        if (!cursor.loadFromPixels(smallCursorTexture.copyToImage().getPixelsPtr(), smallCursorTexture.getSize(), {16, 16})) {
            cout<<"Błąd wczytania kursora"<<endl;
        }
        window.setMouseCursor(cursor);
    }

    sf::Vector2f kursor(sf::RenderWindow& window)
    {
        cel = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return cel;
    }

    void widok_ustawienie(Gracz const &gracz)
    {
        view=sf::View(sf::FloatRect(0, 0, 1360, 765));
        view.setCenter(gracz.getPosition());
        mapBounds = sf::FloatRect(-40.f, -40.f, 1580.f, 1360.f); // Rozmiar mapy
        viewSize = view.getSize();
        minX = mapBounds.left + viewSize.x / 2;
        maxX = mapBounds.left + mapBounds.width - viewSize.x / 2;
        minY = mapBounds.top + viewSize.y / 2;
        maxY = mapBounds.top + mapBounds.height - viewSize.y / 2;
    }

    void rysuj_zycie(sf::RenderWindow& window, Gracz  &gracz)
    {
        if(gracz.get_hp()>0)
        {
            sf::View originalView = window.getView();
            window.setView(window.getDefaultView());

            zycie.setPosition(10.f, 1040.f);
            zycie.setSize(sf::Vector2f(gracz.get_hp()*5,30));
            window.draw(zycie);

            window.setView(originalView);
        }
    }

    void widok_run(sf::RenderWindow& window, Gracz const &gracz)
    {
        viewCenter = gracz.getPosition();

        if (viewCenter.x < minX) {
            viewCenter.x = minX;
        } else if (viewCenter.x > maxX) {
            viewCenter.x = maxX;
        }

        if (viewCenter.y < minY) {
            viewCenter.y = minY;
        } else if (viewCenter.y > maxY) {
            viewCenter.y = maxY;
        }

        view.setCenter(viewCenter);
        window.setView(view);
    }

    sf::Vector2f get_view_center()
    {
        return viewCenter;
    }

    sf::View get_view()
    {
        return view;
    }
};

#endif // INTERFEJS_H
