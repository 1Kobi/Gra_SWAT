# SWAT 2D - Tactical Top-Down Shooter (C++/SFML)

Zaawansowany projekt gry 2D typu top-down shooter, zrealizowany w **C++** przy użyciu biblioteki **SFML**. Projekt demonstruje solidne podstawy programowania obiektowego (OOP), implementację systemów animacji klatkowej oraz autorską logikę AI.
<img width="1672" height="1053" alt="gra_ss" src="https://github.com/user-attachments/assets/4f3e5e4c-d182-4aba-9d22-8565412cf63b" />

## 🚀 Kluczowe Cechy Techniczne

### 1. Zaawansowana Architektura Obiektowa
Projekt opiera się na hierarchii klas z wykorzystaniem polimorfizmu:
* **Klasa bazowa `Postac`**: Abstrakcyjna klasa zarządzająca wspólnymi cechami (HP, animacje, system broni, poruszanie się).
* **Klasy `Gracz` oraz `Wrog`**: Implementują specyficzne zachowania poprzez nadpisywanie metod wirtualnych (`wybor_akcji`, `rozgladanie`).

### 2. System Animacji oparty na Mapach Stanów
Zastosowałem wydajny system zarządzania klatkami animacji (`sf::IntRect`) przy użyciu kontenera `std::map` z kluczem złożonym (`std::pair<Wybrana_Bron, Animacja>`). Pozwala to na:
* Błyskawiczną zmianę zestawu animacji przy zmianie broni (Karabin/Strzelba/Pistolet/Nóż).
* Obsługę różnych stanów: chód, sprint, strzał, przeładowanie, atak wręcz.

### 3. Logika AI i Line of Sight (LoS)
Przeciwnicy korzystają z autorskiego algorytmu wykrywania gracza:
* **Detekcja linii wzroku**: Wykorzystanie geometrii analitycznej do sprawdzania, czy linia między wrogiem a graczem nie przecina się z obiektami typu `Wall` (algorytm orientacji trzech punktów na płaszczyźnie).
* **Fazy zachowania**: Wróg przechodzi ze stanu patrolowania do celowania i ostrzału po wykryciu gracza lub zostaniu trafionym.

### 4. Realistyczna Mechanika Strzelecka
* **System rozrzutu (Recoil/Spread)**: Celność broni dynamicznie zmienia się w zależności od poruszania się postaci (chód vs sprint).
* **Balistyka**: Każda broń posiada unikalne parametry: prędkość pocisku, obrażenia, szybkostrzelność oraz czas przeładowania.

### 5. Proceduralna Losowość
* **Pozycje przeciwników, ich liczba oraz używana przez nich broń są losowane przy każdym uruchomieniu, co zapewnia unikalność każdej rozgrywki.**

### 6. Poziomy trudności
* **Skalowanie poziomu trudności wpływa na szybkość reakcji przeciwników oraz końcową punktację.**
<img width="1867" height="1047" alt="menu" src="https://github.com/user-attachments/assets/ced8f7ce-251c-4a1d-9ef8-cb86c4028059" />

## 🎮 Rozgrywka i Sterowanie

Celem gry jest eliminacja wszystkich przeciwników na mapie przy zachowaniu jak największej ilości punktów życia w jak najkrótszym czasie.

| Klawisz | Akcja |
| :--- | :--- |
| **W, S, A, D** | Poruszanie się (wpływa na celność) |
| **L-Shift** | Sprint (szybszy ruch, większy rozrzut) |
| **Myszka** | Celowanie (płynna rotacja postaci) |
| **LPM** | Strzał |
| **1, 2, 3** | Zmiana broni (Główna / Pistolet / Nóż) |
| **R** | Przeładowanie |
| **F** | Atak wręcz |
<img width="651" height="787" alt="podsumowanie" src="https://github.com/user-attachments/assets/f661205f-070f-43c1-90ae-f769498d3e9f" />

## 🛠️ Technologie i Kompilacja

* **Język:** C++17
* **Biblioteka:** SFML 2.6.1
* **Kompilator:** MinGW 64-bit
* **Zarządzanie projektem:** Qt Creator (qmake)

### Uruchomienie wersji binarnej:
Gotowa, skompilowana wersja gry (Release) znajduje się w zakładce [Releases](link_do_twojego_release). Pobierz ZIP, rozpakuj i uruchom `SWAT.exe`.
