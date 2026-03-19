#ifndef POSTAC_H
#define POSTAC_H
#include "Pociski.h"
#include "SFML/System/Clock.hpp"
#include "graphicalobject.h"
#include "randomnumbergenerator.h"
#include "enumy.h"
#include <map>
#include <memory>


class Postac : public GraphicalObject {
private:
    sf::Texture texture;
protected:
    enum Animacja
    {
        brak=0,
        chod=1,
        strzal=2,
        przeladowanie=3,
        atak=4,
    };

    std::map<std::pair<Wybrana_Bron, Animacja>, std::vector<sf::IntRect>*> wszystkie_animacje;

    sf::Vector2f pozycja;
    sf::Vector2f kierunek_patrzenia;
    int hp=100;
    float velocity;
    float direction;
    float rotationSpeed;

    int aktualna_klatka=-1;
    float ilosc_fps;
    float czas_animacja=0;

    int dostepna_amuniacja_karabin=30;
    int ilosc_amunicji_karabin=90;
    int dostepna_amuniacja_strzelba=6;
    int ilosc_amunicji_strzelba=18;
    int dostepna_amuniacja_pistolet=9;
    int ilosc_amunicji_pistolet=27;
    int obrazenia_broni;
    float predkosc_pocisku;
    float opoznienie=0.f;

    bool czy_ruch = false;
    bool czy_sprint = false;
    bool koniec_animacji=true;

    RandomNumberGenerator rng;

    Animacja aktualna_animacja=chod;
    Wybrana_Bron aktualna_bron=pistolet;
    Wybrana_Bron wybrana_bron;

    std::vector<sf::IntRect> chod_glowna;
    std::vector<sf::IntRect> chod_pistolet;
    std::vector<sf::IntRect> chod_noz;

    std::vector<sf::IntRect> strzal_glowna;
    std::vector<sf::IntRect> strzal_pistolet;

    std::vector<sf::IntRect> atak_glowna;
    std::vector<sf::IntRect> atak_pistolet;
    std::vector<sf::IntRect> atak_noz;

    std::vector<sf::IntRect> przeladowanie_glowna;
    std::vector<sf::IntRect> przeladowanie_pistolet;

    std::vector<sf::IntRect>* wektor_animacji;
    std::vector<sf::IntRect>* wektor_chodu;


public:
    Postac(sf::Vector2f &pos, std::string textura, Wybrana_Bron bron)
        : GraphicalObject(&texture, pos), direction(0)
    {
        if (!texture.loadFromFile(textura)) {
            throw("Wrong texture filename");
        }

        wybrana_bron=bron;
        if(wybrana_bron==strzelba)
        {
            wczytaj_strzelbe();
        }
        else
        {
            wczytaj_karabin();
        }
        ilosc_amunicji_pistolet=36;
        dostepna_amuniacja_pistolet=9;
        wczytaj_pistolet();
        wczytaj_noz();
        inicjalizuj_animacje();

        setScale(sf::Vector2f(0.4f, 0.4f));
    }

    std::vector<sf::IntRect>* pobierz_animacje(const Wybrana_Bron &bron, const Animacja &anim)
    {
        auto it = wszystkie_animacje.find({bron, anim});
        if (it != wszystkie_animacje.end())
        {
            return it->second;
        }
        else
        {
            return nullptr;
        }
    }

