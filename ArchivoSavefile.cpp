#include "ArchivoSavefile.h"

void ArchivoSavefile::agregarRegistro(Savefile obj){
    FILE *reg;
    reg=fopen(nombre, "ab");
    if(reg==NULL){
        reg=fopen(nombre, "wb");
    }
	fwrite(&obj, sizeof (Savefile), 1, reg);
	fclose(reg);
}

Savefile ArchivoSavefile::leerRegistro(int p){
    Savefile obj;
    FILE *reg;
    reg=fopen(nombre, "rb");
    if(reg==NULL){
        std::cout<<"No se pudo leer el archivo savefile"<<"\n";
        return obj;
    }
    fseek(reg, sizeof obj * p, 0); ///0: desde el principio, 1: desde la posicion actual, 2: desde el eof
    int aux=fread(&obj, sizeof obj, 1, reg);
    fclose(reg);
    if(aux==0){
        std::cout<<"No se pudo leer el objeto savefile"<<"\n";
        std::cout<<"Posicion: "<<p<<"\n";
    }
    return obj;
}

int ArchivoSavefile::contarRegistros(){
    FILE *p;
    p=fopen(nombre, "rb");
    if(p==NULL) return -1;
    fseek(p, 0,2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof(Savefile);
}

void ArchivoSavefile::modificarRegistro(Savefile obj, int pos){
    FILE *reg;
    reg = fopen(nombre, "rb+");
    fseek(reg, sizeof obj * pos, 0);
    bool aux = fwrite(&obj, sizeof obj, 1, reg);
        if(aux==0){
        std::cout<<"No se pudo escribir el objeto en el archivo savefile"<<"\n";
        std::cout<<"Posicion: "<<pos<<"\n";
    }
    fclose(reg);
}

void ArchivoSavefile::mostrarRegistros(){
    Savefile obj;
    FILE *reg;
    reg=fopen(nombre, "rb");
    if(reg==NULL){
        std::cout<<"NO SE PUDO CREAR EL ARCHIVO"<<std::endl;
        return;
    }

	while(fread(&obj, sizeof obj, 1, reg)==1){
            obj.mostrar();
	}
	fclose(reg);
}
