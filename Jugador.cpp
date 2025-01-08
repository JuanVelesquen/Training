#include "Jugador.h"

Jugador::Jugador(){
    initVariables();
    initTextures();
    initAudio();
}
void Jugador::initTextures(){
    texture.loadFromFile("Textures/Tren/tren-spritesheet.png");
    sprite.setTexture(texture);
    currentFrame = sf::IntRect(0,0,28,64);
    sprite.setTextureRect(currentFrame);
    sprite.setPosition(400.f,450.f);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height);
    textureTrail = new sf::Texture();
    textureTrail->loadFromFile("Textures/Efectos/rastros-tren1.png");

}
void Jugador::initVariables(){
    movementSpeed = 2;
    presion = 1;
    presionCheck = presion;
    presionIncrement = 0.01;
    presionMAX = 2;
    carbon = 800;
    carbonIncrement = 0.1;
    hpMAX = 100;
    hp = hpMAX;
    score = 0;
    money = 100;
    flag = false;
    damage = 1;
    for(int i=0; i < 5;i++){
        mejoras[i] = 0;
    }
}

void Jugador::initAudio(){
    trainSound.setSound("vaporTren2.wav",2);

}
Jugador::~Jugador(){
    for(auto *i: trail){
        delete i;
    }
    delete textureTrail;
}

///SETS
void Jugador::setSprite(sf::Texture texture){
    sprite.setTexture(texture);
}
void Jugador::setSpritePosition(float x,float y){
    sprite.setPosition(x,y);
}
void Jugador::setMovementSpeed(float movementSpeed){
    this->movementSpeed = movementSpeed;
}
void Jugador::setMoney(int money){
    this->money = money;
}
void Jugador::setMejoras(int mejora,int indice){
    if(mejora >= 0 && mejora <= 2){
        mejoras[indice] = mejora;
    }else{
        mejoras[indice] = 0;
    }
}
void Jugador::setHP(float hp){
    this->hp = hp;
}
void Jugador::setHPMAX(float hpMAX){
    this->hp = hpMAX;
}
void Jugador::setScore(int points){
    score = points;
}
void Jugador::setCarbon(float carbon){
    this->carbon = carbon;
}
void Jugador::setCarbonIncrement(float carbonIncrement){
    this->carbonIncrement = carbonIncrement;
}
void Jugador::setCurrentLevel(int level){
    this->currentLevel = level;
}
void Jugador::setPresion(float presion){
    this->presion = presion;
}
void Jugador::setPresionIncrement(float presionIncrement){
    this->presionIncrement = presionIncrement;
}
void Jugador::setPresionMAX(float presionMAX){
    this->presionMAX = presionMAX;
}
void Jugador::setPresionCheck(float presionCheck){
    this->presionCheck = presionCheck;
}

void Jugador::setDamage(int damage){
    this->damage = damage;
}

void Jugador::setKill(bool kill)
{
    this->kill = kill;
}


///GETS

sf::Sprite Jugador::getSprite(){
    return sprite;
}

float Jugador::getMovementSpeed(){
    return movementSpeed;
}
int Jugador::getMoney(){
    return money;
}

int Jugador::getMejoras(int indice){
    return this->mejoras[indice];
}

float Jugador::getCarbon(){
    return carbon;
}
float Jugador::getCarbonIncrement(){
    return carbonIncrement;
}
 int Jugador::getCurrentLevel(){
     return this->currentLevel;
 }
float Jugador::getPresion(){
    return presion;
}
float Jugador::getPresionIncrement(){
    return presionIncrement;
}
float Jugador::getPresionMAX(){
    return presionMAX;
}
float Jugador::getPresionCheck(){
    return presionCheck;
}

const sf::FloatRect Jugador::getBounds()const{
    return sprite.getGlobalBounds();
}

float Jugador::getHP(){
    return this->hp;
}

float Jugador::getHPMAX(){
    return this->hpMAX;
}

int Jugador::getScore(){
    return score;
}

int Jugador::getDamage(){
    return this->damage;
}

bool Jugador::getKill()
{
    return kill;
}


///METHODS