    void inicjalizuj_animacje()
    {
        if(wybrana_bron==strzelba)
        {
            wszystkie_animacje[{strzelba, chod}] = &chod_glowna;
            wszystkie_animacje[{strzelba, strzal}] = &strzal_glowna;
            wszystkie_animacje[{strzelba, przeladowanie}] = &przeladowanie_glowna;
            wszystkie_animacje[{strzelba, atak}] = &atak_glowna;
        }
        else
        {
            wszystkie_animacje[{karabin, chod}] = &chod_glowna;
            wszystkie_animacje[{karabin, strzal}] = &strzal_glowna;
            wszystkie_animacje[{karabin, przeladowanie}] = &przeladowanie_glowna;
            wszystkie_animacje[{karabin, atak}] = &atak_glowna;
        }

        wszystkie_animacje[{pistolet, chod}] = &chod_pistolet;
        wszystkie_animacje[{pistolet, strzal}] = &strzal_pistolet;
        wszystkie_animacje[{pistolet, przeladowanie}] = &przeladowanie_pistolet;
        wszystkie_animacje[{pistolet, atak}] = &atak_pistolet;

        wszystkie_animacje[{noz, chod}] = &chod_noz;
        wszystkie_animacje[{noz, atak}] = &atak_noz;
    }

    void wczytaj_strzelbe()
    {
        chod_glowna.emplace_back(sf::IntRect(35, 465, 267, 148));// 1 klatka
        chod_glowna.emplace_back(sf::IntRect(346, 465, 267, 148));// 2 klatka
        chod_glowna.emplace_back(sf::IntRect(658, 465, 267, 148));// 3 klatka
        chod_glowna.emplace_back(sf::IntRect(970, 465, 267, 148));// 4 klatka
        chod_glowna.emplace_back(sf::IntRect(1282, 465, 267, 148));// 5 klatka
        chod_glowna.emplace_back(sf::IntRect(1595, 465, 267, 148));// 6 klatka
        chod_glowna.emplace_back(sf::IntRect(1907, 464, 267, 148));// 7 klatka
        chod_glowna.emplace_back(sf::IntRect(2220, 464, 267, 148));// 8 klatka
        chod_glowna.emplace_back(sf::IntRect(2533, 464, 267, 148));// 9 klatka
        chod_glowna.emplace_back(sf::IntRect(2846, 464, 267, 148));// 10 klatka
        chod_glowna.emplace_back(sf::IntRect(3159, 464, 267, 148));// 11 klatka
        chod_glowna.emplace_back(sf::IntRect(3472, 464, 267, 148));// 12 klatka
        chod_glowna.emplace_back(sf::IntRect(3785, 464, 267, 148));// 13 klatka
        chod_glowna.emplace_back(sf::IntRect(4098, 464, 267, 148));// 14 klatka
        chod_glowna.emplace_back(sf::IntRect(4411, 464, 267, 148));// 15 klatka
        chod_glowna.emplace_back(sf::IntRect(4725, 464, 267, 148));// 16 klatka
        chod_glowna.emplace_back(sf::IntRect(5038, 464, 267, 148));// 17 klatka
        chod_glowna.emplace_back(sf::IntRect(5352, 464, 267, 148));// 18 klatka
        chod_glowna.emplace_back(sf::IntRect(5665, 464, 267, 148));// 19 klatka
        chod_glowna.emplace_back(sf::IntRect(5979, 464, 267, 148));// 20 klatka

        atak_glowna.emplace_back(sf::IntRect(40, 1502, 300, 300));// 1 klatka
        atak_glowna.emplace_back(sf::IntRect(396, 1502, 300, 300));// 2 klatka
        atak_glowna.emplace_back(sf::IntRect(752, 1502, 300, 300));// 3 klatka
        atak_glowna.emplace_back(sf::IntRect(1108, 1502, 300, 300));// 4 klatka
        atak_glowna.emplace_back(sf::IntRect(1464, 1502, 300, 300));// 5 klatka
        atak_glowna.emplace_back(sf::IntRect(1820, 1502, 300, 300));// 6 klatka
        atak_glowna.emplace_back(sf::IntRect(2182, 1502, 300, 300));// 7 klatka
        atak_glowna.emplace_back(sf::IntRect(2540, 1502, 300, 300));// 8 klatka
        atak_glowna.emplace_back(sf::IntRect(2898, 1502, 300, 300));// 9 klatka
        atak_glowna.emplace_back(sf::IntRect(3256, 1502, 300, 300));// 10 klatka
        atak_glowna.emplace_back(sf::IntRect(3614, 1502, 300, 300));// 11 klatka
        atak_glowna.emplace_back(sf::IntRect(3974, 1502, 300, 300));// 12 klatka
        atak_glowna.emplace_back(sf::IntRect(4328, 1502, 300, 300));// 13 klatka
        atak_glowna.emplace_back(sf::IntRect(4687, 1502, 300, 300));// 14 klatka
        atak_glowna.emplace_back(sf::IntRect(5048, 1502, 300, 300));// 15 klatka

        przeladowanie_glowna.emplace_back(sf::IntRect(40, 2596, 270, 160));// 1 klatka strzelba
        przeladowanie_glowna.emplace_back(sf::IntRect(362, 2596, 270, 160));// 2 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(684, 2596, 270, 160));// 3 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(1006, 2596, 270, 160));// 4 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(1328, 2596, 270, 160));// 5 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(1650, 2596, 270, 160));// 6 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(1972, 2596, 270, 160));// 7 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(2294, 2596, 270, 160));// 8 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(2616, 2596, 270, 160));// 9 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(2938, 2596, 270, 160));// 10 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(3260, 2596, 270, 160));// 11 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(3582, 2596, 270, 160));// 12 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(3904, 2596, 270, 160));// 13 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(4226, 2596, 270, 160));// 14 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(4550, 2596, 270, 160));// 15 klatka

        strzal_glowna.emplace_back(sf::IntRect(35, 3236, 267, 148));// 1 klatka
        strzal_glowna.emplace_back(sf::IntRect(350, 3236, 267, 148));// 2 klatka
        strzal_glowna.emplace_back(sf::IntRect(658, 3236, 267, 148));// 3 klatka

    }

