#ifndef OPTIONSSTATE_H_INCLUDED
#define OPTIONSSTATE_H_INCLUDED

#include <cmath>
#include "States.h"
#include "Configuracion.h"
#include "ArchivoConfiguracion.h"

class Options:public State{
private:
    sf::Texture mTexture;
    sf::Texture mTextureVolumeBar;
    sf::Texture mTextureVolumeSlider;
    sf::Sprite mBackground;
    sf::Sprite musicVolume;
    sf::Sprite slider[2];
    sf::Sprite sfxVolume;

    ///TEXT
    sf::Font font;
    sf::Text titulo;
    sf::Text musicaSubtitulo;
    sf::Text sfkSubtitulo;
    sf::Text porcentajeSFX;
    sf::Text porcentajeMusica;

    int volumenMusica;
    int volumenSFX;

    ///TEMPORTAL MOUSE POS
    sf::Vector2f lastMousePos;
public:
    ///Constructor / Destructor
    Options(sf::RenderWindow*, std::stack<State*>* states);
    virtual ~Options();

    ///Methods
    void save();

    void updateGUI();
    void updateSliders(sf::Vector2f mousePos);
    void updateButtons(bool MBreleased);
    void renderButtons();

    void checkForQuit(bool MBreleased);
    void endState();
    void updateInput(const float& dt,bool MBrealeased);
    void update(const float& dt,bool MBrealeased, sf::Event event);
    void render(sf::RenderTarget *target = nullptr);

private:
    void initBackground();
    void initGUI();
};

#endif // OPTIONSSTATE_H_INCLUDED
