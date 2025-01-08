#include "GameState.h"

///Constructor / Destructor
GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
:State(window,states){
    initTextures();
    initWorldBackground();
    initPauseMenu();
    initCheckBounds();
    initUpgradesTextures();
    initHud();
    initUpgradesButtons();
    initSpawnTimers();
    loadFile();
}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states,int jugadorJugando)
:State(window,states){
    initTextures();
    initWorldBackground();
    initPauseMenu();
    initCheckBounds();
    initUpgradesTextures();
    initHud();
    initUpgradesButtons();
    initSpawnTimers();
    this->numeroJugador = jugadorJugando;
    loadFile();
    initEnemy();
}
GameState::~GameState(){
    saveFile();
    for (auto *i: arboles){
        delete i;
    }
    for (auto *i: piedras){
        delete i;
    }
    for(auto &i : mTextures){
        delete i.second;
    }
}
///INTIALIZERS
void GameState::loadFile(){
    Savefile objSave;
    ArchivoSavefile arkSave("savefile.dat");
    objSave = arkSave.leerRegistro(numeroJugador);

    jugador.setCurrentLevel(objSave.getNivelesJugador());


    jugador.setMoney(objSave.getDinero());
    for (int i = 0; i < 5;i++){
        jugador.setMejoras(objSave.getMejoras(i),i);
    }

    if(jugador.getMejoras(0) >= 1){
        jugador.setPresionIncrement(jugador.getPresionIncrement()*1.1f);
        jugador.setDamage(jugador.getDamage()*1.1f);
    }
    if(jugador.getMejoras(0) == 2){
        jugador.setPresionIncrement(jugador.getPresionIncrement()*1.25f);
        jugador.setDamage(jugador.getDamage()*1.25f);
    }

    if(jugador.getMejoras(1) >= 1){
        jugador.setMovementSpeed(jugador.getMovementSpeed()*1.10);
        jugador.setPresionMAX(jugador.getPresionMAX() * 1.1f);
        jugador.setPresion(jugador.getPresionMAX() / 2);
    }
    if(jugador.getMejoras(1) == 2){
        jugador.setMovementSpeed(jugador.getMovementSpeed()*1.30);
        jugador.setPresionMAX(jugador.getPresionMAX() * 1.25f);
        jugador.setPresion(jugador.getPresionMAX() / 2);
    }

    if(jugador.getMejoras(2) >= 1){
            jugador.setCarbon(jugador.getCarbon() * 1.35);
    }
    if(jugador.getMejoras(2) == 2){
            jugador.setCarbon(jugador.getCarbon() * 1.50);
    }

    if(jugador.getMejoras(3) >= 1){
           jugador.setPresionMAX(jugador.getPresionMAX() * 1.25f);
           jugador.setPresion(jugador.getPresionMAX() / 2);
    }
    if(jugador.getMejoras(3) == 2){
            jugador.setPresionMAX(jugador.getPresionMAX() * 1.25f);
            jugador.setPresion(jugador.getPresionMAX() / 2);
    }

    if(jugador.getMejoras(4) >= 1){
           jugador.setPresionMAX(jugador.getPresionMAX() * 1.25f);
           jugador.setPresion(jugador.getPresionMAX() / 2);
    }
    if(jugador.getMejoras(4) == 2){
        jugador.setPresionMAX(jugador.getPresionMAX() * 1.25f);
        jugador.setPresion(jugador.getPresionMAX() / 2);
    }
    /*for(int i = 0; i < 5;i++){
        std::cout<<"Mejora "<<i+1<<": "<<jugador.getMejoras(i)<<"\n";
    }
    std::cout<<"Vel: "<<jugador.getMovementSpeed()<<"\n";
    std::cout<<"Presion: "<<jugador.getPresion()<<"\n";
    std::cout<<"Carboon: "<<jugador.getCarbon()<<"\n";*/
}

