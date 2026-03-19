#ifndef WROG_H
#define WROG_H
#include "Postac.h"
#include "Wall.h"
#include "SFML/Graphics/CircleShape.hpp"

using namespace std;

class Wrog : public Postac
{
private:
    sf::CircleShape zasieg;
    bool strzelamy=false;
    float elapsedtime=0;
    bool widzi_gracza=false;
    RandomNumberGenerator rng;
    bool trafiony=false;
    float czas_animacja_trudnosc=0.f;
public:
    Wrog(sf::Vector2f &pos, string texture, Wybrana_Bron bron)
        : Postac(pos, texture, bron)
    {
        setRotation(rng.getRandomInt(0,360));
        zasieg.setRadius(400.f);
        zasieg.setOrigin(sf::Vector2f(0,zasieg.getGlobalBounds().height/2));
        aktualna_bron=bron;
        inicjalizacja_zmiennych();
        zasieg.setPosition(sf::Vector2f(getPosition().x,getPosition().y));
        zasieg.setRotation(getRotation());
        rotationSpeed = 3.f;
    }

    void inicjalizacja_zmiennych()
    {
        if(aktualna_bron==pistolet)
        {
            opoznienie=0.5f;
            predkosc_pocisku=3200.f;
            obrazenia_broni=25;
        }
        if(aktualna_bron==karabin)
        {
            opoznienie=0.1f;
            predkosc_pocisku=4000.f;
            obrazenia_broni=15;
        }
        if(aktualna_bron==strzelba)
        {
            opoznienie=1.f;
            predkosc_pocisku=3600.f;
            obrazenia_broni=10;
        }
        if(aktualna_bron==noz)
        {
            opoznienie=0.f;
            obrazenia_broni=100;
        }
    }

    void rozgladanie(const sf::Vector2f &cel, sf::Clock &zegar) override
    {
        pozycja = this->getPosition();
        kierunek_patrzenia = sf::Vector2f(cel.x - pozycja.x, cel.y - pozycja.y);
        float dlugosc = std::sqrt(kierunek_patrzenia.x * kierunek_patrzenia.x + kierunek_patrzenia.y * kierunek_patrzenia.y);

        if ((zasieg.getGlobalBounds().contains(cel)&&widzi_gracza==true)||trafiony==true)
        {
            if (dlugosc != 0)
            {
                kierunek_patrzenia.x /= dlugosc;
                kierunek_patrzenia.y /= dlugosc;
            }

            float targetAngle = std::atan2(kierunek_patrzenia.y, kierunek_patrzenia.x) * 180 / M_PI;
            float currentAngle = this->getRotation();

            if (targetAngle > 180.0f) targetAngle -= 360.0f;
            if (targetAngle < -180.0f) targetAngle += 360.0f;
            if (currentAngle > 180.0f) currentAngle -= 360.0f;
            if (currentAngle < -180.0f) currentAngle += 360.0f;

            float angleDifference = targetAngle - currentAngle;

            if (angleDifference > 180.0f) angleDifference -= 360.0f;
            if (angleDifference < -180.0f) angleDifference += 360.0f;


            if (std::abs(angleDifference) < rotationSpeed)
            {
                this->setRotation(targetAngle);
                trafiony=false;
                elapsedtime+=zegar.getElapsedTime().asSeconds();
                if(elapsedtime>1.f)
                {
                    strzelamy=true;
                    elapsedtime=0;
                }
            }
            else
            {
                if (angleDifference > 0)
                {
                    this->setRotation(currentAngle + rotationSpeed);
                }
                else
                {
                    this->setRotation(currentAngle - rotationSpeed);
                }
            }
            zasieg.setRotation(currentAngle + rotationSpeed);
        }
        else
        {
            strzelamy=false;
        }
    }

