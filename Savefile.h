#ifndef SAVEFILE_H_INCLUDED
#define SAVEFILE_H_INCLUDED

#include <iostream>
#include <cstring>

 #include <SFML/Graphics.hpp>
 #include <SFML/Window.hpp>
 #include <SFML/System.hpp>
 #include <SFML/Audio.hpp>

class Savefile{
private:
    char nombre[8];
    float dinero;
    int puntos;
    sf::Time tiempoJugado;
    int mejoras[5];
    int nivelesJugador;
public:
    ///Constructor / Destructor
    Savefile();
    ~Savefile();
    ///Sets
    void setNombre(const char *nombre);
    void setDinero(float dinero);
    void setPuntos(int puntos);
    void setTiempoJugado(sf::Time tiempo);
    void setMejoras(int mejora,int indice);
    void setNivelesJugador(int nivel);

    ///Gets
    const char *getNombre();
    float getDinero();
    int getPuntos();
    sf::Time getTiempoJugado();
    int getMejoras(int indice);
    int getNivelesJugador();
    ///Metodos
    void mostrar();
};

#endif // SAVEFILE_H_INCLUDED
