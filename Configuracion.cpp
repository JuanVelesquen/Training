#include "Configuracion.h"

Configuracion::Configuracion(){
    this->configMusica = 50;
    this->configSFX= 50;
    this->score[0] = 0;
    this->score[1] = 0;
    this->score[2] = 0;
}

void Configuracion::setConfigMusica(int volumen){
    if(volumen >= 0 && volumen <= 100){
        this->configMusica = volumen;
    }
}

void Configuracion::setConfigSFX(int volumen){
    if(volumen >= 0 && volumen <= 100){
        this->configSFX = volumen;
    }
}

void Configuracion::setScore(float points,int index){
    this->score[index] = points;
}

int Configuracion::getConfigMusica(){
 return this->configMusica;
}

int Configuracion::getConfigSFX(){
    return this->configSFX;
}

float Configuracion::getScore(int index){
 return this->score[index];
}

void Configuracion::mostrar(){
    std::cout<<"Volumen Musica : "<<configMusica<<"\n";
    std::cout<<"Volumen SFX : "<<configSFX<<"\n";
    std::cout<<"Score 1 : "<<score[0]<<"\n";
    std::cout<<"Score 2 : "<<score[1]<<"\n";
    std::cout<<"Score 3 : "<<score[2]<<"\n";

}
