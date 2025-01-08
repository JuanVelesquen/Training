#include "SavefileState.h"

SavefileState::SavefileState(sf::RenderWindow* window, std::stack<State*>* states)
:State(window,states){
    initTextures();
    initBackground();
    initSavefiles();
    initGUI();
}

SavefileState::~SavefileState(){
    for(auto &i : mTextures){
        delete i.second;
    }
}

///INTIALIZE VARIABLES

void SavefileState::initTextures(){
    ///TEXTURES

    ///BACKGROUND TEXTURE
     mTextures["BACKGROUND"] = new sf::Texture();
    mTextures["BACKGROUND"]->loadFromFile("Textures/Background/training_menu.png");


    ///BUTTONS TEXTURES

    ///SAVE BUTTON BORDERS
    mTextures["SAVE_BORDERS"] = new sf::Texture();
    mTextures["SAVE_BORDERS"]->loadFromFile("Textures/CargarPartida/borde_carga_partida.png");

    ///SAVE BUTTON
    mTextures["SAVE_BUTTON"] = new sf::Texture();
    mTextures["SAVE_BUTTON"]->loadFromFile("Textures/CargarPartida/boton_partidaguardada.png");

   ///SAVE BUTTON EMPTY
    mTextures["SAVE_BUTTON_EMPTY"] = new sf::Texture();
    mTextures["SAVE_BUTTON_EMPTY"]->loadFromFile("Textures/CargarPartida/boton_partidaguardada_empty.png");

    ///SAVE BUTTON 1
    mTextures["SAVE_BUTTON1"] = new sf::Texture();
    mTextures["SAVE_BUTTON1"]->loadFromFile("Textures/CargarPartida/boton_partidaguardada_1.png");

    ///SAVE BUTTON 2
    mTextures["SAVE_BUTTON2"] = new sf::Texture();
    mTextures["SAVE_BUTTON2"]->loadFromFile("Textures/CargarPartida/boton_partidaguardada_2.png");

    ///SAVE BUTTON 3
    mTextures["SAVE_BUTTON3"] = new sf::Texture();
    mTextures["SAVE_BUTTON3"]->loadFromFile("Textures/CargarPartida/boton_partidaguardada_3.png");

    ///ATRAPA VACAS

    ///ATRAPA VACAS 1
    mTextures["ATRAPA_VACAS1"] = new sf::Texture();
    mTextures["ATRAPA_VACAS1"]->loadFromFile("Textures/Extras/atrapa_vacas_mejora_0.png");

    ///ATRAPA VACAS 2
    mTextures["ATRAPA_VACAS2"] = new sf::Texture();
    mTextures["ATRAPA_VACAS2"]->loadFromFile("Textures/Extras/atrapa_vacas_mejora_1.png");

    ///ATRAPA VACAS 3
    mTextures["ATRAPA_VACAS3"] = new sf::Texture();
    mTextures["ATRAPA_VACAS3"]->loadFromFile("Textures/Extras/atrapa_vacas_mejora_2.png");

    ///CARBONERAS

    ///CARBONERA 1
    mTextures["CARBONERA1"] = new sf::Texture();
    mTextures["CARBONERA1"]->loadFromFile("Textures/Extras/carbonera_mejora_0.png");

    ///CARBONERA 2
    mTextures["CARBONERA2"] = new sf::Texture();
    mTextures["CARBONERA2"]->loadFromFile("Textures/Extras/carbonera_mejora_1.png");

    ///CARBONERA 3
    mTextures["CARBONERA3"] = new sf::Texture();
    mTextures["CARBONERA3"]->loadFromFile("Textures/Extras/carbonera_mejora_2.png");


    ///LOCOMOTORAS

    ///LOCOMOTORA 1
    mTextures["LOCOMOTORA1"] = new sf::Texture();
    mTextures["LOCOMOTORA1"]->loadFromFile("Textures/Extras/locomotoa_mejora_0.png");

    ///LOCOMOTORA 2
    mTextures["LOCOMOTORA2"] = new sf::Texture();
    mTextures["LOCOMOTORA2"]->loadFromFile("Textures/Extras/locomotoa_mejora_1.png");

    ///LOCOMOTORA 3
    mTextures["LOCOMOTORA3"] = new sf::Texture();
    mTextures["LOCOMOTORA3"]->loadFromFile("Textures/Extras/locomotoa_mejora_2.png");

    ///ORUGA LOCOMOTORAS

    ///ORUGA LOCOMOTORA 1
    mTextures["ORUGA_LOCOMOTORA1"] = new sf::Texture();
    mTextures["ORUGA_LOCOMOTORA1"]->loadFromFile("Textures/Extras/orugas_locomotora_mejora_0.png");

    ///ORUGA LOCOMOTORA 2
    mTextures["ORUGA_LOCOMOTORA2"] = new sf::Texture();
    mTextures["ORUGA_LOCOMOTORA2"]->loadFromFile("Textures/Extras/orugas_locomotora_mejora_1.png");

    ///ORUGA LOCOMOTORA 3
    mTextures["ORUGA_LOCOMOTORA3"] = new sf::Texture();
    mTextures["ORUGA_LOCOMOTORA3"]->loadFromFile("Textures/Extras/orugas_locomotora_mejora_2.png");
    ///ORUGA CARBONERAS

    ///ORUGA CARBONERA 1
    mTextures["ORUGA_CARBONERA1"] = new sf::Texture();
    mTextures["ORUGA_CARBONERA1"]->loadFromFile("Textures/Extras/orugas_carbonera_mejora_0.png");

    ///ORUGA CARBONERA 2
    mTextures["ORUGA_CARBONERA2"] = new sf::Texture();
    mTextures["ORUGA_CARBONERA2"]->loadFromFile("Textures/Extras/orugas_carbonera_mejora_1.png");

    ///ORUGA CARBONERA 3
    mTextures["ORUGA_CARBONERA3"] = new sf::Texture();
    mTextures["ORUGA_CARBONERA3"]->loadFromFile("Textures/Extras/orugas_carbonera_mejora_2.png");

    ///RELOJ
    mTextures["RELOJ"] = new sf::Texture();
    mTextures["RELOJ"]->loadFromFile("Textures/Extras/reloj.png");


}

