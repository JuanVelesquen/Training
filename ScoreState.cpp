/* */
#include <iostream>
using namespace std;
#include "ScoreState.h"



///Constructor / Destructor
Score::Score(sf::RenderWindow* window, std::stack<State*>* states)
:State(window,states){
    initBackground();
    initGUI();
}
Score::~Score(){

}

///Methods

void Score::initBackground(){
    mTexture.loadFromFile("Textures/Background/trainingScoreLeader.png");
    mBackground.setTexture(mTexture);
    mBackground.setScale(window->getSize().x / mBackground.getGlobalBounds().width,window->getSize().y / mBackground.getGlobalBounds().height);
}

void Score::initGUI(){
   font.loadFromFile("Fonts/Minecraft.ttf");
   for (int i = 0; i < 5; i++){
        textPosiciones[i].setFont(font);
        textPosiciones[i].setFillColor(sf::Color::Black);
        textPosiciones[i].setCharacterSize(36);
        scorePosiciones[4 - i] = 1500 * (i+1);
   }
   std::string nombres[8];
   nombres[0] = "Kloster";
   nombres[1] = "Maxi";
   nombres[2] = "Braian";
   nombres[3] = "Larry";
   nombres[4] = "Bob";
   nombres[5] = "";
   nombres[6] = "";
   nombres[7] = "";

   for (int i = 0; i < 5;i++){
    std::string s = nombres[i];
    s+= ": ";
    s+=std::to_string(scorePosiciones[i]);
    s+=" pts";
   textPosiciones[i].setString(s);
   }

   for(int i = 0;i < 5;i++){
        textPosiciones[4-i].setPosition(window->getSize().x / 2 - textPosiciones[4-i].getGlobalBounds().width/2 ,window->getSize().y - textPosiciones[4-i].getGlobalBounds().height* 2 *(i+1) - 15.f);
   }
   textPosiciones[4].move(0.f,-10.f);

   Configuracion objConfig;
   ArchivoConfiguracion arkConfig("configuracion.dat");
   objConfig = arkConfig.leerRegistro(0);

  Savefile objSave;
   ArchivoSavefile arkSave("savefile.dat");
   int v[8] = {0};
   for(int i = 0; i < 5;i++){
        v[i] = scorePosiciones[i];
   }
   int TAM =  arkSave.contarRegistros();
   for (int i = 0; i < TAM;i++){
        v[5+i] = objConfig.getScore(i);
        objSave = arkSave.leerRegistro(i);
        nombres[5+i] = objSave.getNombre();
   }

   for(int i = 0; i < 8 - 1;i++){
    for(int j = 0; j < 8 - 1 - i;j++){
                if(v[j] < v[j+1]){
                    int temp =  v[j];
                    v[j] =  v[j+1];
                    v[j+1] = temp;
                    std::string tempS = nombres[j];
                    nombres[j] =  nombres[j+1];
                    nombres[j+1] = tempS;
                }
    }
   }

   for (int i = 0; i < 5;i++){
    std::string s = nombres[i];
    s+= ": ";
    s+=std::to_string(v[i]);
    s+=" pts";
   textPosiciones[i].setString(s);
   }





}

void Score::checkForQuit(bool MBreleased){
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        quit = true;
    }
}

void Score::endState(){
        this->quit = true;
}


void Score::updateInput(const float& dt,bool MBreleased){
    this->checkForQuit(MBreleased);
}

void Score::update(const float& dt,bool MBreleased, sf::Event event){
    this->updateMousePosition();
    this->updateInput(dt,MBreleased);

}

void Score::render(sf::RenderTarget *target){
    if(!target)
        target = this->window;

    target->draw(mBackground);

    for (int i = 0; i < 5;i++){
        target->draw(textPosiciones[i]);
    }

    //target->draw(titulo);

}