    virtual void wybor_akcji(const sf::Time &czas, std::vector<std::unique_ptr<Pociski>> &pociski) override
    {

        if(koniec_animacji)
        {
            if(strzelamy)
            {
                if(aktualna_bron==karabin&&dostepna_amuniacja_karabin>0)
                {
                    aktualna_klatka=-1;
                    ilosc_fps=40;
                    aktualna_animacja=strzal;
                    czas_animacja=-0.3f;
                    czas_animacja+=czas_animacja_trudnosc;
                    czy_ruch=true;
                    strzelanie(obrazenia_broni, pociski);
                    dostepna_amuniacja_karabin--;
                }
                if(aktualna_bron==strzelba&&dostepna_amuniacja_strzelba>0)
                {
                    aktualna_klatka=-1;
                    ilosc_fps=40;
                    aktualna_animacja=strzal;
                    czas_animacja=-0.3f;
                    czas_animacja+=czas_animacja_trudnosc;
                    czy_ruch=true;
                    strzelanie(obrazenia_broni, pociski);
                    dostepna_amuniacja_strzelba--;
                }
                if(aktualna_bron==pistolet&&dostepna_amuniacja_pistolet>0)
                {
                    aktualna_klatka=-1;
                    ilosc_fps=40;
                    aktualna_animacja=strzal;
                    czas_animacja=-0.3f;
                    czas_animacja+=czas_animacja_trudnosc;
                    czy_ruch=true;
                    strzelanie(obrazenia_broni, pociski);
                    dostepna_amuniacja_pistolet--;
                }
            }
            if(aktualna_bron==karabin&&dostepna_amuniacja_karabin==0&&ilosc_amunicji_karabin>0)
            {
                aktualna_klatka=-1;
                ilosc_fps=10;
                aktualna_animacja=przeladowanie;
                int roznica=30-dostepna_amuniacja_karabin;
                dostepna_amuniacja_karabin+=roznica;
                ilosc_amunicji_karabin-=roznica;
            }
            else if(aktualna_bron==strzelba&&dostepna_amuniacja_strzelba==0&&ilosc_amunicji_strzelba>0)
            {
                aktualna_klatka=-1;
                ilosc_fps=10;
                aktualna_animacja=przeladowanie;
                int roznica=6-dostepna_amuniacja_strzelba;
                dostepna_amuniacja_strzelba+=roznica;
                ilosc_amunicji_strzelba-=roznica;
            }
            else if(aktualna_bron==pistolet&&dostepna_amuniacja_pistolet==0&&ilosc_amunicji_pistolet>0)
            {
                aktualna_klatka=-1;
                ilosc_fps=10;
                aktualna_animacja=przeladowanie;
                int roznica=9-dostepna_amuniacja_pistolet;
                dostepna_amuniacja_pistolet+=roznica;
                ilosc_amunicji_pistolet-=roznica;
            }
            else
            {
                czy_ruch=false;
                czy_sprint=false;
            }

            wektor_animacji = pobierz_animacje(aktualna_bron, aktualna_animacja);

            if(aktualna_animacja==chod)
            {
                animacja_chod(czas, wektor_animacji);
            }
            else
            {
                if (!wektor_animacji)
                {
                    wektor_animacji = pobierz_animacje(aktualna_bron, chod);
                    animacja_chod(czas, wektor_animacji);
                }
                else
                {
                    animacja(czas, wektor_animacji, ilosc_fps, opoznienie);
                }
            }
        }
        else
        {
            animacja(czas, wektor_animacji, ilosc_fps, opoznienie);
        }
    }

    bool kolizja_linii(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::FloatRect& rect) {
        sf::Vector2f corners[4] = {
            {rect.left, rect.top},
            {rect.left + rect.width, rect.top},
            {rect.left + rect.width, rect.top + rect.height},
            {rect.left, rect.top + rect.height}
        };

        for (int i = 0; i < 4; ++i) {
            int next = (i + 1) % 4;
            if (linia_przecina(p1, p2, corners[i], corners[next])) {
                return true;
            }
        }
        return false;
    }

    bool linia_przecina(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, const sf::Vector2f& p4) {
        auto orientation = [](const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c) {
            float val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
            if (val == 0) return 0;
            return (val > 0) ? 1 : 2;
        };

        int o1 = orientation(p1, p2, p3);
        int o2 = orientation(p1, p2, p4);
        int o3 = orientation(p3, p4, p1);
        int o4 = orientation(p3, p4, p2);

        if (o1 != o2 && o3 != o4) return true;
        return false;
    }

    void czy_widzi_gracza(sf::Vector2f cel, std::vector<std::unique_ptr<Wall>> &sciany)
    {
        sf::Vector2f pozycja = this->getPosition();
        widzi_gracza = true;

        for (const auto& sciana : sciany) {
            if (kolizja_linii(pozycja, cel, sciana->getGlobalBounds()))
            {
                widzi_gracza = false;
                break;
            }
        }
    }

    int get_hp()
    {
        return hp;
    }

    void set_trafiony()
    {
        trafiony=true;
    }

    bool get_widzi_gracza()
    {
        return widzi_gracza;
    }

    void set_poziom_trudnosci(float v_obracania, float czas)
    {
        rotationSpeed=v_obracania;
        czas_animacja_trudnosc=czas;
    }
};

#endif // WROG_H
