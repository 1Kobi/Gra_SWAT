TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
INCLUDEPATH += "C:\Users\kobyl\OneDrive\Pulpit\Studia\2Programowanie\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\include"
LIBS += -L"C:\Users\kobyl\OneDrive\Pulpit\Studia\2Programowanie\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    Background.h \
    Gra.h \
    Gracz.h \
    Interfejs.h \
    Menu.h \
    Pociski.h \
    Postac.h \
    Wall.h \
    Wrog.h \
    enumy.h \
    graphicalobject.h \
    randomnumbergenerator.h