    void wczytaj_karabin()
    {
        chod_glowna.emplace_back(sf::IntRect(36, 259, 255, 148));// 1 klatka
        chod_glowna.emplace_back(sf::IntRect(350, 259, 255, 148));// 2 klatka
        chod_glowna.emplace_back(sf::IntRect(663, 259, 255, 148));// 3 klatka
        chod_glowna.emplace_back(sf::IntRect(975, 259, 255, 148));// 4 klatka
        chod_glowna.emplace_back(sf::IntRect(1287, 258, 255, 148));// 5 klatka
        chod_glowna.emplace_back(sf::IntRect(1599, 258, 255, 148));// 6 klatka
        chod_glowna.emplace_back(sf::IntRect(1911, 258, 255, 148));// 7 klatka
        chod_glowna.emplace_back(sf::IntRect(2223, 258, 255, 148));// 8 klatka
        chod_glowna.emplace_back(sf::IntRect(2536, 258, 255, 148));// 9 klatka
        chod_glowna.emplace_back(sf::IntRect(2848, 258, 255, 148));// 10 klatka
        chod_glowna.emplace_back(sf::IntRect(3161, 258, 255, 148));// 11 klatka
        chod_glowna.emplace_back(sf::IntRect(3474, 258, 255, 148));// 12 klatka
        chod_glowna.emplace_back(sf::IntRect(3788, 258, 255, 148));// 13 klatka
        chod_glowna.emplace_back(sf::IntRect(4102, 258, 255, 148));// 14 klatka
        chod_glowna.emplace_back(sf::IntRect(4416, 258, 255, 148));// 15 klatka
        chod_glowna.emplace_back(sf::IntRect(4730, 258, 255, 148));// 16 klatka
        chod_glowna.emplace_back(sf::IntRect(5044, 258, 255, 148));// 17 klatka
        chod_glowna.emplace_back(sf::IntRect(5356, 259, 255, 148));// 18 klatka
        chod_glowna.emplace_back(sf::IntRect(5669, 259, 255, 148));// 19 klatka
        chod_glowna.emplace_back(sf::IntRect(5984, 259, 255, 148));// 20 klatka

        atak_glowna.emplace_back(sf::IntRect(43, 1149, 280, 305));// 1 klatka
        atak_glowna.emplace_back(sf::IntRect(397, 1149, 280, 305));// 2 klatka
        atak_glowna.emplace_back(sf::IntRect(754, 1149, 280, 305));// 3 klatka
        atak_glowna.emplace_back(sf::IntRect(1108, 1149, 280, 305));// 4 klatka
        atak_glowna.emplace_back(sf::IntRect(1462, 1149, 280, 305));// 5 klatka
        atak_glowna.emplace_back(sf::IntRect(1816, 1149, 280, 305));// 6 klatka
        atak_glowna.emplace_back(sf::IntRect(2177, 1149, 280, 305));// 7 klatka
        atak_glowna.emplace_back(sf::IntRect(2541, 1149, 280, 305));// 8 klatka
        atak_glowna.emplace_back(sf::IntRect(2905, 1149, 280, 305));// 9 klatka
        atak_glowna.emplace_back(sf::IntRect(3268, 1149, 280, 305));// 10 klatka
        atak_glowna.emplace_back(sf::IntRect(3633, 1149, 280, 305));// 11 klatka
        atak_glowna.emplace_back(sf::IntRect(3988, 1149, 280, 305));// 12 klatka
        atak_glowna.emplace_back(sf::IntRect(4342, 1149, 280, 305));// 13 klatka
        atak_glowna.emplace_back(sf::IntRect(4696, 1149, 280, 305));// 14 klatka
        atak_glowna.emplace_back(sf::IntRect(5055, 1149, 280, 305));// 15 klatka

        przeladowanie_glowna.emplace_back(sf::IntRect(40, 2378, 260, 160));// 1 klatka karabin
        przeladowanie_glowna.emplace_back(sf::IntRect(362, 2378, 260, 160));// 2 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(684, 2378, 260, 160));// 3 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(1006, 2378, 260, 160));// 4 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(1328, 2378, 260, 160));// 5 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(1650, 2378, 260, 160));// 6 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(1972, 2378, 260, 160));// 7 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(2294, 2378, 260, 160));// 8 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(2616, 2378, 260, 160));// 9 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(2938, 2378, 260, 160));// 10 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(3260, 2378, 260, 160));// 11 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(3582, 2378, 260, 160));// 12 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(3904, 2378, 260, 160));// 13 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(4226, 2378, 260, 160));// 14 klatka
        przeladowanie_glowna.emplace_back(sf::IntRect(4550, 2378, 260, 160));// 15 klatka

        strzal_glowna.emplace_back(sf::IntRect(36, 3030, 255, 150));// 1 klatka karabin
        strzal_glowna.emplace_back(sf::IntRect(348, 3030, 255, 150));// 2 klatka
        strzal_glowna.emplace_back(sf::IntRect(660, 3030, 255, 150));// 3 klatka
    }