void GameState::saveFile(){
    Savefile objSave;
    ArchivoSavefile arkSave("savefile.dat");
    objSave = arkSave.leerRegistro(numeroJugador);
    if(objSave.getNombre() == NULL)
        objSave.setNombre("NAME");
    objSave.setDinero(jugador.getMoney());
    if(jugador.getScore() > objSave.getPuntos()){
        objSave.setPuntos(jugador.getScore());
    }
    //std::cout<<"Time 1: "<<objSave.getTiempoJugado().asSeconds()<<"\n";
    objSave.setTiempoJugado(objSave.getTiempoJugado() + timePlayed);
    //std::cout<<"Time 2: "<<objSave.getTiempoJugado().asSeconds()<<"\n";
    for (int i = 0;i < 5;i++){
        objSave.setMejoras(jugador.getMejoras(i),i);
    }
    objSave.setNivelesJugador(jugador.getCurrentLevel());
    arkSave.modificarRegistro(objSave,numeroJugador);

    Configuracion objConfig;
    ArchivoConfiguracion arkConfig("configuracion.dat");
    objConfig = arkConfig.leerRegistro(0);
    if(jugador.getScore() + distance > objConfig.getScore(numeroJugador))
        objConfig.setScore(jugador.getScore() + distance,numeroJugador);

    arkConfig.modificarRegistro(objConfig,0);
}
void GameState::initTextures(){
    ///BACKGROUND TEXTURE
    mTextures["BACKGROUND"] = new sf::Texture();
    mTextures["BACKGROUND"]->loadFromFile("Textures/Background/background-02.png");

    ///BACKGROUND TEXTURE
    mTextures["CHECKBOUND"] = new sf::Texture();
    mTextures["CHECKBOUND"]->loadFromFile("Textures/Limites/lado_izquierdo5.png");


    ///OBSTACLES TEXTURES

    ///TREES

    ///PINE TREES
    mTextures["TREE_PINE"] = new sf::Texture();
    mTextures["TREE_PINE"]->loadFromFile("Textures/arboles/arbol-01.png");

    ///DEAD TREES
    mTextures["TREE_DEAD"] = new sf::Texture();
    mTextures["TREE_DEAD"]->loadFromFile("Textures/arboles/arbol-roto/cortado.png");

    ///ROCKS

    ///COMMON ROCK

    mTextures["ROCK_COMMON"] = new sf::Texture();
    mTextures["ROCK_COMMON"]->loadFromFile("Textures/piedras/piedra-1/piedra-01.png");

    ///DEAD ROCK
    mTextures["ROCK_DEAD"] = new sf::Texture();
    mTextures["ROCK_DEAD"]->loadFromFile("Textures/piedras/piedra-rota/piedra-rota.png");

    ///HUD

    ///METER BASE

    mTextures["METER_BASE"] = new sf::Texture();
    mTextures["METER_BASE"]->loadFromFile("Textures/HUD/meter_base.png");

    ///METER NEEDLE
    mTextures["METER_NEEDLE"] = new sf::Texture();
    mTextures["METER_NEEDLE"]->loadFromFile("Textures/HUD/medidor_aguja.png");


    ///GAME OVER

    ///BUTTONS

    ///GAME OVER PAUSE MENU
    mTextures["GAME_OVER"] = new sf::Texture();
    mTextures["GAME_OVER"]->loadFromFile("Textures/finnivel/game_over.png");

    ///PLAY AGAIN

    ///IDLE
    mTextures["PLAY_AGAIN_IDLE"] = new sf::Texture();
    mTextures["PLAY_AGAIN_IDLE"]->loadFromFile("Textures/finnivel/otra_vez0.png");

    ///ACTIVE
    mTextures["PLAY_AGAIN_ACTIVE"] = new sf::Texture();
    mTextures["PLAY_AGAIN_ACTIVE"]->loadFromFile("Textures/finnivel/otra_vez1.png");

    ///RETURN TO MENU

    ///IDLE
    mTextures["RETURN_MENU_IDLE"] = new sf::Texture();
    mTextures["RETURN_MENU_IDLE"]->loadFromFile("Textures/finnivel/volver_al_menu0.png");

    ///ACTIVE
    mTextures["RETURN_MENU_ACTIVE"] = new sf::Texture();
    mTextures["RETURN_MENU_ACTIVE"]->loadFromFile("Textures/finnivel/volver_al_menu1.png");

    ///BUY UPGRADE BUTTON

    ///IDLE
    mTextures["BUY_IDLE"] = new sf::Texture();
    mTextures["BUY_IDLE"]->loadFromFile("Textures/finnivel/comprar_0.png");

    ///ACTIVE
    mTextures["BUY_ACTIVE"] = new sf::Texture();
    mTextures["BUY_ACTIVE"]->loadFromFile("Textures/finnivel/comprar_1.png");

    ///UPGRADE BUTTONS

    ///BUTTON_ATRAPA_VACAS
    mTextures["BUTTON_ATRAPA_VACAS_IDLE"] = new sf::Texture();
    mTextures["BUTTON_ATRAPA_VACAS_IDLE"]->loadFromFile("Textures/botones/boton_atrapa_vacas_mejora_idle.png");

    ///BUTTON_ATRAPA_VACAS
    mTextures["BUTTON_ATRAPA_VACAS_ACTIVE"] = new sf::Texture();
    mTextures["BUTTON_ATRAPA_VACAS_ACTIVE"]->loadFromFile("Textures/botones/boton_atrapa_vacas_mejora_active.png");

    ///LOCOMOTORA
    mTextures["BUTTON_LOCOMOTORA_IDLE"] = new sf::Texture();
    mTextures["BUTTON_LOCOMOTORA_IDLE"]->loadFromFile("Textures/botones/boton_locomotora_mejora_idle.png");
    ///LOCOMOTORA
    mTextures["BUTTON_LOCOMOTORA_ACTIVE"] = new sf::Texture();
    mTextures["BUTTON_LOCOMOTORA_ACTIVE"]->loadFromFile("Textures/botones/boton_locomotora_mejora_active.png");

    ///CARBONERA
    mTextures["BUTTON_CARBONERA_IDLE"] = new sf::Texture();
    mTextures["BUTTON_CARBONERA_IDLE"]->loadFromFile("Textures/botones/boton_carbonera_mejora_idle.png");

    ///CARBONERA
    mTextures["BUTTON_CARBONERA_ACTIVE"] = new sf::Texture();
    mTextures["BUTTON_CARBONERA_ACTIVE"]->loadFromFile("Textures/botones/boton_carbonera_mejora_active.png");

    ///ORUGA LOCOMOTORA
    mTextures["BUTTON_ORUGA_LOCOMOTORA_IDLE"] = new sf::Texture();
    mTextures["BUTTON_ORUGA_LOCOMOTORA_IDLE"]->loadFromFile("Textures/botones/boton_oruga_locomotora_mejora_idle.png");
    ///ORUGA LOCOMOTORA
    mTextures["BUTTON_ORUGA_LOCOMOTORA_ACTIVE"] = new sf::Texture();
    mTextures["BUTTON_ORUGA_LOCOMOTORA_ACTIVE"]->loadFromFile("Textures/botones/boton_oruga_locomotora_mejora_active.png");

    ///ORUGA CARBONERA
    mTextures["BUTTON_ORUGA_CARBONERA_IDLE"] = new sf::Texture();
    mTextures["BUTTON_ORUGA_CARBONERA_IDLE"]->loadFromFile("Textures/botones/boton_oruga_carbonera_mejora_idle.png");
    ///ORUGA CARBONERA
    mTextures["BUTTON_ORUGA_CARBONERA_ACTIVE"] = new sf::Texture();
    mTextures["BUTTON_ORUGA_CARBONERA_ACTIVE"]->loadFromFile("Textures/botones/boton_oruga_carbonera_mejora_active.png");
}

///INIT PAUSE MENU GUI
void GameState::initPauseMenu(){

    pauseSprite.setTexture(*mTextures["GAME_OVER"]);
    pauseSprite.setOrigin(pauseSprite.getGlobalBounds().width / 2,pauseSprite.getGlobalBounds().height / 2);
    pauseSprite.setPosition(sf::Vector2f(window->getSize().x / 2 ,window->getSize().y / 1.8));
    playAgain.setButton(mTextures["PLAY_AGAIN_IDLE"], mTextures["PLAY_AGAIN_ACTIVE"], sf::Vector2f(pauseSprite.getPosition().x - pauseSprite.getGlobalBounds().width / 3, pauseSprite.getPosition().y - mTextures["PLAY_AGAIN_IDLE"]->getSize().y * 1.5),0);
    returnMenu.setButton(mTextures["RETURN_MENU_IDLE"], mTextures["RETURN_MENU_ACTIVE"],sf::Vector2f(pauseSprite.getPosition().x - pauseSprite.getGlobalBounds().width / 3,pauseSprite.getPosition().y + mTextures["RETURN_MENU_IDLE"]->getSize().y * 0.5) ,0);
    BuyUpgrade.setButton(mTextures["BUY_IDLE"], mTextures["BUY_ACTIVE"],sf::Vector2f(pauseSprite.getPosition().x + pauseSprite.getGlobalBounds().width / 3,pauseSprite.getPosition().y + mTextures["RETURN_MENU_IDLE"]->getSize().y * 1.5) ,0);
}

