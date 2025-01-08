#ifndef SONIDO_H
#define SONIDO_H
#include "cstring"
 #include <SFML/Graphics.hpp>
 #include <SFML/Window.hpp>
 #include <SFML/System.hpp>
 #include <SFML/Audio.hpp>



class Sonido: public sf::Sound
{
    protected:
    char nombre[30];
    sf::SoundBuffer buffer;
    sf::Sound sound;
    public:
        ///Constructor
        Sonido(const char *n);
        ///Setters

        void setNombre(const char* n);
        ///Getters

        const char* getNombre();

        ///Methods
};

#endif // SONIDO_H