    void wczytaj_pistolet()
    {
        chod_pistolet.emplace_back(sf::IntRect(40, 40, 206, 152));// 1 klatka
        chod_pistolet.emplace_back(sf::IntRect(298, 40, 206, 152));// 2 klatka
        chod_pistolet.emplace_back(sf::IntRect(556, 40, 206, 152));// 3 klatka
        chod_pistolet.emplace_back(sf::IntRect(813, 41, 206, 152));// 4 klatka
        chod_pistolet.emplace_back(sf::IntRect(1071, 41, 206, 152));// 5 klatka
        chod_pistolet.emplace_back(sf::IntRect(1329, 42, 206, 152));// 6 klatka
        chod_pistolet.emplace_back(sf::IntRect(1586, 42, 206, 152));// 7 klatka
        chod_pistolet.emplace_back(sf::IntRect(1844, 43, 206, 152));// 8 klatka
        chod_pistolet.emplace_back(sf::IntRect(2102, 43, 206, 152));// 9 klatka
        chod_pistolet.emplace_back(sf::IntRect(2359, 44, 206, 152));// 10 klatka
        chod_pistolet.emplace_back(sf::IntRect(2617, 44, 206, 152));// 11 klatka
        chod_pistolet.emplace_back(sf::IntRect(2875, 44, 206, 152));// 12 klatka
        chod_pistolet.emplace_back(sf::IntRect(3134, 44, 206, 152));// 13 klatka
        chod_pistolet.emplace_back(sf::IntRect(3392, 43, 206, 152));// 14 klatka
        chod_pistolet.emplace_back(sf::IntRect(3650, 43, 206, 152));// 15 klatka
        chod_pistolet.emplace_back(sf::IntRect(3909, 42, 206, 152));// 16 klatka
        chod_pistolet.emplace_back(sf::IntRect(4167, 42, 206, 152));// 17 klatka
        chod_pistolet.emplace_back(sf::IntRect(4426, 41, 206, 152));// 18 klatka
        chod_pistolet.emplace_back(sf::IntRect(4684, 41, 206, 152));// 19 klatka
        chod_pistolet.emplace_back(sf::IntRect(4942, 40, 206, 152));// 20 klatka

        atak_pistolet.emplace_back(sf::IntRect(20, 866, 250, 210));// 1 klatka
        atak_pistolet.emplace_back(sf::IntRect(310, 866, 250, 210));// 2 klatka
        atak_pistolet.emplace_back(sf::IntRect(600, 866, 250, 210));// 3 klatka
        atak_pistolet.emplace_back(sf::IntRect(890, 866, 250, 210));// 4 klatka
        atak_pistolet.emplace_back(sf::IntRect(1180, 866, 250, 210));// 5 klatka
        atak_pistolet.emplace_back(sf::IntRect(1470, 866, 250, 210));// 6 klatka
        atak_pistolet.emplace_back(sf::IntRect(1760, 866, 250, 210));// 7 klatka
        atak_pistolet.emplace_back(sf::IntRect(2050, 866, 250, 210));// 8 klatka
        atak_pistolet.emplace_back(sf::IntRect(2340, 866, 250, 210));// 9 klatka
        atak_pistolet.emplace_back(sf::IntRect(2640, 866, 250, 210));// 10 klatka
        atak_pistolet.emplace_back(sf::IntRect(2940, 866, 250, 210));// 11 klatka
        atak_pistolet.emplace_back(sf::IntRect(3230, 866, 250, 210));// 12 klatka
        atak_pistolet.emplace_back(sf::IntRect(3520, 866, 250, 210));// 13 klatka
        atak_pistolet.emplace_back(sf::IntRect(3815, 866, 250, 210));// 14 klatka
        atak_pistolet.emplace_back(sf::IntRect(4100, 866, 250, 210));// 15 klatka

        przeladowanie_pistolet.emplace_back(sf::IntRect(39, 2139, 206, 180));// 1 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(299, 2139, 206, 180));// 2 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(559, 2139, 206, 180));// 3 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(819, 2139, 206, 180));// 4 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(1079, 2139, 206, 180));// 5 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(1339, 2139, 206, 180));// 6 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(1599, 2139, 206, 180));// 7 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(1859, 2139, 206, 180));// 8 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(2119, 2139, 206, 180));// 9 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(2379, 2139, 206, 180));// 10 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(2639, 2139, 206, 180));// 11 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(2899, 2139, 206, 180));// 12 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(3159, 2139, 206, 180));// 13 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(3419, 2139, 206, 180));// 14 klatka
        przeladowanie_pistolet.emplace_back(sf::IntRect(3679, 2139, 206, 180));// 15 klatka

        strzal_pistolet.emplace_back(sf::IntRect(37, 2808, 206, 170));// 1 klatka
        strzal_pistolet.emplace_back(sf::IntRect(292, 2808, 206, 170));// 2 klatka
        strzal_pistolet.emplace_back(sf::IntRect(547, 2808, 206, 170));// 3 klatka
    }

