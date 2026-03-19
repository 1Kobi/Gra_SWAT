#ifndef GRACZ_H
#define GRACZ_H
#include "Postac.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

using namespace std;

class Gracz : public Postac{
private:

    sf::Vector2f WSAD = sf::Vector2f(0.f,0.f);

public:
    Gracz(sf::Vector2f pos, string texture, Wybrana_Bron bron)
        : Postac(pos, texture, bron)
    {
        hp=100;
        rotationSpeed = 4.f;
    }

    void uzupelnij_ammo()
    {
        dostepna_amuniacja_karabin=30;
        ilosc_amunicji_karabin=90;
        dostepna_amuniacja_strzelba=6;
        ilosc_amunicji_strzelba=18;
        dostepna_amuniacja_pistolet=9;
        ilosc_amunicji_pistolet=27;
    }

    void bron_glowna(Wybrana_Bron bron)
    {
        if(bron==strzelba)
        {
            chod_glowna.clear();
            strzal_glowna.clear();
            atak_glowna.clear();
            przeladowanie_glowna.clear();
            wczytaj_strzelbe();
            inicjalizuj_animacje();
            wybrana_bron=bron;
        }
        else
        {
            chod_glowna.clear();
            strzal_glowna.clear();
            atak_glowna.clear();
            przeladowanie_glowna.clear();
            wczytaj_karabin();
            inicjalizuj_animacje();
            wybrana_bron=bron;
        }
    }

