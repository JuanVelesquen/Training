#include "TextBox.h"

TextBox::TextBox(int size,sf::Color color,bool selected){
    font.loadFromFile("Fonts/Minecraft.ttf");
    textBox.setFont(font);
    textBox.setCharacterSize(size);
    textBox.setColor(color);
    isSelected = selected;
    hasLimit = false;
    if(isSelected){
        textBox.setString("_");
    }else{
        textBox.setString("");
    }
}

void TextBox::inputLogic(int charTyped){
    if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY){
        text<< static_cast<char>(charTyped);
    }else if(charTyped == DELETE_KEY){
        if(text.str().length() > 0){
            deleteLastChar();
        }
    }
    textBox.setString(text.str() + "_");
}


void TextBox::deleteLastChar(){
    std::string t = text.str();
    std::string newT = "";
    for (int i = 0; i < t.length() - 1;i++){
        newT += t[i];
    }
    text.str("");
    text<<newT;

    textBox.setString(text.str());
}

void TextBox::setPosition(float x,float y){
    textBox.setPosition(x,y);
}

void TextBox::setLimit(bool hasLimit,int limit){
    this->hasLimit = hasLimit;
    this->limit = limit;
}

void TextBox::setSelected(bool selected){
    this->isSelected = selected;
    if(!isSelected){
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length();i++){
            newT += t[i];
        }
        textBox.setString(newT);
    }
}

std::string TextBox::getText(){
    return text.str();
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    target.draw(textBox,states);
}

void TextBox::typedOn(sf::Event input){
    if(isSelected){
        int charTyped = input.text.unicode;
        if(charTyped < 128){
            if(hasLimit){
                if(text.str().length() <= limit){
                    inputLogic(charTyped);
                } else if(text.str().length() >= limit && charTyped == DELETE_KEY){
                    deleteLastChar();
                }
            }
        }
    }
}
