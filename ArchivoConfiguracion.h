#ifndef ARCHIVOCONFIGURACION_H_INCLUDED
#define ARCHIVOCONFIGURACION_H_INCLUDED

#include "Configuracion.h"

class ArchivoConfiguracion{
private:
    char nombre[30];
public:
    ArchivoConfiguracion(const char *n){
        strcpy(nombre, n);
    }
    ///Metodos

    ///AGREGAR
    void agregarRegistro(Configuracion obj);
    ///LEER
    Configuracion leerRegistro(int p);
    ///CONTAR REGISTROS
    int contarRegistros();
    ///LISTADO/S
    void modificarRegistro(Configuracion obj, int p);
    void mostrarRegistros();
};


#endif // ARCHIVOCONFIGURACION_H_INCLUDED
