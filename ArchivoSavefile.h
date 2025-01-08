#ifndef ARCHIVOSAVEFILE_H_INCLUDED
#define ARCHIVOSAVEFILE_H_INCLUDED

#include "Savefile.h"

class ArchivoSavefile{
private:
    char nombre[30];
public:
    ArchivoSavefile(const char *n){
        strcpy(nombre, n);
    }
    ///Metodos

    ///AGREGAR
    void agregarRegistro(Savefile obj);
    ///LEER
    Savefile leerRegistro(int p);
    ///CONTAR REGISTROS
    int contarRegistros();
    ///LISTADO/S
    void modificarRegistro(Savefile obj, int p);
    void mostrarRegistros();
};

#endif // ARCHIVOSAVEFILE_H_INCLUDED