void GameState::initSpawnTimers(){
    ///SPAWN TIMER ARBOLES NORMALES
    spawnTimerArboles.spawnTimerIncrement = 1.5f;
    spawnTimerArboles.spawnTimerMAX = 100.f;
    spawnTimerArboles.spawnTimer = spawnTimerArboles.spawnTimerMAX;

    ///SPAWN TIMER PIEDRAS NORMALES
    spawnTimerPiedras.spawnTimerIncrement = 0.5f;
    spawnTimerPiedras.spawnTimerMAX = 150.f;
    spawnTimerPiedras.spawnTimer = 0.f;
}
///INTIALIZE BACKGROUND
void GameState::initWorldBackground(){
    worldBackground.setTexture(*mTextures["BACKGROUND"]);
    worldBackground.setPosition(0.f,window->getSize().y - worldBackground.getGlobalBounds().height);
}
///INTIALIZE CHECKBOUNDS
void GameState::initCheckBounds(){
    checkboundLeft.setTexture(*mTextures["CHECKBOUND"]);
    checkboundLeft.setPosition(0.f,window->getSize().y - worldBackground.getGlobalBounds().height);
    checkboundRight.setTexture(*mTextures["CHECKBOUND"]);
    checkboundRight.setScale(-1.f,1.f);
    checkboundRight.setPosition(window->getSize().x,window->getSize().y - worldBackground.getGlobalBounds().height);
}
///INTIALIZE HUD
void GameState::initHud(){
    meterBase.setTexture(*mTextures["METER_BASE"]);
    meterBase.setOrigin(meterBase.getGlobalBounds().width / 2,meterBase.getGlobalBounds().height);
    meterBase.setPosition(meterBase.getGlobalBounds().width / 2, meterBase.getGlobalBounds().height);

    needleMeter.setTexture(*mTextures["METER_NEEDLE"]);
    needleMeter.setOrigin(needleMeter.getGlobalBounds().width / 2,needleMeter.getGlobalBounds().height / 2);
    needleMeter.setPosition(meterBase.getPosition().x ,meterBase.getPosition().y / 2 - 3.f);
    needleMeter.rotate(-45);

    ///INIT TEXT
    sf::Color color = sf::Color(0.f,0.f,0.f,210);
    font.loadFromFile("Fonts/Minecraft.ttf");
    textPoints.setFont(font);
    textPoints.setCharacterSize(24);
    textPoints.setFillColor(color);

    textDistance.setFont(font);
    textDistance.setCharacterSize(24);

    textDistance.setFillColor(color);
    sf::String s = "Distance: ";
    s += "0 km";
    textDistance.setString(s);
    textDistance.setPosition(meterBase.getPosition().x - textDistance.getGlobalBounds().width / 3,meterBase.getPosition().y );


    textArbolesHarvested.setFont(font);
    textArbolesHarvested.setCharacterSize(26);
    textArbolesHarvested.setFillColor(color);

    textPiedrasHarvested.setFont(font);
    textPiedrasHarvested.setCharacterSize(26);
    textPiedrasHarvested.setFillColor(color);

    textTotal.setFont(font);
    textTotal.setCharacterSize(26);
    textTotal.setFillColor(color);

    textSubtotal.setFont(font);
    textSubtotal.setCharacterSize(26);
    textSubtotal.setFillColor(color);

    textPlayerMoney.setFont(font);
    textPlayerMoney.setCharacterSize(26);
    textPlayerMoney.setFillColor(color);

    textUpgrades.setFont(font);
    textUpgrades.setCharacterSize(20);
    textUpgrades.setFillColor(color);
    textUpgrades.setPosition(pauseSprite.getPosition().x + pauseSprite.getGlobalBounds().width / 5 ,pauseSprite.getPosition().y - pauseSprite.getGlobalBounds().height / 5);

    ///INIT VARIABLES HUD
    distance = 0;
    arbolesHarvested = 0;
    piedrasHarvested = 0;
    flagUpgradeText = false;
    total = 0;
    ///INIT AUDIO
    arcadeMusic.setSound("arcadeMusic.wav",1);
    arcadeMusic.playAudio();

    ///INIT UPGRADES
    updateUpgradeTextures();
    atrapaVacas.setPosition(pauseSprite.getPosition().x + atrapaVacas.getGlobalBounds().width * 1.2,pauseSprite.getPosition().y - atrapaVacas.getGlobalBounds().height * 3);
    locomotora.setPosition(pauseSprite.getPosition().x + locomotora.getGlobalBounds().width * 1.2,pauseSprite.getPosition().y - locomotora.getGlobalBounds().height * 3);
    carbonera.setPosition(pauseSprite.getPosition().x + carbonera.getGlobalBounds().width * 1.2,pauseSprite.getPosition().y - carbonera.getGlobalBounds().height * 3);
    orugaLocomotora.setPosition(pauseSprite.getPosition().x + orugaLocomotora.getGlobalBounds().width * 1.2,pauseSprite.getPosition().y - orugaLocomotora.getGlobalBounds().height * 3);
    orugaCarbonera.setPosition(pauseSprite.getPosition().x + orugaCarbonera.getGlobalBounds().width * 1.2,pauseSprite.getPosition().y - orugaCarbonera.getGlobalBounds().height * 3);

}
///INITIALIZE UPGRADED BUTTONS
void GameState::initUpgradesButtons(){
    botonMejoras[0].setButton(mTextures["BUTTON_ATRAPA_VACAS_ACTIVE"],mTextures["BUTTON_ATRAPA_VACAS_ACTIVE"],sf::Vector2f(atrapaVacas.getPosition().x + atrapaVacas.getGlobalBounds().width - mTextures["BUTTON_ATRAPA_VACAS_ACTIVE"]->getSize().x / 2, atrapaVacas.getPosition().y + atrapaVacas.getGlobalBounds().height  / 2 + 1.f),1);
    botonMejoras[1].setButton(mTextures["BUTTON_LOCOMOTORA_IDLE"],mTextures["BUTTON_LOCOMOTORA_ACTIVE"],sf::Vector2f(atrapaVacas.getPosition().x + atrapaVacas.getGlobalBounds().width - mTextures["BUTTON_LOCOMOTORA_ACTIVE"]->getSize().x / 1.25, atrapaVacas.getPosition().y),1);
    botonMejoras[2].setButton(mTextures["BUTTON_CARBONERA_IDLE"],mTextures["BUTTON_CARBONERA_ACTIVE"],sf::Vector2f(atrapaVacas.getPosition().x + mTextures["BUTTON_CARBONERA_ACTIVE"]->getSize().x / 2, atrapaVacas.getPosition().y + 4.f),1);
    botonMejoras[3].setButton(mTextures["BUTTON_ORUGA_LOCOMOTORA_IDLE"],mTextures["BUTTON_ORUGA_LOCOMOTORA_ACTIVE"],sf::Vector2f(atrapaVacas.getPosition().x + atrapaVacas.getGlobalBounds().width / 2 + mTextures["BUTTON_ORUGA_LOCOMOTORA_ACTIVE"]->getSize().x / 3, atrapaVacas.getPosition().y + atrapaVacas.getGlobalBounds().height  / 1.5 - 1.f),1);
    botonMejoras[4].setButton(mTextures["BUTTON_ORUGA_CARBONERA_IDLE"],mTextures["BUTTON_ORUGA_CARBONERA_ACTIVE"],sf::Vector2f(atrapaVacas.getPosition().x + mTextures["BUTTON_ORUGA_CARBONERA_ACTIVE"]->getSize().x / 2, atrapaVacas.getPosition().y + atrapaVacas.getGlobalBounds().height  / 1.6),1);
    btnMejoraPresionado = 0;

    ///INITIALIZE UPGRADES PRICES
    upgradesPrice[0][0] = 3500;
    upgradesPrice[0][1] = 6500;
    upgradesPrice[1][0] = 3000;
    upgradesPrice[1][1] = 7000;
    upgradesPrice[2][0] = 2300;
    upgradesPrice[2][1] = 5000;
    upgradesPrice[3][0] = 3000;
    upgradesPrice[3][1] = 6000;
    upgradesPrice[4][0] = 2500;
    upgradesPrice[4][1] = 4500;

        std::string s = "";
    if(jugador.getMejoras(0) == 0){
        s = "+10% reduction of\n pressure\n";
        s += "+10% harvested\n materials\n";
        s += "-15% reduction of\n  velocity\n";
        s += std::to_string(upgradesPrice[0][0]);
        s+="$";
    }else if(jugador.getMejoras(0) == 1){
        s = "+25% reduction of\n pressure\n";
        s+= "+25% harvested\n materials\n";
        s += "-45% reduction of\n  velocity\n";
        s += std::to_string(upgradesPrice[0][1]);
        s+="$";
    }
    textUpgrades.setString(s);
}
//INTIALIZE ENEMY

