/* */
#include "sonido.h"

///Constructor
  Sonido::Sonido(const char *n)
    {
        strcpy(nombre,n);

        buffer.loadFromFile(nombre);
        sound.setBuffer(buffer);

    }
///Setters

    void Sonido::setNombre(const char* n)
    {
        strcpy(nombre,n);
    }
///Getters

    const char* Sonido::getNombre()
    {
        return nombre;
    }
