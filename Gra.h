#ifndef GRA_H
#define GRA_H

#include "Background.h"
#include "Interfejs.h"
#include "Menu.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "Wall.h"
#include "Wrog.h"
#include <memory>
using namespace std;

class Gra
{
private:
    std::vector<std::unique_ptr<Wall>> sciany;
    sf::RenderWindow& window;
    Interfejs interfejs;
    Background podloga;
    Background asfalt;
    Gracz gracz;
    sf::Clock zegar;
    std::vector<std::unique_ptr<Wrog>> przeciwnicy;
    bool czy_kolizja=false;
    RandomNumberGenerator rng;
    std::vector<std::unique_ptr<Pociski>> pociski;

    sf::RectangleShape overlay;
    Stan_Gry stan_gry;
    class Menu menu;
    bool czy_wczytani_przeciwnicy=false;
    bool pauza=false;
    std::unique_ptr<sf::RectangleShape> przycisk;
    std::unique_ptr<sf::Text> tekst;

    sf::Clock czas_gry;
    sf::Time czas;
    int ilosc_przeciwnikow;
    int zabici;

public:
    Gra(sf::RenderWindow& _window, sf::Texture &tekstura_sciana, sf::Texture &tekstura_podloga, sf::Texture &tekstura_asfalt)
        : window(_window),
        interfejs(_window, gracz),
        podloga(&tekstura_podloga, sf::Vector2f(0,0), true, sf::IntRect(0, 0, 3000, 2000)),
        asfalt(&tekstura_asfalt, sf::Vector2f(-40,1000), true, sf::IntRect(0, 0, 3160, 640)),
        gracz({1000.f, 1150.f}, "survivor.png", karabin),
        zegar(),
        menu(_window)
    {
        overlay.setSize(sf::Vector2f(2200, 2200));
        overlay.setPosition(sf::Vector2f(-200,-200));
        overlay.setFillColor(sf::Color(100, 100, 100));
        tworzenie_mapy(tekstura_sciana);
        stan_gry=Stan_Gry::Menu;
        przycisk = menu.get_przycisk();
        tekst = menu.get_tekst();
    }

    void set_stan_gry(Stan_Gry &stan)
    {
        stan_gry=stan;
    }

