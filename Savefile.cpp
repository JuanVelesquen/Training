#include "Savefile.h"

///Constructor/Destructor

Savefile::Savefile(){
    this->dinero = 100;
    this->puntos = 0;
    for(int i = 0; i < 5; i++){
        this->mejoras[i] = 0;
    }
    this->nivelesJugador = 0;
    this->tiempoJugado = sf::Time::Zero;
}

Savefile::~Savefile(){
}

///sets
void Savefile::setNombre(const char* nombre){
    strcpy(this->nombre,nombre);
}

void Savefile::setDinero(float dinero){
    this->dinero = dinero;
}

void Savefile::setPuntos(int puntos){
    this->puntos = puntos;
}



void Savefile::setTiempoJugado(sf::Time tiempo){
    this->tiempoJugado = tiempo;
}

void Savefile::setMejoras(int mejora,int indice){
    if(mejora >= 0 && mejora <= 2){
        mejoras[indice] = mejora;
    }else{
        mejoras[indice] = 0;
    }
}

void Savefile::setNivelesJugador(int nivel){
    if(nivel >= 0 && nivel <= 3){
        this->nivelesJugador = nivel;
    }else{
        this->nivelesJugador = 0;
    }
}




///Gets
const char* Savefile::getNombre(){
    return nombre;
}
float Savefile::getDinero(){
    return this->dinero;
}

int Savefile::getPuntos(){
    return this->puntos;
}

sf::Time Savefile::getTiempoJugado(){
    return this->tiempoJugado;
}

int Savefile::getMejoras(int indice){
    return this->mejoras[indice];
}

int Savefile::getNivelesJugador(){
    return this->nivelesJugador;
}




///Metodos


///mostrar variables

void Savefile::mostrar(){
    std::cout<<"Nombre : "<<nombre<<"\n";
    std::cout<<"Dinero : "<<dinero<<"\n";
    std::cout<<"Puntos : "<<puntos<<"\n";
    std::cout<<"Mejora 1 : "<<mejoras[0]<<"\n";
    std::cout<<"Mejora 2 : "<<mejoras[1]<<"\n";
    std::cout<<"Mejora 3 : "<<mejoras[2]<<"\n";
    std::cout<<"Mejora 4 : "<<mejoras[3]<<"\n";
    std::cout<<"Mejora 5 : "<<mejoras[4]<<"\n";
    std::cout<<"Niveles que jugo el jugador : "<<nivelesJugador<<"\n";
    std::cout<<"Tiempo jugado : "<<tiempoJugado.asSeconds()<<"\n";
}