void SavefileState::initBackground(){
    background.setTexture(*mTextures["BACKGROUND"]);
    background.setScale(window->getSize().x / background.getGlobalBounds().width,window->getSize().y / background.getGlobalBounds().height);
}

void SavefileState::initSavefiles(){
    Savefile objSave;
    ArchivoSavefile arkSave("savefile.dat");

    ///SAVE BUTTON BORDER
    saveBorder.setTexture(*mTextures["SAVE_BORDERS"]);
    saveBorder.setOrigin(saveBorder.getGlobalBounds().width / 2,saveBorder.getGlobalBounds().height / 2);
    saveBorder.setPosition(sf::Vector2f(window->getSize().x / 2 ,window->getSize().y / 1.8));

    saveSpot = arkSave.contarRegistros();
    if(saveSpot < 0)
        saveSpot = 0;
    switch(saveSpot){
    case 0:
        ///SAVE BUTTON  1
        btnSave[0].setButton(mTextures["SAVE_BUTTON"], mTextures["SAVE_BUTTON1"], sf::Vector2f(saveBorder.getPosition().x, saveBorder.getPosition().y - mTextures["SAVE_BUTTON"]->getSize().y * 1.5),1);
        ///SAVE BUTTON  2
        btnSave[1].setButton(mTextures["SAVE_BUTTON_EMPTY"], mTextures["SAVE_BUTTON_EMPTY"],sf::Vector2f(saveBorder.getPosition().x,saveBorder.getPosition().y - mTextures["SAVE_BUTTON"]->getSize().y * 0.5),1);

        ///SAVE BUTTON  3
        btnSave[2].setButton(mTextures["SAVE_BUTTON_EMPTY"], mTextures["SAVE_BUTTON_EMPTY"],sf::Vector2f(saveBorder.getPosition().x,saveBorder.getPosition().y + mTextures["SAVE_BUTTON"]->getSize().y * 0.5),1);
        break;
    case 1:
         ///SAVE BUTTON  1
         btnSave[0].setButton(mTextures["SAVE_BUTTON1"], mTextures["SAVE_BUTTON1"], sf::Vector2f(saveBorder.getPosition().x, saveBorder.getPosition().y - mTextures["SAVE_BUTTON"]->getSize().y * 1.5),1);
        ///SAVE BUTTON  2
        btnSave[1].setButton(mTextures["SAVE_BUTTON"], mTextures["SAVE_BUTTON2"],sf::Vector2f(saveBorder.getPosition().x,saveBorder.getPosition().y - mTextures["SAVE_BUTTON"]->getSize().y * 0.5),1);

        ///SAVE BUTTON  3
        btnSave[2].setButton(mTextures["SAVE_BUTTON_EMPTY"], mTextures["SAVE_BUTTON_EMPTY"],sf::Vector2f(saveBorder.getPosition().x,saveBorder.getPosition().y + mTextures["SAVE_BUTTON"]->getSize().y * 0.5),1);
        break;
    case 2:
         ///SAVE BUTTON  1
         btnSave[0].setButton(mTextures["SAVE_BUTTON1"], mTextures["SAVE_BUTTON1"], sf::Vector2f(saveBorder.getPosition().x, saveBorder.getPosition().y - mTextures["SAVE_BUTTON"]->getSize().y * 1.5),1);
        ///SAVE BUTTON  2
        btnSave[1].setButton(mTextures["SAVE_BUTTON2"], mTextures["SAVE_BUTTON2"],sf::Vector2f(saveBorder.getPosition().x,saveBorder.getPosition().y - mTextures["SAVE_BUTTON"]->getSize().y * 0.5),1);

        ///SAVE BUTTON  3
        btnSave[2].setButton(mTextures["SAVE_BUTTON"], mTextures["SAVE_BUTTON3"],sf::Vector2f(saveBorder.getPosition().x,saveBorder.getPosition().y + mTextures["SAVE_BUTTON"]->getSize().y * 0.5),1);
        break;
    case 3:
         ///SAVE BUTTON  1
         btnSave[0].setButton(mTextures["SAVE_BUTTON1"], mTextures["SAVE_BUTTON1"], sf::Vector2f(saveBorder.getPosition().x, saveBorder.getPosition().y - mTextures["SAVE_BUTTON"]->getSize().y * 1.5),1);
        ///SAVE BUTTON  2
        btnSave[1].setButton(mTextures["SAVE_BUTTON2"], mTextures["SAVE_BUTTON2"],sf::Vector2f(saveBorder.getPosition().x,saveBorder.getPosition().y - mTextures["SAVE_BUTTON"]->getSize().y * 0.5),1);

        ///SAVE BUTTON  3
        btnSave[2].setButton(mTextures["SAVE_BUTTON3"], mTextures["SAVE_BUTTON3"],sf::Vector2f(saveBorder.getPosition().x,saveBorder.getPosition().y + mTextures["SAVE_BUTTON"]->getSize().y * 0.5),1);
        break;
    default:
        std::cout<<"ERROR: NO SE PUDO LEER EL ARCHIVO SAVEFILE.DAT DE MANERA CORRECTA"<<"\n";
        exit(-5);
        break;
    }
    for (int i = 0; i < saveSpot; i++){
        objSave = arkSave.leerRegistro(i);
        for(int j = 0; j < 5; j++){
            switch(j){
            case 0:
                if(objSave.getMejoras(j) == 0){
                    atrapaVacas[i].setTexture(*mTextures["ATRAPA_VACAS1"]);
                }else if(objSave.getMejoras(j) == 1){
                    atrapaVacas[i].setTexture(*mTextures["ATRAPA_VACAS2"]);
                }else if(objSave.getMejoras(j) == 2){
                    atrapaVacas[i].setTexture(*mTextures["ATRAPA_VACAS3"]);
                }
                break;
            case 1:
                if(objSave.getMejoras(j) == 0){
                    locomotora[i].setTexture(*mTextures["LOCOMOTORA1"]);
                }else if(objSave.getMejoras(j) == 1){
                    locomotora[i].setTexture(*mTextures["LOCOMOTORA2"]);
                }else if(objSave.getMejoras(j) == 2){
                    locomotora[i].setTexture(*mTextures["LOCOMOTORA3"]);
                }
                break;
            case 2:
                if(objSave.getMejoras(j) == 0){
                    carbonera[i].setTexture(*mTextures["CARBONERA1"]);
                }else if(objSave.getMejoras(j) == 1){
                    carbonera[i].setTexture(*mTextures["CARBONERA2"]);
                }else if(objSave.getMejoras(j) == 2){
                    carbonera[i].setTexture(*mTextures["CARBONERA3"]);
                }
                break;
            case 3:
                if(objSave.getMejoras(j) == 0){
                    orugaLocomotora[i].setTexture(*mTextures["ORUGA_LOCOMOTORA1"]);
                }else if(objSave.getMejoras(j) == 1){
                    orugaLocomotora[i].setTexture(*mTextures["ORUGA_LOCOMOTORA2"]);
                }else if(objSave.getMejoras(j) == 2){
                    orugaLocomotora[i].setTexture(*mTextures["ORUGA_LOCOMOTORA3"]);
                }
                break;
            case 4:
                if(objSave.getMejoras(j) == 0){
                    orugaCarbonera[i].setTexture(*mTextures["ORUGA_CARBONERA1"]);
                }else if(objSave.getMejoras(j) == 1){
                    orugaCarbonera[i].setTexture(*mTextures["ORUGA_CARBONERA2"]);
                }else if(objSave.getMejoras(j) == 2){
                    orugaCarbonera[i].setTexture(*mTextures["ORUGA_CARBONERA3"]);
                }
                break;
            }
        }
    }
}