void GameState::initEnemy(){
    enemy.initEnemy(50.f,2.f);
}

///Methods

void GameState::setPlayerUpgrades(){
    Savefile objSave;
    ArchivoSavefile arkSave("savefile.dat");
    objSave = arkSave.leerRegistro(numeroJugador);
    switch(btnMejoraPresionado){
    case 0:
        if(jugador.getMejoras(btnMejoraPresionado) == 0 &&
           jugador.getMejoras(btnMejoraPresionado) != objSave.getMejoras(btnMejoraPresionado)){
            jugador.setPresionIncrement(jugador.getPresionIncrement()*0.9f);
            jugador.setDamage(jugador.getDamage()*1.1f);
            jugador.setMovementSpeed(jugador.getMovementSpeed()*1.15);

        }else if(jugador.getMejoras(btnMejoraPresionado) == 1 &&
           jugador.getMejoras(btnMejoraPresionado) != objSave.getMejoras(btnMejoraPresionado)){
            jugador.setPresionIncrement(jugador.getPresionIncrement()*0.75f);
            jugador.setDamage(jugador.getDamage()*1.25f);
            jugador.setMovementSpeed(jugador.getMovementSpeed()*1.45);
        }
        break;
    case 1:
        if(jugador.getMejoras(btnMejoraPresionado) == 0 &&
           jugador.getMejoras(btnMejoraPresionado) != objSave.getMejoras(btnMejoraPresionado)){
            jugador.setMovementSpeed(jugador.getMovementSpeed()*1.10);
            jugador.setPresionIncrement(jugador.getPresionIncrement()*0.9f);

        }else if(jugador.getMejoras(btnMejoraPresionado) == 1 &&
           jugador.getMejoras(btnMejoraPresionado) != objSave.getMejoras(btnMejoraPresionado)){
            jugador.setMovementSpeed(jugador.getMovementSpeed()*1.30);
            jugador.setPresionIncrement(jugador.getPresionIncrement()*0.75f);

        }
        break;
    case 2:
        if(jugador.getMejoras(btnMejoraPresionado) == 0 &&
           jugador.getMejoras(btnMejoraPresionado) != objSave.getMejoras(btnMejoraPresionado)){
               jugador.setCarbon(jugador.getCarbon()*1.35);

        }else if (jugador.getMejoras(btnMejoraPresionado) == 1 &&
           jugador.getMejoras(btnMejoraPresionado) != objSave.getMejoras(btnMejoraPresionado)){
               jugador.setCarbon(jugador.getCarbon()*1.50);

        }
        break;
    case 3:
        if(jugador.getMejoras(btnMejoraPresionado) == 0 &&
           jugador.getMejoras(btnMejoraPresionado) != objSave.getMejoras(btnMejoraPresionado)){
               jugador.setMovementSpeed(jugador.getMovementSpeed()*1.20);

        }else if(jugador.getMejoras(btnMejoraPresionado) == 1 &&
           jugador.getMejoras(btnMejoraPresionado) != objSave.getMejoras(btnMejoraPresionado)){
               jugador.setMovementSpeed(jugador.getMovementSpeed()*1.50);

        }
        break;
    case 4:
        if(jugador.getMejoras(btnMejoraPresionado) == 0 &&
           jugador.getMejoras(btnMejoraPresionado) != objSave.getMejoras(btnMejoraPresionado)){
               jugador.setMovementSpeed(jugador.getMovementSpeed()*1.10);
        }else if(jugador.getMejoras(btnMejoraPresionado) == 1 &&
           jugador.getMejoras(btnMejoraPresionado) != objSave.getMejoras(btnMejoraPresionado)){
               jugador.setMovementSpeed(jugador.getMovementSpeed()*1.15);
        }
        break;
    }
}
///UPDATE BACKGROUND
void GameState::backgroundLoop(){
    //std::cout<<"Pos Y: "<<worldBackground.getPosition().y<<"\n";
    worldBackground.move(0.f,jugador.getMovementSpeed() * jugador.getPresion());
    if(worldBackground.getPosition().y >= -1.f){
        worldBackground.setPosition(0.f,window->getSize().y - worldBackground.getGlobalBounds().height);
    }

    checkboundLeft.move(0.f,jugador.getMovementSpeed() * jugador.getPresion());
    if(checkboundLeft.getPosition().y >= -14.89f){
        checkboundLeft.setPosition(0.f,window->getSize().y - worldBackground.getGlobalBounds().height);
    }
    checkboundRight.move(0.f,jugador.getMovementSpeed() * jugador.getPresion());
    if(checkboundRight.getPosition().y >= -14.89f){
        checkboundRight.setPosition(window->getSize().x,window->getSize().y - worldBackground.getGlobalBounds().height);
    }
}

///OBSTACLES

///RESPAWN OBSTACLES
void GameState::respawnObstacles(){

    spawnTimerPiedras.spawnTimer += spawnTimerPiedras.spawnTimerIncrement * jugador.getPresion();
    if(spawnTimerPiedras.spawnTimer >= spawnTimerPiedras.spawnTimerMAX)
    {
        int loops = rand() % 3 + 1;
        //std::cout<<"Loops: "<<loops<<"\n";
        for(int i = 0; i < loops; i++){
            int dirX1 = rand() % static_cast<int>(window->getSize().x / 2) + checkboundLeft.getGlobalBounds().width;
            int dirX2 = 10;
            //std::cout<<"Dir X1: "<<dirX1<<"\n";
            //std::cout<<"Dir X2: "<<dirX2<<"\n";
            int spawnGroup = rand() % 5 + 1;
            //std::cout<<"Spawn group: "<<spawnGroup<<"\n";
            for(int j = 0; j < spawnGroup; j++){
                piedras.push_back(new Piedra(window,dirX1,dirX2,mTextures["ROCK_COMMON"],mTextures["ROCK_DEAD"],0));
                if(j % 2 == 0)
                    dirX1 += mTextures["ROCK_COMMON"]->getSize().x;
                //std::cout<<"Arbol " <<j+1<<" : spawneo en "<< piedras[j]->getSprite().getPosition().x<<"\n";
            }
        }
        spawnTimerPiedras.spawnTimer = 0;
    }

   spawnTimerArboles.spawnTimer += spawnTimerArboles.spawnTimerIncrement * jugador.getPresion();
    if(spawnTimerArboles.spawnTimer >= spawnTimerArboles.spawnTimerMAX)
    {
        //bound al principio miden 50.f
        int loops = rand() % 3 + 1;
        //std::cout<<"Loops: "<<loops<<"\n";
        for(int i = 0; i < loops; i++){
            int dirX1 = rand() % static_cast<int>(window->getSize().x / 2) + checkboundLeft.getGlobalBounds().width * 2;
            int dirX2 = 30;
            //std::cout<<"Dir X1: "<<dirX1<<"\n";
            //std::cout<<"Dir X2: "<<dirX2<<"\n";
            int spawnGroup = rand() % 10 + 5;
            //std::cout<<"Spawn group: "<<spawnGroup<<"\n";
            for(int j = 0; j < spawnGroup; j++){
                arboles.push_back(new Arbol(window,dirX1,dirX2,mTextures["TREE_PINE"],mTextures["TREE_DEAD"],0));
                if(j % 2 == 0)
                    dirX1 += mTextures["TREE_PINE"]->getSize().x;
                //std::cout<<"Arbol " <<j+1<<" : spawneo en "<< arboles[j]->getSprite().getPosition().x<<"\n";
            }
        }
        spawnTimerArboles.spawnTimer = 0;
    }

}

