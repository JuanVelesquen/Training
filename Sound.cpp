#include "Sound.h"
Sound::Sound(){

}
Sound::~Sound(){}

///METHODS
void Sound::setSound(const char* audioFileName,int type){
    buffer.loadFromFile(audioFileName);
    sound.setBuffer(buffer);

    Configuracion objConfig;
    ArchivoConfiguracion arkConfig("configuracion.dat");
    objConfig = arkConfig.leerRegistro(0);

    this->type = type;
    switch(type){
        case 1:
            sound.setVolume(objConfig.getConfigMusica());
            break;
        case 2:
            sound.setVolume(objConfig.getConfigSFX());
            break;
        default:
            sound.setVolume(objConfig.getConfigMusica());
            break;
    }
}

void Sound::checkStatus(){
    if(sound.getStatus() == sound.Stopped && type == 1){
        playAudio();
    }
}
void Sound::playAudio(){
    if(sound.getStatus() != sound.Playing)
        sound.play();
}
void Sound::endAudio(){
    sound.stop();
}
void Sound::pauseAudio(){
    sound.pause();
}

void Sound::updateVolume(){
    Configuracion objConfig;
    ArchivoConfiguracion arkConfig("configuracion.dat");
    objConfig = arkConfig.leerRegistro(0);
    switch(type){
    case 1:
        sound.setVolume(objConfig.getConfigMusica());
        break;
    case 2:
        sound.setVolume(objConfig.getConfigSFX());
        break;
    default:
        sound.setVolume(objConfig.getConfigMusica());
        break;
}
}
void Sound::update(){
    checkStatus();
    updateVolume();
}
