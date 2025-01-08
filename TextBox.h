#ifndef TEXTBOX_H_INCLUDED
#define TEXTBOX_H_INCLUDED
 #include <iostream>
 #include <sstream>
 #include <SFML/Graphics.hpp>
 #include <SFML/Window.hpp>
 #include <SFML/System.hpp>
 #include <SFML/Audio.hpp>

 #define DELETE_KEY 8
 #define ENTER_KEY 13
 #define ESCAPE_KEY 27

class TextBox:public sf::Drawable{
private:
    sf::Font font;
    sf::Text textBox;
    std::ostringstream text;
    bool isSelected;
    bool hasLimit;
    int limit;
public:
    ///CONSTRUCTOR
    TextBox(int size,sf::Color color,bool selected);

    void setPosition(float x,float y);
    void setLimit(bool hasLimit,int limit);
    void setSelected(bool selected);

    std::string getText();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void typedOn(sf::Event input);
private:
    void inputLogic(int charTyped);
    void deleteLastChar();
};

#endif // TEXTBOX_H_INCLUDED