///CHECK OBSTACLES BOUNDS AND DELETE THEM IF NECESSARY
void GameState::checkObstaclesBounds(){
    ///PIEDRAS
    if(!piedras.empty()){
        for(long long unsigned int i = 0; i < piedras.size(); i++){
            ///CHECK IF ROCKS HIT EACH OTHER, IF THEY DO WE DELETE ONE
            for(long long unsigned int j = 0; j < piedras.size(); j++){
                if(piedras[i]->getBounds().intersects(piedras[j]->getBounds()))
                {
                    if(piedras[i]->getSprite().getPosition().y < piedras[j]->getSprite().getPosition().y && i > j)
                    {
                        //std::cout<<"piedra l "<<i+1<<": "<<piedras[i]->getSprite().getPosition().y<<"\n";
                        //std::cout<<"piedra 2 "<<i+1<<": "<<piedras[j]->getSprite().getPosition().y<<"\n";
                        piedras.erase(piedras.begin() + j);
                        j--;
                    }
                }
            }
            ///CHECK IF ROCKS HIT A TREE, IF IT DO WE DELETE THE TREE
            for(long long unsigned int j = 0; j < arboles.size(); j++){
                if(piedras[i]->getBounds().intersects(arboles[j]->getBounds()))
                {
                    arboles.erase(arboles.begin() + j);
                    j--;
                }
            }
            ///CHECK IF OBSTACLE NEEDS TO BE DELETED
            if(piedras[i]->getSprite().getPosition().y > window->getSize().y)
            {
                piedras.erase(piedras.begin() + i);
                i--;
            }
        }
    }
    ///ARBOLES
    if(!arboles.empty()){
        for(long long unsigned int i = 0; i < arboles.size(); i++){
            ///CHECK IF TREES HIT EACH OTHER, IF THEY DO WE DELETE ONE
            for(long long unsigned int j = 0; j < arboles.size(); j++){
                if(arboles[i]->getBounds().intersects(arboles[j]->getBounds()))
                {
                    if(arboles[i]->getSprite().getPosition().y < arboles[j]->getSprite().getPosition().y && i > j)
                    {
                    //std::cout<<"Arbo l "<<i+1<<": "<<arboles[i]->getSprite().getPosition().y<<"\n";
                    //std::cout<<"Arbo 2 "<<i+1<<": "<<arboles[j]->getSprite().getPosition().y<<"\n";
                    arboles.erase(arboles.begin() + j);
                    j--;
                    }
                }
            }
            ///CHECK IF OBSTACLE NEEDS TO BE DELETED
            if(arboles[i]->getSprite().getPosition().y > window->getSize().y)
            {
                arboles.erase(arboles.begin() + i);
                i--;
            }
        }
    }

    moveObstacles();
}
///MOVE OBSTACLES
void GameState::moveObstacles(){
    ///ARBOLES
    for(long long unsigned int i = 0; i < arboles.size(); i++){
         ///OBSTACLES MOVES
        arboles[i]->moves((jugador.getMovementSpeed() * jugador.getPresion()));
    }
    ///PIEDRAS
    for(long long unsigned int i = 0; i < piedras.size(); i++){
        ///OBSTACLES MOVES
        piedras[i]->moves((jugador.getMovementSpeed() * jugador.getPresion()));
    }
}

///UPDATE OBSTACLES
void GameState::updateObstacles(){
    respawnObstacles();
    checkObstaclesBounds();
}

///PLAYER
void GameState::checkBoundsPlayer(){
    ///CHECKBOUND WITH WINDOW
    if(jugador.getSprite().getPosition().x <= jugador.getSprite().getGlobalBounds().width / 4 + checkboundLeft.getGlobalBounds().width){
        jugador.setSpritePosition(jugador.getSprite().getGlobalBounds().width / 4 + checkboundLeft.getGlobalBounds().width,jugador.getSprite().getPosition().y);
    }
    if(jugador.getSprite().getPosition().y <= window->getSize().y / 3){
        jugador.setSpritePosition(jugador.getSprite().getPosition().x, window->getSize().y / 3);
    }
    if(jugador.getSprite().getPosition().x >= window->getSize().x - jugador.getSprite().getGlobalBounds().width / 4 - checkboundRight.getGlobalBounds().width){
        jugador.setSpritePosition(window->getSize().x - jugador.getSprite().getGlobalBounds().width / 4 - checkboundRight.getGlobalBounds().width,jugador.getSprite().getPosition().y);
    }
    if(jugador.getSprite().getPosition().y >= window->getSize().y - jugador.getSprite().getGlobalBounds().height / 4){
        jugador.setSpritePosition(jugador.getSprite().getPosition().x,window->getSize().y - jugador.getSprite().getGlobalBounds().height / 4);
    }
    ///UPDATE JUAN.M.
       //std::cout << jugador.getPresion()<<std::endl;
       float damage =  jugador.getDamage();
       float damage2 =  jugador.getDamage() ;
     for(long long unsigned int i = 0; i < arboles.size(); i++)
        {
            if(!arboles[i]->getDead())
            {
                if(arboles[i]->getBounds().intersects(jugador.getBounds())){
                    if(jugador.getKill())
                    {
                        arboles[i]->setHP(std::round(arboles[i]->getHP() - damage));
                        if(arboles[i]->getHP() <= 0)
                            arbolesHarvested += 1;

                    }else{
                        arboles[i]->setHP(arboles[i]->getHP() - damage2);
                        jugador.setHP(jugador.getHP() - arboles[i]->getDamage());
                        std::cout<<"HP: "<<jugador.getHP()<<"\n";
                        if(jugador.getPresion() > jugador.getPresionMAX() / 4){
                            jugador.setPresion(jugador.getPresion() - 0.01);
                        }
                    }

                }
                if(arboles[i]->getHP() <= 0){
                    arboles[i]->setSpriteDEADPosition(arboles[i]->getSprite().getPosition().x,arboles[i]->getSprite().getPosition().y);
                    arboles[i]->setDead(true);
                    jugador.setScore(jugador.getScore() + arboles[i]->getPoints());
                }
            }

        }
        for(long long unsigned int i = 0; i < piedras.size(); i++)
        {
        //    std::cout << jugador.getKill()<<std::endl;
         //   std::cout << jugador.getPresion()<<std::endl;
            ///CHECK IF PLAYER HITS OBSTACLES
            if(!piedras[i]->getDead())
            {
                if(piedras[i]->getBounds().intersects(jugador.getBounds())){
                    if(jugador.getKill())
                    {
                        piedras[i]->setHP(piedras[i]->getHP() - damage);
                        if(piedras[i]->getHP() <= 0)
                            piedrasHarvested += 1;
                        if(jugador.getPresion() > jugador.getPresionMAX() / 4){
                            jugador.setPresion(jugador.getPresion() - 0.01);
                        }
                    }else{
                        piedras[i]->setHP(piedras[i]->getHP() - damage2);
                        if(jugador.getPresion() > jugador.getPresionMAX() / 4){
                            jugador.setPresion(jugador.getPresion() - 0.05);
                        }
                    }
                }
                if(piedras[i]->getHP() <= 0){
                    piedras[i]->setSpriteDEADPosition(piedras[i]->getSprite().getPosition().x,piedras[i]->getSprite().getPosition().y);
                    piedras[i]->setDead(true);
                    jugador.setScore(jugador.getScore() + piedras[i]->getPoints());
                }
            }

        }
}

