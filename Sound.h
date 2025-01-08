#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Configuracion.h"
#include "ArchivoConfiguracion.h"

class Sound{
private:
    sf::Sound sound;
    sf::SoundBuffer buffer;
    int type;//1 = MUSIC 2=SFX
public:
    Sound();
    ~Sound();

    ///METHODS

    void setSound(const char* audioFileName,int type);

    void checkStatus();
    void playAudio();
    void endAudio();
    void pauseAudio();

    void updateVolume();
    void update();
};

#endif // SOUND_H_INCLUDED