///INITIALIZE TEXT
void SavefileState::initGUI(){
    ArchivoSavefile arkSave("savefile.dat");
    Savefile objSave;
    font.loadFromFile("Fonts/Minecraft.ttf");
    int TAM = arkSave.contarRegistros();
    for(int i = 0; i < TAM; i++){
    ///LEER EL SAVEFILE
    objSave = arkSave.leerRegistro(i);
    ///PLAYAER NAME
    textPlayerName[i].setFont(font);
    textPlayerName[i].setCharacterSize(36);
    textPlayerName[i].setFillColor(sf::Color::Black);
    textPlayerName[i].setString(objSave.getNombre());
    textPlayerName[i].setPosition(btnSave[i].getSprite().getPosition().x + btnSave[i].getSprite().getGlobalBounds().width / 8, btnSave[i].getSprite().getPosition().y + btnSave[i].getSprite().getGlobalBounds().height / 6);

    ///TIME PLAYER PLAYED
    textTimePlayed[i].setFont(font);
    textTimePlayed[i].setCharacterSize(42);
    textTimePlayed[i].setFillColor(sf::Color::Black);
    sf::String s;
    char buffer[10];
    sf::Int32 time = objSave.getTiempoJugado().asMilliseconds();
    int hours = time / 3600000;
    time -= hours * 3600000;
    itoa(hours,buffer,10);
    s = buffer;
    s += ":";
    int minutes = time / 60000;
    time -= minutes * 60000;
    itoa(minutes,buffer,10);
    s += buffer;
    s += ":";
    int seconds = time / 1000;
    time -= seconds * 1000;
    itoa(seconds,buffer,10);
    s += buffer;
    textTimePlayed[i].setString(s);
    textTimePlayed[i].setPosition(btnSave[i].getSprite().getPosition().x + btnSave[i].getSprite().getGlobalBounds().width / 2, btnSave[i].getSprite().getPosition().y + btnSave[i].getSprite().getGlobalBounds().height / 6);
    }

    ///INTIALIZE MEJORAS DEL TREN

    for (int i = 0; i < saveSpot; i++){
        ///MEJORAS
        atrapaVacas[i].setPosition(btnSave[i].getSprite().getPosition().x +btnSave[i].getSprite().getGlobalBounds().width - atrapaVacas[i].getGlobalBounds().width * 1.2, textTimePlayed[i].getPosition().y + atrapaVacas[i].getGlobalBounds().height / 4);
        locomotora[i].setPosition(btnSave[i].getSprite().getPosition().x +btnSave[i].getSprite().getGlobalBounds().width - locomotora[i].getGlobalBounds().width * 1.2, textTimePlayed[i].getPosition().y + atrapaVacas[i].getGlobalBounds().height / 4);
        carbonera[i].setPosition(btnSave[i].getSprite().getPosition().x +btnSave[i].getSprite().getGlobalBounds().width - carbonera[i].getGlobalBounds().width * 1.2, textTimePlayed[i].getPosition().y + atrapaVacas[i].getGlobalBounds().height / 4);
        orugaLocomotora[i].setPosition(btnSave[i].getSprite().getPosition().x +btnSave[i].getSprite().getGlobalBounds().width - orugaLocomotora[i].getGlobalBounds().width * 1.2, textTimePlayed[i].getPosition().y + atrapaVacas[i].getGlobalBounds().height / 4);
        orugaCarbonera[i].setPosition(btnSave[i].getSprite().getPosition().x +btnSave[i].getSprite().getGlobalBounds().width - orugaCarbonera[i].getGlobalBounds().width * 1.2, textTimePlayed[i].getPosition().y + atrapaVacas[i].getGlobalBounds().height / 4);

        ///RELOJ
        reloj[i].setTexture(*mTextures["RELOJ"]);
        reloj[i].setPosition(textTimePlayed[i].getPosition().x - reloj[i].getGlobalBounds().width * 1.1f,textTimePlayed[i].getPosition().y + reloj[i].getGlobalBounds().height);
    }



}