///UPDATE PLAYER
void GameState::buyUpgrades(){
    int t = upgradesPrice[btnMejoraPresionado][jugador.getMejoras(btnMejoraPresionado)];
    if(jugador.getMejoras(btnMejoraPresionado) < 2){
        if(jugador.getMoney() >= t){
                std::cout<<"cuanto tengo? "<<jugador.getMoney()<<"\n";
                jugador.setMoney(jugador.getMoney() - t);
                jugador.setMejoras(jugador.getMejoras(btnMejoraPresionado) + 1, btnMejoraPresionado);
                std::cout<<"cuanto me quedo? "<<jugador.getMoney()<<"\n";
                ///Igualamos el total a cero asi se reinicia la cantidad de plata que tenemos en el GUI
        }else{
            std::string s = "Ooops... You don't\nhave enough money";
            textUpgrades.setString(s);
            btnMejoraPresionado = -1;
        }
    }
}

void GameState::updatePlayer(float dt){
    jugador.update(window,dt);
    checkBoundsPlayer();
    if(arbolesHarvested >= 10){
        arbolesHarvested -= 10;
        jugador.setCarbon(jugador.getCarbon() + 50);
    }
}
void GameState::updateButtons(bool MBreleased){

    playAgain.update(mousePosView);
    if(playAgain.isPressed(MBreleased,mousePosView))
    {
        reset();
    }

    for(int i = 0; i < 5;i++){
        botonMejoras[i].update(mousePosView);
        if(botonMejoras[i].isPressed(MBreleased,mousePosView)){
            btnMejoraPresionado = i;
        }
    }
    if(btnMejoraPresionado >= 0)
        updateUpgradedButtons(btnMejoraPresionado);
    BuyUpgrade.update(mousePosView);
    if(BuyUpgrade.isPressed(MBreleased,mousePosView))
    {
        buyUpgrades();
    }

    returnMenu.update(mousePosView);
}