    void wczytaj_noz()
    {
        chod_noz.emplace_back(sf::IntRect(40, 653, 230, 170));// 1 klatka
        chod_noz.emplace_back(sf::IntRect(319, 653, 230, 170));// 2 klatka
        chod_noz.emplace_back(sf::IntRect(598, 653, 230, 170));// 3 klatka
        chod_noz.emplace_back(sf::IntRect(877, 653, 230, 170));// 4 klatka
        chod_noz.emplace_back(sf::IntRect(1156, 653, 230, 170));// 5 klatka
        chod_noz.emplace_back(sf::IntRect(1434, 653, 230, 170));// 6 klatka
        chod_noz.emplace_back(sf::IntRect(1712, 653, 230, 170));// 7 klatka
        chod_noz.emplace_back(sf::IntRect(1990, 653, 230, 170));// 8 klatka
        chod_noz.emplace_back(sf::IntRect(2268, 653, 230, 170));// 9 klatka
        chod_noz.emplace_back(sf::IntRect(2546, 653, 230, 170));// 10 klatka
        chod_noz.emplace_back(sf::IntRect(2824, 653, 230, 170));// 11 klatka
        chod_noz.emplace_back(sf::IntRect(3100, 653, 230, 170));// 12 klatka
        chod_noz.emplace_back(sf::IntRect(3380, 653, 230, 170));// 13 klatka
        chod_noz.emplace_back(sf::IntRect(3660, 653, 230, 170));// 14 klatka
        chod_noz.emplace_back(sf::IntRect(3940, 653, 230, 170));// 15 klatka
        chod_noz.emplace_back(sf::IntRect(4220, 653, 230, 170));// 16 klatka
        chod_noz.emplace_back(sf::IntRect(4500, 653, 230, 170));// 17 klatka
        chod_noz.emplace_back(sf::IntRect(4780, 653, 230, 170));// 18 klatka
        chod_noz.emplace_back(sf::IntRect(5060, 653, 230, 170));// 19 klatka
        chod_noz.emplace_back(sf::IntRect(5337, 653, 230, 170));// 20 klatka

        atak_noz.emplace_back(sf::IntRect(15, 1782, 290, 290));// 1 klatka
        atak_noz.emplace_back(sf::IntRect(344, 1784, 290, 290));// 2 klatka
        atak_noz.emplace_back(sf::IntRect(673, 1786, 290, 290));// 3 klatka
        atak_noz.emplace_back(sf::IntRect(1002, 1788, 290, 290));// 4 klatka
        atak_noz.emplace_back(sf::IntRect(1331, 1790, 290, 290));// 5 klatka
        atak_noz.emplace_back(sf::IntRect(1660, 1792, 290, 290));// 6 klatka
        atak_noz.emplace_back(sf::IntRect(1989, 1794, 290, 290));// 7 klatka
        atak_noz.emplace_back(sf::IntRect(2318, 1795, 290, 290));// 8 klatka
        atak_noz.emplace_back(sf::IntRect(2647, 1792, 290, 290));// 9 klatka
        atak_noz.emplace_back(sf::IntRect(2976, 1789, 290, 290));// 10 klatka
        atak_noz.emplace_back(sf::IntRect(3305, 1786, 290, 290));// 11 klatka
        atak_noz.emplace_back(sf::IntRect(3634, 1783, 290, 290));// 12 klatka
    }

