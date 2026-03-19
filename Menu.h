#ifndef MENU_H
#define MENU_H
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "enumy.h"
#include <iostream>
using namespace std;

class Menu {
private:
    sf::RenderWindow& window;
    std::vector<std::unique_ptr<sf::RectangleShape>> przyciski;
    sf::Font font;
    std::vector<std::unique_ptr<sf::Text>> tekst;
    status_menu status;
    sf::Text text;
    int poziom_trudnosci=1;
    sf::Vector2f wielkosc_przycisku = sf::Vector2f(400, 100);
    sf::Texture textura_1, textura_2;
    Wybrana_Bron wybrana_bron=karabin;

public:
    Menu(sf::RenderWindow& _window) : window(_window)
    {
        if (!font.loadFromFile("Roboto-Black.ttf"))
        {
            std::cerr << "Błąd wczytania czcionki!" << std::endl;
        }
        status = strona_glowna;

        text.setFont(font);

        przyciski.reserve(9);
        tekst.reserve(10);

        //menu_graj przycisk[0]
        przyciski.emplace_back(new sf::RectangleShape(wielkosc_przycisku));
        przyciski.back()->setFillColor(sf::Color::Green);
        przyciski.back()->setPosition(window.getSize().x / 2 - wielkosc_przycisku.x/2, window.getSize().y / 2 - wielkosc_przycisku.y-50);

        //menu_info przycisk[1]
        przyciski.emplace_back(new sf::RectangleShape(wielkosc_przycisku));
        przyciski.back()->setFillColor(sf::Color::Cyan);
        przyciski.back()->setPosition(window.getSize().x / 2 - wielkosc_przycisku.x/2, window.getSize().y / 2);

        //menu_wyjdz przycisk[2]
        przyciski.emplace_back(new sf::RectangleShape(wielkosc_przycisku));
        przyciski.back()->setFillColor(sf::Color::Red);
        przyciski.back()->setPosition(window.getSize().x / 2 - wielkosc_przycisku.x/2, window.getSize().y / 2 + wielkosc_przycisku.y+50);

        //info_cofnij przycisk[3]
        przyciski.emplace_back(new sf::RectangleShape(wielkosc_przycisku));
        przyciski.back()->setFillColor(sf::Color::White);
        przyciski.back()->setPosition(window.getSize().x / 20, window.getSize().y-window.getSize().y/10);

        //graj_latwy przycisk[4]
        przyciski.emplace_back(new sf::RectangleShape(wielkosc_przycisku));
        przyciski.back()->setPosition(window.getSize().x / 4 - wielkosc_przycisku.x, window.getSize().y/10);

        //graj_sredni przycisk[5]
        przyciski.emplace_back(new sf::RectangleShape(wielkosc_przycisku));
        przyciski.back()->setPosition(window.getSize().x / 4, window.getSize().y / 10);

        //graj_trudny przycisk[6]
        przyciski.emplace_back(new sf::RectangleShape(wielkosc_przycisku));
        przyciski.back()->setPosition(window.getSize().x / 4 + wielkosc_przycisku.x, window.getSize().y/10);

        //graj_karabin przycisk[7]
        przyciski.emplace_back(new sf::RectangleShape(sf::Vector2f(300,300)));
        przyciski.back()->setOrigin(wielkosc_przycisku.x/2, wielkosc_przycisku.y/2);
        przyciski.back()->setPosition(window.getSize().x / 2 - wielkosc_przycisku.x, window.getSize().y / 3.5);
        if (!textura_1.loadFromFile("AK.png"))
        {
            std::cerr << "Błąd wczytania karabinu!" << std::endl;
        }
        przyciski.back()->setTexture(&textura_1);

        //graj_strzelba przycisk[8]
        przyciski.emplace_back(new sf::RectangleShape(sf::Vector2f(300,300)));
        przyciski.back()->setOrigin(wielkosc_przycisku.x/2, wielkosc_przycisku.y/2);
        przyciski.back()->setPosition(window.getSize().x / 2 + wielkosc_przycisku.x, window.getSize().y/3.5);
        if (!textura_2.loadFromFile("Shotgun.png"))
        {
            std::cerr << "Błąd wczytania strzelby!" << std::endl;
        }
        przyciski.back()->setTexture(&textura_2);

        std::vector<std::string> buttonLabels = {"Graj", "Info", "Wyjdz", "Cofnij", "Latwy", "Sredni", "Trudny"};
        for (size_t i = 0; i < przyciski.size()-2; ++i)
        {
            text.setString(buttonLabels[i]);
            text.setCharacterSize(40);
            text.setFillColor(sf::Color::Black);
            text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2);
            text.setPosition(przyciski[i]->getPosition() + wielkosc_przycisku / 2.f);
            tekst.emplace_back(new sf::Text(text));
        }