void GameState::updateUpgradedButtons(int btn){
    ///TEXT
    std::string s = "";
    switch(btn){
    case 0:
        if(jugador.getMejoras(btnMejoraPresionado) == 0){
            s = "+10% reduction of\n pressure\n";
            s += "+10% harvested\n materials\n";
            s += "-15% reduction of\n  velocity\n";
            s += std::to_string(upgradesPrice[0][0]);
            s+= "$";
        }else if(jugador.getMejoras(btnMejoraPresionado) == 1){
            s = "+25% reduction of\n pressure\n";
            s+= "+25% harvested\n materials\n";
            s += "-45% reduction of\n  velocity\n";
            s += std::to_string(upgradesPrice[0][1]);
            s+= "$";
        }
        textUpgrades.setString(s);
        break;
    case 1:
        if(jugador.getMejoras(btnMejoraPresionado) == 0){
            s = "+10% velocity\n";
            s+= "+10% retention  of\n temperatures\n";
            s += "+10% reduction of \n pressure\n";
            s += std::to_string(upgradesPrice[1][0]);
            s+= "$";
        }else if(jugador.getMejoras(btnMejoraPresionado) == 1){
            s = "+30% velocity\n";
            s+= "+20% retention of\n temperatures\n";
            s += "+25% reduction of\n pressure\n";
            s += std::to_string(upgradesPrice[1][1]);
            s+= "$";
        }
        textUpgrades.setString(s);
        break;
    case 2:
        if(jugador.getMejoras(btnMejoraPresionado) == 0){
            s = "+35% duration of\n level\n";
            s += std::to_string(upgradesPrice[2][0]);
        }else if(jugador.getMejoras(btnMejoraPresionado) == 1){
            s = "+50% duration of\n level\n";
            s += std::to_string(upgradesPrice[2][1]);
            s+= "$";
        }
        textUpgrades.setString(s);
        break;
    case 3:
        if(jugador.getMejoras(btnMejoraPresionado) == 0){
            s = "+20% velocity\n";
            s += std::to_string(upgradesPrice[3][0]);
            s+= "$";

        }else if(jugador.getMejoras(btnMejoraPresionado) == 1){
            s = "+50% velocity\n";
            s += std::to_string(upgradesPrice[3][1]);
            s+= "$";
        }
        textUpgrades.setString(s);
        break;
    case 4:
        if(jugador.getMejoras(btnMejoraPresionado) == 0){
            s = "+3% velocity per 10%\n";
            s+= "of missing carbon\n";
            s += "+10% velocity\n";
            s += std::to_string(upgradesPrice[4][0]);
            s+= "$";
        }else if(jugador.getMejoras(btnMejoraPresionado) == 1){
            s = "+10% velocity per\n";
            s+= "10% of missing\n carbon\n";
            s += "+15% velocity\n";
            s += std::to_string(upgradesPrice[4][1]);
            s+= "$";
        }
        textUpgrades.setString(s);
        break;
    default:

        break;
    }


}
///UPDATE HUD
void GameState::updateHUD(float dt){
    ///NEEDLE METER
    if(jugador.getCarbon() > 0){
        if(jugador.getPresion() > jugador.getPresionCheck()){
            if(needleMeter.getRotation() < 120 || needleMeter.getRotation() >= 265)
                needleMeter.rotate(jugador.getPresion()* 60 * dt);
        }else if(jugador.getPresion() < jugador.getPresionCheck()){
            if(needleMeter.getRotation() > 270 || needleMeter.getRotation() <= 125)
                needleMeter.rotate(-jugador.getPresion()* 60  * dt);
        }
        jugador.setPresionCheck(jugador.getPresion());

    }
    ///TEXT
    distance += std::ceil(jugador.getPresion());
    std::string dist = "Distance: ";
    dist += std::to_string(distance);
    dist += "m";
    textDistance.setString(dist);

    ///AUDIO
    arcadeMusic.update();
}
void GameState::updatePauseMenu(){
    arcadeMusic.endAudio();

    ///TEXT
    textDistance.setCharacterSize(26);
    std::string s = "Distance   ";
    s += std::to_string(distance);
    s += "m";
    textDistance.setString(s);
    textDistance.setPosition(pauseSprite.getPosition().x - textDistance.getGlobalBounds().width / 2,pauseSprite.getPosition().y - textDistance.getGlobalBounds().height * 6);

    s = "Trees        ";
    s += std::to_string(arbolesHarvested);
    textArbolesHarvested.setString(s);
    textArbolesHarvested.setPosition(pauseSprite.getPosition().x - textDistance.getGlobalBounds().width / 2,pauseSprite.getPosition().y - textDistance.getGlobalBounds().height * 4);

    s = "Rocks       ";
    s += std::to_string(piedrasHarvested);
    textPiedrasHarvested.setString(s);
    textPiedrasHarvested.setPosition(pauseSprite.getPosition().x - textDistance.getGlobalBounds().width / 2,pauseSprite.getPosition().y - textDistance.getGlobalBounds().height * 2);
    if(!flagUpgradeText){
        total =  jugador.getScore() + distance;
        s = "Subtotal    ";
        textSubtotal.setPosition(pauseSprite.getPosition().x - textDistance.getGlobalBounds().width / 2,pauseSprite.getPosition().y );
        s += std::to_string(total);
        s += "$";
        textSubtotal.setString(s);
        flagUpgradeText = true;
    }else if(total == jugador.getScore() + distance){
        s = "Money       ";
        s += std::to_string(jugador.getMoney());
        s += "$";
        textPlayerMoney.setString(s);
        textPlayerMoney.setPosition(pauseSprite.getPosition().x - textDistance.getGlobalBounds().width / 2,pauseSprite.getPosition().y + textDistance.getGlobalBounds().height * 2);
        total += jugador.getMoney();
    }else if(total == jugador.getMoney() + jugador.getScore() + distance ){
        s = "                " ;
        s += std::to_string(total);
        s += "$";
        textTotal.setString(s);
        textTotal.setPosition(pauseSprite.getPosition().x - textDistance.getGlobalBounds().width / 2,pauseSprite.getPosition().y + textDistance.getGlobalBounds().height * 6);
        jugador.setMoney(total);
    }
    ///UPGRADES

    ///UPDATE UPGRADES PAUSE MENU HUD
    updateUpgradeTextures();
}
void GameState::initUpgradesTextures(){
    ///TEXTURES

    ///ATRAPA VACAS

    ///ATRAPA VACAS 1
    mTextures["ATRAPA_VACAS1"] = new sf::Texture();
    mTextures["ATRAPA_VACAS1"]->loadFromFile("Textures/Extras/extrasMini/atrapa_vacas_mejora_0.png");

    ///ATRAPA VACAS 2
    mTextures["ATRAPA_VACAS2"] = new sf::Texture();
    mTextures["ATRAPA_VACAS2"]->loadFromFile("Textures/Extras/extrasMini/atrapa_vacas_mejora_1.png");

    ///ATRAPA VACAS 3
    mTextures["ATRAPA_VACAS3"] = new sf::Texture();
    mTextures["ATRAPA_VACAS3"]->loadFromFile("Textures/Extras/extrasMini/atrapa_vacas_mejora_2.png");

    ///CARBONERAS

    ///CARBONERA 1
    mTextures["CARBONERA1"] = new sf::Texture();
    mTextures["CARBONERA1"]->loadFromFile("Textures/Extras/extrasMini/carbonera_mejora_0.png");

    ///CARBONERA 2
    mTextures["CARBONERA2"] = new sf::Texture();
    mTextures["CARBONERA2"]->loadFromFile("Textures/Extras/extrasMini/carbonera_mejora_1.png");

    ///CARBONERA 3
    mTextures["CARBONERA3"] = new sf::Texture();
    mTextures["CARBONERA3"]->loadFromFile("Textures/Extras/extrasMini/carbonera_mejora_2.png");


    ///LOCOMOTORAS

    ///LOCOMOTORA 1
    mTextures["LOCOMOTORA1"] = new sf::Texture();
    mTextures["LOCOMOTORA1"]->loadFromFile("Textures/Extras/extrasMini/locomotoa_mejora_0.png");

    ///LOCOMOTORA 2
    mTextures["LOCOMOTORA2"] = new sf::Texture();
    mTextures["LOCOMOTORA2"]->loadFromFile("Textures/Extras/extrasMini/locomotoa_mejora_1.png");

    ///LOCOMOTORA 3
    mTextures["LOCOMOTORA3"] = new sf::Texture();
    mTextures["LOCOMOTORA3"]->loadFromFile("Textures/Extras/extrasMini/locomotoa_mejora_2.png");

    ///ORUGA LOCOMOTORAS

    ///ORUGA LOCOMOTORA 1
    mTextures["ORUGA_LOCOMOTORA1"] = new sf::Texture();
    mTextures["ORUGA_LOCOMOTORA1"]->loadFromFile("Textures/Extras/extrasMini/orugas_locomotora_mejora_0.png");

    ///ORUGA LOCOMOTORA 2
    mTextures["ORUGA_LOCOMOTORA2"] = new sf::Texture();
    mTextures["ORUGA_LOCOMOTORA2"]->loadFromFile("Textures/Extras/extrasMini/orugas_locomotora_mejora_1.png");

    ///ORUGA LOCOMOTORA 3
    mTextures["ORUGA_LOCOMOTORA3"] = new sf::Texture();
    mTextures["ORUGA_LOCOMOTORA3"]->loadFromFile("Textures/Extras/extrasMini/orugas_locomotora_mejora_2.png");
    ///ORUGA CARBONERAS

    ///ORUGA CARBONERA 1
    mTextures["ORUGA_CARBONERA1"] = new sf::Texture();
    mTextures["ORUGA_CARBONERA1"]->loadFromFile("Textures/Extras/extrasMini/orugas_carbonera_mejora_0.png");

    ///ORUGA CARBONERA 2
    mTextures["ORUGA_CARBONERA2"] = new sf::Texture();
    mTextures["ORUGA_CARBONERA2"]->loadFromFile("Textures/Extras/extrasMini/orugas_carbonera_mejora_1.png");

    ///ORUGA CARBONERA 3
    mTextures["ORUGA_CARBONERA3"] = new sf::Texture();
    mTextures["ORUGA_CARBONERA3"]->loadFromFile("Textures/Extras/extrasMini/orugas_carbonera_mejora_2.png");
}
void GameState::updateUpgradeTextures(){
        for(int j = 0; j < 5; j++){
            switch(j){
            case 0:
                if(jugador.getMejoras(j) == 0){
                    atrapaVacas.setTexture(*mTextures["ATRAPA_VACAS1"]);
                }else if(jugador.getMejoras(j) == 1){
                    atrapaVacas.setTexture(*mTextures["ATRAPA_VACAS2"]);
                }else if(jugador.getMejoras(j) == 2){
                    atrapaVacas.setTexture(*mTextures["ATRAPA_VACAS3"]);
                }
                break;
            case 1:
                if(jugador.getMejoras(j) == 0){
                    locomotora.setTexture(*mTextures["LOCOMOTORA1"]);
                }else if(jugador.getMejoras(j) == 1){
                    locomotora.setTexture(*mTextures["LOCOMOTORA2"]);
                }else if(jugador.getMejoras(j) == 2){
                    locomotora.setTexture(*mTextures["LOCOMOTORA3"]);
                }
                break;
            case 2:
                if(jugador.getMejoras(j) == 0){
                    carbonera.setTexture(*mTextures["CARBONERA1"]);
                }else if(jugador.getMejoras(j) == 1){
                    carbonera.setTexture(*mTextures["CARBONERA2"]);
                }else if(jugador.getMejoras(j) == 2){
                    carbonera.setTexture(*mTextures["CARBONERA3"]);
                }
                break;
            case 3:
                if(jugador.getMejoras(j) == 0){
                    orugaLocomotora.setTexture(*mTextures["ORUGA_LOCOMOTORA1"]);
                }else if(jugador.getMejoras(j) == 1){
                    orugaLocomotora.setTexture(*mTextures["ORUGA_LOCOMOTORA2"]);
                }else if(jugador.getMejoras(j) == 2){
                    orugaLocomotora.setTexture(*mTextures["ORUGA_LOCOMOTORA3"]);
                }
                break;
            case 4:
                if(jugador.getMejoras(j) == 0){
                    orugaCarbonera.setTexture(*mTextures["ORUGA_CARBONERA1"]);
                }else if(jugador.getMejoras(j) == 1){
                    orugaCarbonera.setTexture(*mTextures["ORUGA_CARBONERA2"]);
                }else if(jugador.getMejoras(j) == 2){
                    orugaCarbonera.setTexture(*mTextures["ORUGA_CARBONERA3"]);
                }
                break;
            }
        }
    }