    virtual void rozgladanie(const sf::Vector2f &cel, sf::Clock &zegar)=0;

    void animacja_chod(const sf::Time &czas, std::vector<sf::IntRect> *animacja)
    {
        if(czy_ruch){
            czas_animacja+=czas.asSeconds();
            if(czy_sprint)
            {
                if (czas_animacja > 1.0f / 45) {
                    aktualna_klatka = (aktualna_klatka + 1) % animacja->size();
                    czas_animacja=0.f;
                    setTextureRect(sf::IntRect((*animacja)[aktualna_klatka]));
                }
            }
            else
            {
                if (czas_animacja > 1.0f / 30) {
                    aktualna_klatka = (aktualna_klatka + 1) %  animacja->size();
                    czas_animacja=0.f;
                    setTextureRect(sf::IntRect((*animacja)[aktualna_klatka]));
                }
            }
        }
        else
        {
            aktualna_klatka=0;
            setTextureRect(sf::IntRect((*animacja)[aktualna_klatka]));
            this->setOrigin(this->getLocalBounds().width/3,this->getLocalBounds().height/2);
        }
    };

    void animacja(const sf::Time &czas, std::vector<sf::IntRect> *animacja, int ilosc_fps, float opoznienie)
    {
        this->koniec_animacji=false;
        czas_animacja+=czas.asSeconds();
        if (czas_animacja > 1.0f / ilosc_fps) {
            if(aktualna_klatka+1== animacja->size())
            {
                if(czas_animacja > opoznienie)
                {
                    this->koniec_animacji=true;
                    this->aktualna_animacja=chod;
                }
            }
            else
            {
                aktualna_klatka = (aktualna_klatka + 1) %  animacja->size();
                czas_animacja=0.f;
                setTextureRect(sf::IntRect((*animacja)[aktualna_klatka]));
                this->setOrigin(this->getLocalBounds().width/3,this->getLocalBounds().height/2);
            }
        }
    }