///METHODS
void SavefileState::updateUpgradesSprites(){
    Savefile objSave;
    ArchivoSavefile arkSave("savefile.dat");
    int TAM = arkSave.contarRegistros();
    for (int i = 0; i < TAM; i++){
        objSave = arkSave.leerRegistro(i);
        for(int j = 0; j < 5; j++){
            switch(j){
            case 0:
                if(objSave.getMejoras(j) == 0){
                    atrapaVacas[i].setTexture(*mTextures["ATRAPA_VACAS1"]);
                }else if(objSave.getMejoras(j) == 1){
                    atrapaVacas[i].setTexture(*mTextures["ATRAPA_VACAS2"]);
                }else if(objSave.getMejoras(j) == 2){
                    atrapaVacas[i].setTexture(*mTextures["ATRAPA_VACAS3"]);
                }
                break;
            case 1:
                if(objSave.getMejoras(j) == 0){
                    locomotora[i].setTexture(*mTextures["LOCOMOTORA1"]);
                }else if(objSave.getMejoras(j) == 1){
                    locomotora[i].setTexture(*mTextures["LOCOMOTORA2"]);
                }else if(objSave.getMejoras(j) == 2){
                    locomotora[i].setTexture(*mTextures["LOCOMOTORA3"]);
                }
                break;
            case 2:
                if(objSave.getMejoras(j) == 0){
                    carbonera[i].setTexture(*mTextures["CARBONERA1"]);
                }else if(objSave.getMejoras(j) == 1){
                    carbonera[i].setTexture(*mTextures["CARBONERA2"]);
                }else if(objSave.getMejoras(j) == 2){
                    carbonera[i].setTexture(*mTextures["CARBONERA3"]);
                }
                break;
            case 3:
                if(objSave.getMejoras(j) == 0){
                    orugaLocomotora[i].setTexture(*mTextures["ORUGA_LOCOMOTORA1"]);
                }else if(objSave.getMejoras(j) == 1){
                    orugaLocomotora[i].setTexture(*mTextures["ORUGA_LOCOMOTORA2"]);
                }else if(objSave.getMejoras(j) == 2){
                    orugaLocomotora[i].setTexture(*mTextures["ORUGA_LOCOMOTORA3"]);
                }
                break;
            case 4:
                if(objSave.getMejoras(j) == 0){
                    orugaCarbonera[i].setTexture(*mTextures["ORUGA_CARBONERA1"]);
                }else if(objSave.getMejoras(j) == 1){
                    orugaCarbonera[i].setTexture(*mTextures["ORUGA_CARBONERA2"]);
                }else if(objSave.getMejoras(j) == 2){
                    orugaCarbonera[i].setTexture(*mTextures["ORUGA_CARBONERA3"]);
                }
                break;
            }
        }
    }
}
///SAVE

