#ifndef CONFIGURACION_H_INCLUDED
#define CONFIGURACION_H_INCLUDED

#include <iostream>
#include <cstring>

 #include <SFML/Graphics.hpp>
 #include <SFML/Window.hpp>
 #include <SFML/System.hpp>
 #include <SFML/Audio.hpp>
class Configuracion{
private:
    float score[3];
    int configMusica;
    int configSFX;
public:
    Configuracion();

    void setScore(float points,int index);
    void setConfigMusica(int volumen);
    void setConfigSFX(int volumen);

    int getConfigMusica();
    int getConfigSFX();
    float getScore(int index);

    ///Metodos
    void mostrar();

};

#endif // CONFIGURACION_H_INCLUDED