    virtual void wybor_akcji(const sf::Time &czas, std::vector<std::unique_ptr<Pociski>> &pociski)=0;

    void strzelanie(int &obrazenia, std::vector<std::unique_ptr<Pociski>> &pociski)
    {
        sf::Vector2f odchylenie;

        if(czy_ruch){
            if(czy_sprint)
            {
                if(aktualna_bron==pistolet)
                {
                    odchylenie=sf::Vector2f(rng.getRandomInt(-12, 12),rng.getRandomInt(-12, 12));
                }
                if((aktualna_bron==strzelba)||(aktualna_bron==karabin))
                {
                    odchylenie=sf::Vector2f(rng.getRandomInt(-20, 20),rng.getRandomInt(-20, 20));
                }
            }
            else
            {
                if(aktualna_bron==pistolet)
                {
                    odchylenie=sf::Vector2f(rng.getRandomInt(-8, 8),rng.getRandomInt(-8, 8));
                }
                if((aktualna_bron==strzelba)||(aktualna_bron==karabin))
                {
                    odchylenie=sf::Vector2f(rng.getRandomInt(-12, 12),rng.getRandomInt(-12, 12));
                }
            }
        }
        else
        {
            if(aktualna_bron==pistolet)
            {
                odchylenie=sf::Vector2f(rng.getRandomInt(-5, 5),rng.getRandomInt(-5, 5));
            }
            if((aktualna_bron==strzelba)||(aktualna_bron==karabin))
            {
                odchylenie=sf::Vector2f(rng.getRandomInt(-8, 8),rng.getRandomInt(-8, 8));
            }
        }

        odchylenie/=100.f;
        kierunek_patrzenia+=odchylenie;

        if(aktualna_bron==strzelba)
        {
            kierunek_patrzenia-=sf::Vector2f(0.1f,0.1f);
            for(int i=0;i<5;i++)
            {
                pociski.emplace_back(std::make_unique<Pociski>(pozycja, predkosc_pocisku, kierunek_patrzenia, obrazenia));
                kierunek_patrzenia+=sf::Vector2f(0.05f,0.05f);
            }
        }
        else
        {
            pociski.emplace_back(std::make_unique<Pociski>(pozycja, predkosc_pocisku, kierunek_patrzenia, obrazenia));
        }
    }

    void zabierz_zycie(int ilosc_dmg)
    {
        hp-=ilosc_dmg;
    }
};

#endif // POSTAC_H