void Jugador::moves(float dt){
    sf::Vector2f movement(0.f, 0.f);
    //double pi = 3.14159265359;
    //double radian = sprite.getRotation() * (pi/180);
    if(carbon > 0){

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(presion <= presionMAX){
                carbon -= carbonIncrement;
                presion += presionIncrement;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if (presion >= presionMAX * 0.25)
                presion -= presionIncrement;

        }
       /* if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::W)){

                movement.y -= movementSpeed * presion;

            //std::cout<<"Rotatioon: "<<sprite.getRotation()<<"\n";
            //std::cout<<"X: "<<movement.x<<"\n";
            //std::cout<<"Y: "<<movement.y<<"\n";
            //carbon -= 0.5;
            //if (presion <= 3)
            //   presion += 0.025;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Keyboard::isKeyPressed(sf::Keyboard::S)){

                movement.y += movementSpeed * presion;
                if (presion >= presionMAX * 0.25)
                    presion -= presionIncrement * 0.1;
        }*/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            /*if(sprite.getRotation() > 330 || sprite.getRotation() <= 30)
                sprite.rotate(-1);*/
            movement.x -= movementSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            /*if(sprite.getRotation() < 30 || sprite.getRotation() >= 330)
                sprite.rotate(1);*/

            movement.x += movementSpeed;
        }

        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            carbon -= 0.5;
            if (presion <= 3)
                presion += 0.025;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
                if (presion >= 0.5)
                    presion -= 0.025;
        }
        */


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            kill=true;
            //std::cout<<"yes"<<std::endl;
        }
        else{kill=false;
       // std::cout<<"not"<<std::endl;
        }


        sprite.move(movement);
    }
}
void Jugador::animation(){
    animationTimer = animationClock.getElapsedTime();
    if(animationTimer >= sf::seconds(0.2f)){
        currentFrame.left += 28;
        if(currentFrame.left >= 112.f){
            currentFrame.left = 0;
        }
        animationTimer = animationClock.restart();
        sprite.setTextureRect(currentFrame);
    }
}
///Jugador Sounds


///TRAIL TRACKS
void Jugador::addTrail(){
    trailSpawnTimer = trailClock.getElapsedTime();
    if(trailSpawnTimer >= sf::seconds(0.1f)){
        trail.push_back(new Effects(textureTrail,sprite.getPosition().x - textureTrail->getSize().x / 2,
                                               sprite.getPosition().y));
        trailSpawnTimer = trailClock.restart();
    }
}
void Jugador::checkTrailBounds(sf::RenderWindow *window){
    if(!trail.empty()){
        for(long long unsigned i = 0; i < trail.size();i++){
            trail[i]->update(movementSpeed * presion);
            if(trail[i]->getSprite().getPosition().y > window->getSize().y)
            {
                trail.erase(trail.begin() + i);
                break;
            }
        }
    }
}
void Jugador::checkPressureLevel(){
    //Sobrepasa la presion maxima ´posible
    if(presion >= presionMAX){
        pressureLevelTime = pressureLevelClock.getElapsedTime();
        if(pressureLevelTime >= sf::seconds(3.f)){
            carbon = 0;
            std::cout<<"BOOM"<<"\n";
            std::cout<<"MOTORS OVERHEATED"<<"\n";
        }
    }else{
        pressureLevelTime = pressureLevelClock.restart();
    }

    //Si la presion es muy baja se apaga
    if(presion <= presionMAX / 4){
        UnderNormalPressureLevelTime = UnderNormalPressureLevelClock.getElapsedTime();
        if(UnderNormalPressureLevelTime >= sf::seconds(3.f)){
            carbon = 0;
            std::cout<<"TOO LITTLE PRESSURE"<<"\n";
            std::cout<<"TURNING MOTORS OFF"<<"\n";
        }
    }else{
        UnderNormalPressureLevelTime = UnderNormalPressureLevelClock.restart();
    }
}

void Jugador::updateTrail(sf::RenderWindow *window){
    if(carbon > 0){
        addTrail();
        checkTrailBounds(window);
    }
}
void Jugador::updateVariables(){
    if(hp <= 0){
        if(carbon > 10){
            carbon = 10;
            money = money / 2;
            std::cout<<"TRAIN DESTROYED"<<"\n";
            std::cout<<"HALF YOUR MONEY WENT TO REPAIR IT"<<"\n";
        }
    }
    if(carbon > 10){
        if(presion >= presionMAX * (3 / 4)){
            carbon -= presion * 0.5;
        }else if(presion <= presionMAX / 2 && presion > presionMAX / 4){
            carbon -= presion * 0.15;
        }else if(presion <= presionMAX / 4){
            carbon -= presion * 0.01;
        }
    }else if(movementSpeed > 0){
        movementSpeed -= 0.1;
        }else{
        carbon = 0;
        movementSpeed = 0;
        std::cout<<"CARBON: 0"<<"\n";
        std::cout<<"NO MORE CARBON LEFT"<<"\n";
    }
    //std::cout<<"Pos: "<<sprite.getPosition().x<<"\n";
    //std::cout<<"Presion: "<<presion<<"\n";
    //std::cout<<"Speed: "<<movementSpeed<<"\n";
}
void Jugador::updateAudio(){
    trainSound.update();
    if(presion >= presionMAX && flag == false){
        trainSound.playAudio();
        flag = true;
    }else if(presion < presionMAX && flag == true)
        flag = false;
}
void Jugador::update(sf::RenderWindow *window, float dt){
    updateVariables();
    updateAudio();
    moves(dt);
    checkPressureLevel();
    updateTrail(window);
    animation();
}

///RENDER Jugador
void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    for(long long unsigned i = 0;i < trail.size();i++){
        target.draw(trail[i]->getSprite(),states);
    }
    target.draw(sprite,states);
}
///RESET
void Jugador::reset(){
    initVariables();
    initTextures();
    initAudio();
    for(long long unsigned i = 0; i < trail.size();i++){
        trail.erase(trail.begin() + i);
        i--;
    }
}
