#ifndef SCORE_H
#define SCORE_H
#include <cmath>
#include "States.h"
#include "Configuracion.h"
#include "ArchivoConfiguracion.h"
#include "Savefile.h"
#include "ArchivoSavefile.h"


class Score:public State
{
private:
    sf::Texture mTexture;
    sf::Sprite mBackground;



    ///TEXT
    sf::Font font;
    sf::Text textPosiciones[5];

    int scorePosiciones[5];

public:
    ///Constructor / Destructor
    Score(sf::RenderWindow*, std::stack<State*>* states);
    virtual ~Score();

    ///Methods

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

#endif // SCORE_H
