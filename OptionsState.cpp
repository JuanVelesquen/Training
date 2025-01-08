#include "OptionsState.h"

///Constructor / Destructor
Options::Options(sf::RenderWindow* window, std::stack<State*>* states)
:State(window,states){
    initBackground();
    initGUI();
}
Options::~Options(){
    save();
}

///Methods
void Options::save(){
    Configuracion objConfig;
    ArchivoConfiguracion arkConfig("configuracion.dat");
    objConfig = arkConfig.leerRegistro(0);
    int TAM = arkConfig.contarRegistros();
    if(TAM < 0){
        objConfig.setConfigMusica(volumenMusica);
        objConfig.setConfigSFX(volumenSFX);
        arkConfig.agregarRegistro(objConfig);
        return;
    }
    objConfig.setConfigMusica(volumenMusica);
    objConfig.setConfigSFX(volumenSFX);
    arkConfig.modificarRegistro(objConfig,0);
}
void Options::initBackground(){
    mTexture.loadFromFile("Textures/Background/training_menu.png");
    mBackground.setTexture(mTexture);
    mBackground.setScale(window->getSize().x / mBackground.getGlobalBounds().width,window->getSize().y / mBackground.getGlobalBounds().height);
}

void Options::initGUI(){
    Configuracion objConfig;
    ArchivoConfiguracion arkConfig("configuracion.dat");
    objConfig = arkConfig.leerRegistro(0);
    ///INIT SLIDERS
    mTextureVolumeBar.loadFromFile("Textures/botones/sliderbars.png");
    mTextureVolumeSlider.loadFromFile("Textures/botones/slider.png");
    musicVolume.setTexture(mTextureVolumeBar);
    musicVolume.setOrigin(musicVolume.getGlobalBounds().width / 2,musicVolume.getGlobalBounds().height / 2);
    musicVolume.setPosition(window->getSize().x / 2 ,window->getSize().y / 2);
    sfxVolume.setTexture(mTextureVolumeBar);
    sfxVolume.setOrigin(sfxVolume.getGlobalBounds().width / 2,sfxVolume.getGlobalBounds().height / 2);
    sfxVolume.setPosition(window->getSize().x / 2 ,window->getSize().y / 1.5);
    slider[0].setTexture(mTextureVolumeSlider);
    slider[0].setOrigin(slider[0].getGlobalBounds().width / 2,slider[0].getGlobalBounds().height / 2);
    slider[0].setPosition((objConfig.getConfigMusica() * (694 - 120) / 100 + 120) + 1,musicVolume.getPosition().y);
    slider[1].setTexture(mTextureVolumeSlider);
    slider[1].setOrigin(slider[1].getGlobalBounds().width / 2,slider[1].getGlobalBounds().height / 2);
    slider[1].setPosition((objConfig.getConfigSFX() * (694 - 120) / 100 + 120) + 1,sfxVolume.getPosition().y);

    ///INIT TEXT
    font.loadFromFile("Fonts/Minecraft.ttf");
    ///TITULO
    titulo.setFont(font);
    titulo.setCharacterSize(42);
    titulo.setColor(sf::Color::Black);
    titulo.setString("CONFIGURACION");
    titulo.setOrigin(titulo.getGlobalBounds().width / 2,titulo.getGlobalBounds().height / 2);
    titulo.setPosition(musicVolume.getPosition().x,musicVolume.getPosition().y * 0.65);

    /// VOLUMEN DE LA MUSICA
    musicaSubtitulo.setFont(font);
    musicaSubtitulo.setCharacterSize(24);
    musicaSubtitulo.setColor(sf::Color::Black);
    musicaSubtitulo.setString("MUSICA");
    musicaSubtitulo.setPosition(musicVolume.getPosition().x - musicVolume.getGlobalBounds().width / 2, musicVolume.getPosition().y * 0.8);

    ///PORCENTAJE DE LA MUSICA;
    porcentajeMusica.setFont(font);
    porcentajeMusica.setCharacterSize(24);
    porcentajeMusica.setColor(sf::Color::Black);
    porcentajeMusica.setString("50%");
    porcentajeMusica.setPosition(musicVolume.getPosition().x + musicVolume.getGlobalBounds().width / 1.9, musicVolume.getPosition().y - porcentajeMusica.getGlobalBounds().height);

    ///SUBTITULO SFX
    sfkSubtitulo.setFont(font);
    sfkSubtitulo.setCharacterSize(24);
    sfkSubtitulo.setColor(sf::Color::Black);
    sfkSubtitulo.setString("SFX");
    sfkSubtitulo.setPosition(sfxVolume.getPosition().x - sfxVolume.getGlobalBounds().width / 2, sfxVolume.getPosition().y * 0.85);
    ///PROCENTAJE DE SFX
    porcentajeSFX.setFont(font);
    porcentajeSFX.setCharacterSize(24);
    porcentajeSFX.setColor(sf::Color::Black);
    porcentajeSFX.setString("50%");
    porcentajeSFX.setPosition(sfxVolume.getPosition().x + sfxVolume.getGlobalBounds().width / 1.9, sfxVolume.getPosition().y - porcentajeSFX.getGlobalBounds().height );

}

void Options::checkForQuit(bool MBreleased){
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        quit = true;
    }
}

void Options::endState(){
        this->quit = true;
}

void Options::updateGUI(){
    volumenMusica = (slider[0].getPosition().x - 120) * 100 / (694 - 120.f);
    volumenSFX = (slider[1].getPosition().x - 120) * 100 / (694 - 120.f);
    std::string s = std::to_string(volumenMusica);
    s += "%";
    porcentajeMusica.setString(s);
     s = std::to_string(volumenSFX);
    s += "%";
    porcentajeSFX.setString(s);

}
void Options::updateSliders(sf::Vector2f mousePos){

    if(musicVolume.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            slider[0].setPosition(mousePos.x,slider[0].getPosition().y);
    }

    if(sfxVolume.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            slider[1].setPosition(mousePos.x,slider[1].getPosition().y);
    }
}
void Options::updateInput(const float& dt,bool MBreleased){
    this->checkForQuit(MBreleased);
}

void Options::update(const float& dt,bool MBreleased, sf::Event event){
    this->updateMousePosition();
    this->updateInput(dt,MBreleased);
    this->updateSliders(mousePosView);
    this->updateGUI();
}

void Options::render(sf::RenderTarget *target){
    if(!target)
        target = this->window;

    target->draw(mBackground);
    target->draw(musicVolume);
    target->draw(sfxVolume);
    target->draw(slider[0]);
    target->draw(slider[1]);
    target->draw(titulo);
    target->draw(musicaSubtitulo);
    target->draw(sfkSubtitulo);
    target->draw(porcentajeMusica);
    target->draw(porcentajeSFX);
}