    void tworzenie_mapy(sf::Texture &tekstura_sciana)
    {
        sf::Vector2f skala = sf::Vector2f(0.25f,0.25f);
        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 10, 10), sf::Vector2f(-200.f,-200.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 2000, 200), sf::Vector2f(0.f,1000.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 3280, 200), sf::Vector2f(680.f,1000.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 200, 4200), sf::Vector2f(-40.f,0.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 6320, 200), sf::Vector2f(-40.f,-40.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 200, 4200), sf::Vector2f(1500.f,0.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 200, 920), sf::Vector2f(450.f,780.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 3660, 200), sf::Vector2f(0.f,572.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 200, 2320), sf::Vector2f(1095.f,420.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 1000, 200), sf::Vector2f(165.f,375.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 200, 840), sf::Vector2f(165.f,180.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 500, 200), sf::Vector2f(440.f,290.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 650, 200), sf::Vector2f(750.f,290.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 200, 1700), sf::Vector2f(873.f,0.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 200, 1700), sf::Vector2f(400.f,0.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 1800, 200), sf::Vector2f(923.f,230.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 800, 200), sf::Vector2f(1145.f,750.f), skala, &tekstura_sciana, true));

        sciany.push_back(std::make_unique<Wall>(sf::IntRect(0, 0, 900, 200), sf::Vector2f(1280.f,540.f), skala, &tekstura_sciana, true));
    }

    void wyswietlanie()
    {

        window.draw(podloga);
        window.draw(asfalt);

        window.draw(gracz);
        wyswietl_przeciwnikow();

        for(const auto &s:pociski)
        {
            window.draw(*s);
        }
        for(const auto &s:sciany)
        {
            window.draw(*s);
        }
    }

    void obslugaZdarzen() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            if (stan_gry == Stan_Gry::Menu)
            {
                menu.przyciski_obsluga(event, stan_gry);
            }
            if (stan_gry == Stan_Gry::Rozgrywka && sf::Mouse::isButtonPressed(sf::Mouse::Left) && pauza==true)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
                if (przycisk->getGlobalBounds().contains(static_cast<sf::Vector2f>(worldPosition)))
                {
                    window.close();
                }
            }

            if (stan_gry == Stan_Gry::Rozgrywka && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                pauza = !pauza;
                rysujEkranPauzy();
            }
        }
    }

    void rysujEkranPauzy()
    {
        if (pauza) {
            window.draw(overlay);

            przycisk->setPosition(interfejs.get_view_center().x-przycisk->getSize().x/2, interfejs.get_view_center().y+przycisk->getSize().y);
            tekst->setPosition(przycisk->getPosition()+przycisk->getSize()/2.f);
            window.draw(*przycisk);
            window.draw(*tekst);

        }

    }

    void aktualizacja_rozgywki()
    {
        interfejs.widok_run(window, gracz);
        window.clear();

        gracz.rozgladanie(interfejs.kursor(window),zegar);
        sprawdzKolizje();
        gracz.czy_WSAD();
        atak_wrecz();
        gracz.wybor_akcji(zegar.getElapsedTime(), pociski);

        sprawdzKolizjePociskow();
        aktualizuj_pociski();

        wyswietlanie();

        sprawdzKolizje();

        interfejs.rysuj_zycie(window, gracz);

        gracz.usuwanie_danych();
        zegar.restart();
        czy_kolizja=false;

        window.display();
    }

    void Menu() {
        window.clear(sf::Color::Black);

        menu.draw();
    }

    void Podsumowanie()
    {
        window.clear(sf::Color::Black);

        window.draw(overlay);
        sf::View defaultView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
        window.setView(defaultView);
        przeciwnicy.clear();
        czy_wczytani_przeciwnicy=false;

        menu.podsumowanie(zabici ,gracz.get_hp(), czas.asSeconds());
    }

    void uruchom() {
        window.setFramerateLimit(144);
        while (window.isOpen())
        {
            obslugaZdarzen();

            switch (stan_gry)
            {
            case Stan_Gry::Menu:
                Menu();
                break;
            case Stan_Gry::Rozgrywka:
                gracz.bron_glowna(menu.get_bron());
                if(czy_wczytani_przeciwnicy==false)
                {
                    czas_gry.restart();
                    wczytaj_przeciwnikow();
                    interfejs.widok_ustawienie(gracz);
                    poziom_trudnosci();
                    czy_wczytani_przeciwnicy=true;
                }

                if (gracz.get_hp() <= 0)
                {
                    gracz.set_hp(0);
                    stan_gry = Stan_Gry::Podsumowanie;
                    zabici=ilosc_przeciwnikow-przeciwnicy.size();
                    czas=czas_gry.getElapsedTime();
                }
                else if(przeciwnicy.empty()==true)
                {
                    stan_gry = Stan_Gry::Podsumowanie;
                    zabici=ilosc_przeciwnikow;
                    czas=czas_gry.getElapsedTime();
                }

                else if(pauza==false)
                {
                    aktualizacja_rozgywki();
                }

                else
                {
                    rysujEkranPauzy();
                }
                break;
            case Stan_Gry::Podsumowanie:
                Podsumowanie();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    gracz.uzupelnij_ammo();
                    stan_gry = Stan_Gry::Menu;
                    gracz.set_hp(100);
                    gracz.setPosition({1000.f, 1150.f});
                    gracz.set_aktualna_bron();
                    menu.usun_podsumowanie();
                }
                break;
            }
            window.display();
        }
    }

    void poziom_trudnosci()
    {

        for(auto& enemy:przeciwnicy)
        {
            int poziom = menu.get_trudnosc();
            if(poziom==1)
            {
                enemy->set_poziom_trudnosci(2.f,0.f);
            }
            else if(poziom==2)
            {
                enemy->set_poziom_trudnosci(3.f,0.3f);
            }
            else
            {
                enemy->set_poziom_trudnosci(5.f,0.9f);
            }
        }
    }

    void sprawdzKolizjePociskow() {
        for (auto pociskIt = pociski.begin(); pociskIt != pociski.end();) {
            bool pociskUsuniety = false;

            for (const auto& sciana : sciany) {
                if ((*pociskIt)->getGlobalBounds().intersects(sciana->getGlobalBounds())) {
                    pociskIt = pociski.erase(pociskIt);
                    pociskUsuniety = true;
                    break;
                }
            }

            if (!pociskUsuniety) {
                if((*pociskIt)->getGlobalBounds().intersects(gracz.getGlobalBounds())) {
                    gracz.zabierz_zycie((*pociskIt)->get_dmg());
                    pociskIt = pociski.erase(pociskIt);
                    pociskUsuniety = true;
                }
            }

            if (!pociskUsuniety) {
                for (auto enemyIt = przeciwnicy.begin(); enemyIt != przeciwnicy.end(); ++enemyIt) {
                    if ((*pociskIt)->getGlobalBounds().intersects((*enemyIt)->getGlobalBounds())) {
                        (*enemyIt)->set_trafiony();
                        (*enemyIt)->zabierz_zycie((*pociskIt)->get_dmg());
                        pociskIt = pociski.erase(pociskIt);
                        pociskUsuniety = true;
                        if ((*enemyIt)->get_hp() <= 0) {
                            enemyIt = przeciwnicy.erase(enemyIt);
                        }
                        break;
                    }
                }
            }

            if (!pociskUsuniety) {
                ++pociskIt;
            }
        }
    }

    void sprawdzKolizje()
    {
        sf::FloatRect graczBounds = gracz.getGlobalBounds();

        for (const auto& sciana : sciany) {
            if (graczBounds.intersects(sciana->getGlobalBounds())) {
                czy_kolizja=true;

                gracz.kolizja_gracza(*sciana,zegar);
            }
        }
        for (auto& przeciwnik : przeciwnicy) {
            if (graczBounds.intersects(przeciwnik->getGlobalBounds())) {
                czy_kolizja=true;

                gracz.kolizja_gracza(*przeciwnik,zegar);
            }
        }
        if (!czy_kolizja) {
            gracz.kolizja_gracza(*sciany[0],zegar);
        }
    }

    void wczytaj_przeciwnikow()
    {
        int ilosc=rng.getRandomInt(5, 8);
        przeciwnicy.reserve(ilosc);

        std::vector<sf::Vector2f> dostepne_pozycje = {
                                                      {100.f, 90.f}, {300.f, 280.f}, {560.f,460.f}, {260.f, 500.f}, {90.f,500.f}, {740.f, 460.f}, {650.f, 300.f}, {560.f, 110.f},
                                                      {1050.f, 120.f},{1400.f, 120.f},{1400.f, 670.f},{370.f, 710.f},{990.f, 720.f},{920.f, 910.f}};
        for (int i = 0; i < ilosc; ++i)
        {
            sf::Vector2f pozycja;
            int wylosowana_bron=rng.getRandomInt(0, 2);
            int powtorzenia=0;
            do {

                pozycja = sf::Vector2f(rng.getRandomInt(100, 1440), rng.getRandomInt(100, 940));
                if(powtorzenia>=20)
                {
                    pozycja=dostepne_pozycje[(powtorzenia+wylosowana_bron)%20];
                }
                powtorzenia++;
            } while (czyKoliduje(pozycja));

            przeciwnicy.emplace_back(std::make_unique<Wrog>(pozycja, "terrorist.png", static_cast<Wybrana_Bron>(wylosowana_bron)));
        }
        ilosc_przeciwnikow=przeciwnicy.size();
    }

    bool czyKoliduje(const sf::Vector2f pozycja) {
        sf::FloatRect nowyPrzeciwnikBounds(sf::Vector2f(pozycja.x-75, pozycja.y-75), sf::Vector2f(150.f, 150.f));

        for (const auto& przeciwnik : przeciwnicy)
        {
            if (nowyPrzeciwnikBounds.intersects(przeciwnik->getGlobalBounds()))
            {
                return true;
            }
        }
        for(const auto& sciana : sciany)
        {
            if (nowyPrzeciwnikBounds.intersects(sciana->getGlobalBounds()))
            {
                return true;
            }
        }
        return false;
    }

    void wyswietl_przeciwnikow()
    {
        for(auto& enemy:przeciwnicy)
        {
            enemy->rozgladanie(gracz.getPosition(),zegar);
            enemy->wybor_akcji(zegar.getElapsedTime(), pociski);
            enemy->czy_widzi_gracza(gracz.getPosition(),sciany);
            if (enemy->get_widzi_gracza()==true)
            {
                window.draw(*enemy);
            }
        }
    }

    void aktualizuj_pociski()
    {
        auto it = pociski.begin();
        while (it != pociski.end())
        {
            (*it)->lot(zegar.getElapsedTime());
            if ((*it)->isOffScreen())
            {
                it = pociski.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void atak_wrecz()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            Wybrana_Bron bron_gracza = gracz.get_bron();
            sf::FloatRect graczBounds = gracz.getGlobalBounds();

            if(gracz.k_animacji()==true)
            {
                for (auto enemyIt = przeciwnicy.begin(); enemyIt != przeciwnicy.end();)
                {
                    if (graczBounds.intersects((*enemyIt)->getGlobalBounds()))
                    {
                        (*enemyIt)->set_trafiony();
                        if (bron_gracza == strzelba || bron_gracza == karabin)
                        {
                            (*enemyIt)->zabierz_zycie(45);
                        }
                        else if (bron_gracza == pistolet)
                        {
                            (*enemyIt)->zabierz_zycie(45);
                        }
                        else if (bron_gracza == noz)
                        {
                            (*enemyIt)->zabierz_zycie(100);
                        }

                        if ((*enemyIt)->get_hp() <= 0)
                        {
                            cout<<(*enemyIt)->get_hp()<<endl;
                            enemyIt = przeciwnicy.erase(enemyIt);
                        }
                        else
                        {
                            ++enemyIt;
                        }
                    }
                    else
                    {
                        ++enemyIt;
                    }
                }
            }
        }
    }
};

#endif // GRA_H