    virtual void wybor_akcji(const sf::Time &czas, std::vector<std::unique_ptr<Pociski>> &pociski) override
    {
        this->setOrigin(this->getLocalBounds().width/3,this->getLocalBounds().height/2);
        if(aktualna_bron==pistolet)
        {
            opoznienie=0.3f;
            predkosc_pocisku=3200.f;
            obrazenia_broni=26;
            velocity=90;
        }
        if(aktualna_bron==karabin)
        {
            opoznienie=0.1f;
            predkosc_pocisku=4000.f;
            obrazenia_broni=18;
            velocity=70;
        }
        if(aktualna_bron==strzelba)
        {
            opoznienie=0.7f;
            predkosc_pocisku=3600.f;
            obrazenia_broni=12;
            velocity=70;
        }
        if(aktualna_bron==noz)
        {
            opoznienie=0.f;
            obrazenia_broni=100;
            velocity=110;
        }

        if(koniec_animacji)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                aktualna_bron = wybrana_bron;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                aktualna_bron = pistolet;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                aktualna_bron = noz;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                aktualna_klatka=-1;
                ilosc_fps=24;
                aktualna_animacja=atak;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)&&aktualna_bron!=noz)
            {
                if(aktualna_bron==karabin&&dostepna_amuniacja_karabin<30&&ilosc_amunicji_karabin>0)
                {
                    aktualna_klatka=-1;
                    ilosc_fps=10;
                    aktualna_animacja=przeladowanie;
                    int roznica=30-dostepna_amuniacja_karabin;
                    dostepna_amuniacja_karabin+=roznica;
                    ilosc_amunicji_karabin-=roznica;
                }
                if(aktualna_bron==strzelba&&dostepna_amuniacja_strzelba<30&&ilosc_amunicji_strzelba>0)
                {
                    aktualna_klatka=-1;
                    ilosc_fps=10;
                    aktualna_animacja=przeladowanie;
                    int roznica=6-dostepna_amuniacja_strzelba;
                    dostepna_amuniacja_strzelba+=roznica;
                    ilosc_amunicji_strzelba-=roznica;
                }
                if(aktualna_bron==pistolet&&dostepna_amuniacja_pistolet<9&&ilosc_amunicji_pistolet>0)
                {
                    aktualna_klatka=-1;
                    ilosc_fps=10;
                    aktualna_animacja=przeladowanie;
                    int roznica=9-dostepna_amuniacja_pistolet;
                    dostepna_amuniacja_pistolet+=roznica;
                    ilosc_amunicji_pistolet-=roznica;
                }
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&aktualna_bron!=noz)
            {
                if(aktualna_bron==karabin&&dostepna_amuniacja_karabin>0)
                {
                    aktualna_klatka=-1;
                    ilosc_fps=40;
                    aktualna_animacja=strzal;
                    this->strzelanie(obrazenia_broni, pociski);
                    dostepna_amuniacja_karabin--;
                }
                if(aktualna_bron==strzelba&&dostepna_amuniacja_strzelba>0)
                {
                    aktualna_klatka=-1;
                    ilosc_fps=40;
                    aktualna_animacja=strzal;
                    this->strzelanie(obrazenia_broni, pociski);
                    dostepna_amuniacja_strzelba--;
                }
                if(aktualna_bron==pistolet&&dostepna_amuniacja_pistolet>0)
                {
                    aktualna_klatka=-1;
                    ilosc_fps=40;
                    aktualna_animacja=strzal;
                    this->strzelanie(obrazenia_broni, pociski);
                    dostepna_amuniacja_pistolet--;
                }
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
                else animacja(czas, wektor_animacji, ilosc_fps, opoznienie);
            }
        }
        else
        {
            animacja(czas, wektor_animacji, ilosc_fps, opoznienie);
        }
    }

    void ruch(const sf::Time &czas)
    {
        if (WSAD.x!=0&&WSAD.y!=0) {
            WSAD.x = WSAD.x/ sqrt(2);
            WSAD.y = WSAD.y/ sqrt(2);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
            WSAD = WSAD * velocity * 1.5f * czas.asSeconds();
        }
        else{
            WSAD = WSAD * velocity * czas.asSeconds();
        }

        this->move(WSAD);
    }

    void czy_WSAD(){

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            czy_ruch=true;
            WSAD.y-=1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                czy_sprint=true;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            czy_ruch=true;
            WSAD.y+=1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                czy_sprint=true;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            czy_ruch=true;
            WSAD.x-=1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                czy_sprint=true;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            czy_ruch=true;
            WSAD.x+=1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                czy_sprint=true;
            }
        }
    }

    void usuwanie_danych(){
        setOrigin(getLocalBounds().width / 3, getLocalBounds().height / 2);
        czy_ruch=false;
        czy_sprint=false;
        WSAD=sf::Vector2f(0,0);
    }

    void kolizja_gracza(GraphicalObject &obiekt, sf::Clock &zegar)
    {
        sf::FloatRect graczBounds = this->getGlobalBounds();
        graczBounds.left+=10;
        graczBounds.width+=-20;
        graczBounds.top+=10;
        graczBounds.height+=-20;
        sf::FloatRect obiektBounds = obiekt.getGlobalBounds();


        if (graczBounds.left<obiektBounds.left+obiektBounds.width-20&&
            graczBounds.left+graczBounds.width>obiektBounds.left&&
            graczBounds.top<obiektBounds.top+obiektBounds.height-20&&
            graczBounds.top+graczBounds.height>obiektBounds.top+20)
        {
            WSAD.x+=-1;
        }

        if (graczBounds.left<obiektBounds.left+obiektBounds.width&&
            graczBounds.left+graczBounds.width>obiektBounds.left+20&&
            graczBounds.top<obiektBounds.top+obiektBounds.height-20&&
            graczBounds.top+graczBounds.height>obiektBounds.top+20)
        {
            WSAD.x+=1;
        }

        if (graczBounds.left < obiektBounds.left + obiektBounds.width - 20 &&
            graczBounds.left + graczBounds.width > obiektBounds.left + 20 &&
            graczBounds.top < obiektBounds.top + obiektBounds.height &&
            graczBounds.top + graczBounds.height > obiektBounds.top + 20)
        {
            WSAD.y+=1;
        }

        if (graczBounds.left<obiektBounds.left+obiektBounds.width-20&&
            graczBounds.left+graczBounds.width>obiektBounds.left+20&&
            graczBounds.top<obiektBounds.top+obiektBounds.height-20&&
            graczBounds.top+graczBounds.height>obiektBounds.top)
        {
            WSAD.y+=-1;
        }

        if(graczBounds.left<-50)
        {
            WSAD.x+=1;
        }

        if(graczBounds.left+graczBounds.width>1520)
        {
            WSAD.x-=1;
        }

        if(graczBounds.top+graczBounds.height>1320)
        {
            WSAD.y-=1;
        }

        ruch(zegar.getElapsedTime());
    }

    void rozgladanie(const sf::Vector2f &cel, sf::Clock &zegar)override
    {
        pozycja = this->getPosition();
        kierunek_patrzenia = sf::Vector2f(cel.x - pozycja.x, cel.y - pozycja.y);
        float dlugosc = std::sqrt(kierunek_patrzenia.x * kierunek_patrzenia.x + kierunek_patrzenia.y * kierunek_patrzenia.y);

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
    }

    int get_hp()
    {
        return hp;
    }

    void set_hp(int zycie)
    {
        hp=zycie;
    }

    Wybrana_Bron get_bron()
    {
        return aktualna_bron;
    }

    void set_aktualna_bron()
    {
        aktualna_bron=pistolet;
    }

    bool k_animacji()
    {
        if(koniec_animacji==true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

#endif // GRACZ_H
