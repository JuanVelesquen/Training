#include "Button.h"

Button::Button(){
    ///ANIMATION TIMER
    AnimationCounter = 0;

    ///INIT AUDIO
    click.setSound("click.wav",2);

}

Button::~Button(){

}
void Button::setButton(sf::Texture *textureIdle, sf::Texture *textureActive,sf::Vector2f location,int type){
    spriteIdle.setTexture(*textureIdle);
    spriteActive.setTexture(*textureActive);
    spriteIdle.setPosition(location.x - spriteIdle.getGlobalBounds().width / 2,location.y);
    spriteActive.setPosition(location.x - spriteIdle.getGlobalBounds().width / 2,location.y);
    currentSprite = spriteIdle;
    this->type = type;
}

btn_states Button::getState(){
    return state;
}

bool Button::isPressed(bool MBreleased,sf::Vector2f mousePos){
    if(state == btn_active)
    {

        if(AnimationCounter <= 2){
            currentSprite = spriteActive;
            AnimationCounter++;
        }else if(AnimationCounter > 2){
            if(type != 1){
                currentSprite = spriteIdle;
            }
            AnimationCounter++;
        }
    }

    if(AnimationCounter >= 3 && MBreleased == true){
        AnimationCounter = 0;
        if(type == 1){
            spriteIdle.setTexture(*spriteActive.getTexture());
            setState(btn_idle);
        }
        if(currentSprite.getGlobalBounds().contains(mousePos)){
            click.playAudio();
            return true;
        }

    }
    //std::cout<<AnimationCounter<<"\n";
    return false;
}



void Button::setState(btn_states state){
    this->state = state;
    switch(this->state){
     case btn_idle:
         currentSprite = spriteIdle;
        break;
     case btn_active:
         currentSprite = spriteActive;
        break;
     default:
         currentSprite = spriteIdle;
        break;
    }
}

sf::Sprite Button::getSprite(){
    return currentSprite;
}

void Button::checkClick(sf::Vector2f mousePos){
    switch(type){
    case 0:
        if(currentSprite.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            setState(btn_active);
        }else{
            setState(btn_idle);
        }
        break;
    case 1:
        if(state != btn_active){
            if(currentSprite.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                setState(btn_active);
        }
        break;
    default:
        if(currentSprite.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            setState(btn_active);
        }else{
            setState(btn_idle);
        }
        break;
    }
}


void Button::update(sf::Vector2f mousePos){
    click.update();
    checkClick(mousePos);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    target.draw(currentSprite,states);
}