void SavefileState::save(){
    Savefile objSave;
    ArchivoSavefile arkSave("savefile.dat");
    arkSave.agregarRegistro(objSave);
}

/// CHECK IF WE POP THE STACK
void SavefileState::checkForQuit(bool MBreleased){
     if( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        quit = true;
}

///WE POP THE STACK
void SavefileState::endState(){
    this->quit = true;
}

///UPDATE
void SavefileState::updateGUI(){
    ArchivoSavefile arkSave("savefile.dat");
    Savefile objSave;
    int TAM = arkSave.contarRegistros();
    for(int i = 0; i < TAM; i++){
        ///LEER EL SAVEFILE
        objSave = arkSave.leerRegistro(i);

        ///TIME PLAYER PLAYED
        sf::String s;
        char buffer[10];
        sf::Int32 time = objSave.getTiempoJugado().asMilliseconds();
        int hours = time / 3600000;
        time -= hours * 3600000;
        itoa(hours,buffer,10);
        s = buffer;
        s += ":";
        int minutes = time / 60000;
        time -= minutes * 60000;
        itoa(minutes,buffer,10);
        s += buffer;
        s += ":";
        int seconds = time / 1000;
        time -= seconds * 1000;
        itoa(seconds,buffer,10);
        s += buffer;
        textTimePlayed[i].setString(s);

        textPlayerName[i].setString(objSave.getNombre());
    }
}

void SavefileState::updateButtons(bool MBreleased){
    switch(saveSpot){
        case 0:
            btnSave[0].update(mousePosView);
            if(btnSave[0].isPressed(MBreleased,mousePosView))
            {
                save();
                initSavefiles();
                initGUI();
                Configuracion objConfig;
                ArchivoConfiguracion arkConfig("configuracion.dat");
                objConfig = arkConfig.leerRegistro(0);
                objConfig.setScore(0,0);
                objConfig.setScore(0,1);
                objConfig.setScore(0,2);
                arkConfig.modificarRegistro(objConfig,0);
                states->push(new PlayerCreationState(window,states,0));
            }
            break;
        case 1:
            btnSave[0].update(mousePosView);
            if(btnSave[0].isPressed(MBreleased,mousePosView))
            {
                states->push(new GameState(window,states,0));
            }
            btnSave[1].update(mousePosView);
            if(btnSave[1].isPressed(MBreleased,mousePosView))
            {
                save();
                initSavefiles();
                initGUI();
                Configuracion objConfig;
                ArchivoConfiguracion arkConfig("configuracion.dat");
                objConfig = arkConfig.leerRegistro(0);
                objConfig.setScore(0,1);
                objConfig.setScore(0,2);
                arkConfig.modificarRegistro(objConfig,0);
                states->push(new PlayerCreationState(window,states,1));
            }
            break;
        case 2:
            btnSave[0].update(mousePosView);
            if(btnSave[0].isPressed(MBreleased,mousePosView))
            {
                states->push(new GameState(window,states,0));
            }
            btnSave[1].update(mousePosView);
            if(btnSave[1].isPressed(MBreleased,mousePosView))
            {
                states->push(new GameState(window,states,1));
            }
            btnSave[2].update(mousePosView);
            if(btnSave[2].isPressed(MBreleased,mousePosView))
            {
                save();
                initSavefiles();
                initGUI();
                Configuracion objConfig;
                ArchivoConfiguracion arkConfig("configuracion.dat");
                objConfig = arkConfig.leerRegistro(0);
                objConfig.setScore(0,2);
                arkConfig.modificarRegistro(objConfig,0);
                states->push(new PlayerCreationState(window,states,2));
            }
            break;
        case 3:
            btnSave[0].update(mousePosView);
            if(btnSave[0].isPressed(MBreleased,mousePosView))
            {
                states->push(new GameState(window,states,0));
            }
            btnSave[1].update(mousePosView);
            if(btnSave[1].isPressed(MBreleased,mousePosView))
            {
                states->push(new GameState(window,states,1));
            }
            btnSave[2].update(mousePosView);
            if(btnSave[2].isPressed(MBreleased,mousePosView))
            {
                states->push(new GameState(window,states,2));
            }
            break;
    }
    /*btnQuit.update(mousePosView);
    if(btnQuit.isPressed())
    {
        endState();
    }*/
    updateUpgradesSprites();
}

void SavefileState::updateInput(const float& dt, bool MBreleased){
    this->checkForQuit(MBreleased);
}

void SavefileState::update(const float& dt,bool MBreleased,sf::Event event){
    this->updateMousePosition();
    this->updateInput(dt,MBreleased);
    this->updateButtons(MBreleased);
    this->updateGUI();
}


///RENDER
///RENDER TEXT
void SavefileState::renderGUI(){
    for (int i = 0;i < saveSpot; i++){
        window->draw(textPlayerName[i]);
        window->draw(textTimePlayed[i]);
        window->draw(atrapaVacas[i]);
        window->draw(locomotora[i]);
        window->draw(carbonera[i]);
        window->draw(orugaLocomotora[i]);
        window->draw(orugaCarbonera[i]);
        window->draw(reloj[i]);
    }
}
///RENDER BUTTONS
void SavefileState::renderButtons(){
    window->draw(saveBorder);
    window->draw(btnSave[0]);
    window->draw(btnSave[1]);
    window->draw(btnSave[2]);
}

///RENDER MAIN
void SavefileState::render(sf::RenderTarget *target){
    if(!target)
        target = this->window;

    target->draw(background);
    renderButtons();
    renderGUI();
}