        //gra_trudnosc tekst[7]
        text.setString("Wybierz poziom trudnosci:");
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2);
        text.setPosition(sf::Vector2f(200.f,50.f));
        tekst.emplace_back(new sf::Text(text));

        //gra_wybierz bron glowna tekst[8]
        text.setString("Wybierz bron glowna:");
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2);
        text.setPosition(sf::Vector2f(170.f,300.f));
        tekst.emplace_back(new sf::Text(text));

        //info_text tekst[9]
        text.setString("Celem gry jest zlikwidowanie wszystkich przeciwnikow na mapie.\n"
                       "Punkty przyznawane sa za ilosc zlikwidowanych przeciwnikow oraz za czas pokonania wszystkich - im mniej czasu tym wiecej punktow.\n"
                       "Ujemne punkty przyznawane sa za stracone punkty zycia gracza.\n"
                       "Ilosc przeciwnikow, ich bron oraz pozycja na mapie sa losowane przy kazdej nowej grze.\n"
                       "Przy rozpoczeniu gry nalezy wybrac poziom trudnosci, ktory wplywa na zachowanie przeciwnikow oraz koncowa punktacje.\n"
                       "Do wyboru sa dwie bronie glowne: karabin oraz strzelba.\n"
                       "Kazda bron ma okreslona - szybkostrzelnosc, celnosc, obrazenia oraz ilosc amunicji:\n"
                       "Karabin: 30 + 90 w zapasie.\n"
                       "Strzelba: 6 + 18 w zapasie.\n"
                       "Pistolet: 9 + 27 w zapasie.\n"
                       "Ilosc amunicji, tak jak w prawdziwym zyciu, dobry operator liczy sam.\n"
                       "Chodzenie oraz bieganie wplywaja na celnosc broni.\n"
                       "Przyciski:\n\n"
                       "1, 2, 3 - wybor broni.\n"
                       "R - przeladowanie.\n"
                       "F - walka wrecz.\n"
                       "Shift - sprint.\n");
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2);
        text.setPosition(window.getSize().x/2,window.getSize().y/3);
        tekst.emplace_back(new sf::Text(text));

        //pauza
        przyciski.emplace_back(new sf::RectangleShape(sf::Vector2f(200.f,80.f)));
        text.setString("Wyjdz");
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);
        text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2);
        tekst.emplace_back(new sf::Text(text));

        //tekst 10 czas w grze
        text.setString("");
        tekst.emplace_back(new sf::Text(text));
    }

    void draw() {
        switch (status)
        {
        case strona_glowna:
            for (size_t i = 0; i < 3; i++)
            {
                window.draw(*przyciski[i]);
                window.draw(*tekst[i]);
            }
            break;
        case info:
            window.draw(*przyciski[3]);
            window.draw(*tekst[3]);
            window.draw(*tekst[9]);
            break;
        case graj:
            for (size_t i = 4; i < 9; i++)
            {
                if(poziom_trudnosci==1)
                {
                    przyciski[4]->setFillColor(sf::Color::Green);
                    przyciski[5]->setFillColor(sf::Color(128, 128, 128));
                    przyciski[6]->setFillColor(sf::Color(128, 128, 128));
                }
                else if(poziom_trudnosci==2)
                {
                    przyciski[4]->setFillColor(sf::Color(128, 128, 128));
                    przyciski[5]->setFillColor(sf::Color::Yellow);
                    przyciski[6]->setFillColor(sf::Color(128, 128, 128));
                }
                else if(poziom_trudnosci==3)
                {
                    przyciski[4]->setFillColor(sf::Color(128, 128, 128));
                    przyciski[5]->setFillColor(sf::Color(128, 128, 128));
                    przyciski[6]->setFillColor(sf::Color::Red);
                }
                if(wybrana_bron==1)
                {
                    przyciski[8]->setFillColor(sf::Color::White);
                    przyciski[7]->setFillColor(sf::Color(100, 100, 100));
                }
                else
                {
                    przyciski[8]->setFillColor(sf::Color(100, 100, 100));
                    przyciski[7]->setFillColor(sf::Color::White);
                }
                window.draw(*przyciski[i]);
                window.draw(*tekst[i]);
            }
            window.draw(*przyciski[3]);//cofnij
            window.draw(*tekst[3]);
            przyciski[0]->setPosition(window.getSize().x - window.getSize().x / 4, window.getSize().y-window.getSize().y/10);
            window.draw(*przyciski[0]);//graj
            tekst[0]->setPosition(przyciski[0]->getPosition() + wielkosc_przycisku / 2.f);
            window.draw(*tekst[0]);
            break;
        }
    }

    unique_ptr<sf::RectangleShape> get_przycisk()
    {
        return std::make_unique<sf::RectangleShape>(*przyciski[9]);
    }

    unique_ptr<sf::Text> get_tekst()
    {
        return std::make_unique<sf::Text>(*tekst[10]);
    }

    void przyciski_obsluga(const sf::Event& event, Stan_Gry& stan) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            switch (status) {
            case strona_glowna:
                if (przyciski[0]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    status = graj;
                } else if (przyciski[1]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    status = info;
                } else if (przyciski[2]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                }
                break;
            case info:
                if (przyciski[3]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    status = strona_glowna;
                }
                break;
            case graj:
                if (przyciski[3]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    przyciski[0]->setPosition(window.getSize().x / 2 - wielkosc_przycisku.x / 2, window.getSize().y / 2 - wielkosc_przycisku.y - 50);
                    tekst[0]->setPosition(przyciski[0]->getPosition() + wielkosc_przycisku / 2.f);
                    status = strona_glowna;
                } else if (przyciski[4]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    poziom_trudnosci = 1;
                } else if (przyciski[5]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    poziom_trudnosci = 2;
                } else if (przyciski[6]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    poziom_trudnosci = 3;
                }
                if (przyciski[7]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    wybrana_bron = karabin;
                }
                if (przyciski[8]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    wybrana_bron = strzelba;
                }
                if (przyciski[0]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    stan = Stan_Gry::Rozgrywka;
                }
                break;
            }
        }
    }

    void set_status(status_menu &stat)
    {
        status=stat;
    }

    Wybrana_Bron get_bron()
    {
        return wybrana_bron;
    }

    int get_trudnosc()
    {
        return poziom_trudnosci;
    }

    void podsumowanie(int ilosc_przeciwnikow, int zycie, int czas)
    {

        sf::View originalView = window.getView();
        window.setView(window.getDefaultView());

        sf::String sfText = tekst[10]->getString();
        std::string slowo = sfText.toAnsiString();
        int stracone_zycie=100-zycie;

        int minut_5=300;

        string poziom;
        if(poziom_trudnosci==1)
        {
            poziom="Latwy";
        }
        else if(poziom_trudnosci==2)
        {
            poziom="Sredni";
        }
        else
        {
            poziom="Trudny";
        }
        string stan_gry;

        if(zycie==0)
        {
            stan_gry="Przegrana";
        }
        else
        {
            stan_gry="Wygrana";
        }

        int suma = ilosc_przeciwnikow*1000-stracone_zycie*50+(minut_5-czas)*10+poziom_trudnosci*1000;
        std::vector<std::string> dane = {stan_gry," ", "Ilosc zabitych przeciwnikow: ", to_string(ilosc_przeciwnikow),"Czas[s]: ", to_string(czas), "Stracone zycie: ",
                                         to_string(stracone_zycie),"Poziom trudnosci: ", poziom, "Suma punktow: ", to_string(suma)};

        sf::Vector2f miejsce;
        miejsce.y=170;
        miejsce.x=750;
        for (size_t i = 0; i < dane.size(); ++i)
        {
            text.setString(dane[i]);
            text.setCharacterSize(30);
            text.setFillColor(sf::Color::Black);
            text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2);
            if(i%2==0)
            {
                miejsce.y+=120;
                text.setPosition(miejsce.x+110, miejsce.y);
            }
            else
            {
                text.setPosition(miejsce.x+360, miejsce.y);
            }
            tekst.emplace_back(new sf::Text(text));
        }
        for (size_t i = 11; i < tekst.size(); ++i)
        {
            window.draw(*tekst[i]);
        }
        window.setView(originalView);
    }

    void usun_podsumowanie()
    {
        if (tekst.size() > 11)
        {
            tekst.erase(tekst.begin() + 11, tekst.end());
        }
    }
};


#endif // MENU_H