///CHECK STATE
void GameState::checkForQuit(bool MBreleased){

     if( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            quit = true;
     }
     if(returnMenu.isPressed(MBreleased,mousePosView))
    {
        quit = true;
    }
}

void GameState::endState(){
        this->quit = true;
}

void GameState::updateInput(const float& dt, bool MBreleased){
    this->checkForQuit(MBreleased);
}
void GameState::checkBoundsEnemy(){
    if(!arboles.empty()){
        for(long long unsigned i = 0; i < arboles.size();i++){
            if(arboles[i]->getBounds().intersects(enemy.getSprite().getGlobalBounds())){
                arboles[i]->setDead(true);
            }
        }
    }

    if(!piedras.empty()){
        for(long long unsigned i = 0; i < piedras.size();i++){
            if(piedras[i]->getBounds().intersects(enemy.getSprite().getGlobalBounds())){
                piedras[i]->setDead(true);
            }
        }
    }

}

void GameState::checkBoundBullets(){
    if(enemy.checkBulletBounds(jugador.getSprite().getGlobalBounds())){
        jugador.setHP(jugador.getHP() - 10);
        std::cout<<"HP: "<<jugador.getHP()<<"\n";
    }
}
///UPDATE
void GameState::updateEnemy(sf::RenderWindow *window,float dt){
    if(distance > 1200){
        enemy.update(window,dt,jugador.getPresion() * jugador.getMovementSpeed(),jugador.getSprite().getPosition());
        checkBoundsEnemy();
        checkBoundBullets();
    }

}

void GameState::update(const float& dt,bool MBreleased, sf::Event event){
    this->timePlayed = clock.getElapsedTime();
  //  std::cout<<"Time: "<<timePlayed.asSeconds()<<"\n";
    this->updateMousePosition();
    this->updateInput(dt,MBreleased);
    if(jugador.getCarbon() > 0){
        this->backgroundLoop();
        this->updatePlayer(dt);
        this->updateEnemy(window,dt);
        this->updateObstacles();
        this->updateHUD(dt);
    }else{
        updatePauseMenu();
        if(total >= jugador.getScore() + distance)
            this->updateButtons(MBreleased);
    }
}

///RENDER
void GameState::renderUpgradedButtons(){
    if(btnMejoraPresionado >= 0)
        window->draw(botonMejoras[btnMejoraPresionado]);
}
///RENDER CHECKBOUNDS
void GameState::renderBackground(){
    window->draw(worldBackground);
    window->draw(checkboundLeft);
    window->draw(checkboundRight);
}

///RENDER HUD
void GameState::renderHUD(){
    window->draw(meterBase);
    window->draw(needleMeter);
    window->draw(textDistance);
}

///RENDER PAUSE MENU
void GameState::renderPauseMenu(){
    window->draw(pauseSprite);
    window->draw(playAgain);
    window->draw(returnMenu);
    window->draw(textArbolesHarvested);
    window->draw(textPiedrasHarvested);
    window->draw(textPlayerMoney);
    window->draw(textSubtotal);
    window->draw(textTotal);
    window->draw(atrapaVacas);
    window->draw(locomotora);
    window->draw(carbonera);
    window->draw(orugaLocomotora);
    window->draw(orugaCarbonera);
    renderUpgradedButtons();
    window->draw(textUpgrades);
    window->draw(BuyUpgrade);
}

///MAIN RENDER
void GameState::render(sf::RenderTarget *target){
    if(!target)
        target = this->window;

    ///WORLD BACKGROUND
    renderBackground();

    if(jugador.getCarbon() > 0){
    for(long long unsigned int i = 0; i < arboles.size();i++){
        target->draw(arboles[i]->getSprite());
    }

    for(long long unsigned int i = 0; i < piedras.size();i++){
        target->draw(piedras[i]->getSprite());
    }

    ///DRAW GAME OBJECTS
    target->draw(enemy);
    target->draw(enemy.getSprite());
    target->draw(jugador);

    }else{renderPauseMenu();}
    renderHUD();
}
void GameState::resetObstacles(){
        for(long long unsigned int i = 0; i < arboles.size(); i++){
            arboles.erase(arboles.begin() + i);
            i--;
        }
        for(long long unsigned int i = 0; i < piedras.size(); i++){
            piedras.erase(piedras.begin() + i);
            i--;
        }
}

void GameState::resetHUD(){
    while(needleMeter.getRotation() < 290 ){
        needleMeter.rotate(-1);
    }
    while(needleMeter.getRotation() > 290 ){
        needleMeter.rotate(-1);
    }
    distance = 0;
    arbolesHarvested = 0;
    piedrasHarvested = 0;
    total = 0;
    flagUpgradeText = false;
    textDistance.setPosition(meterBase.getPosition().x - textDistance.getGlobalBounds().width / 3.5,meterBase.getPosition().y );
}

void GameState::reset(){
    std::system("cls");
    saveFile();
    timePlayed = clock.restart();
    resetHUD();
    resetObstacles();
    initSpawnTimers();
    jugador.reset();
    enemy.reset();
    loadFile();
}
