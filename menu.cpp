#include "menu.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("COOPBL.ttf")) {
        
    }

    itemCount = 0;
    selectedItemIndex = 0;
    setMenuState(0);
}

Menu::~Menu() {
}

void Menu::setMenuState(int state) {
    itemCount = 0;
    selectedItemIndex = 0;
    float centerX = 800.f;

    if (state == 0) {
        titleText.setString("GALAXY WARS");             // page -0
        titleText.setFont(font);
        titleText.setCharacterSize(50);
        titleText.setFillColor(Color::Cyan);
        titleText.setPosition(700.f, 100.f);

        menuItems[0].setFont(font); menuItems[0].setFillColor(Color::Red);
        menuItems[0].setString("Start Game"); menuItems[0].setPosition(centerX, 300.f);
        itemCount++;

        menuItems[1].setFont(font); menuItems[1].setFillColor(Color::White);
        menuItems[1].setString("High Scores"); menuItems[1].setPosition(centerX, 400.f);
        itemCount++;

        menuItems[2].setFont(font); menuItems[2].setFillColor(Color::White);
        menuItems[2].setString("Exit"); menuItems[2].setPosition(centerX, 500.f);
        itemCount++;
    }

    else if (state == 2) {                      // pause & resume h
        
        titleText.setString("PAUSED");
        titleText.setPosition(750.f, 100.f);

        menuItems[0].setFont(font); menuItems[0].setFillColor(Color::Red);
        menuItems[0].setString("Resume"); menuItems[0].setPosition(centerX, 300.f);
        itemCount++;

        menuItems[1].setFont(font); menuItems[1].setFillColor(Color::White);
        menuItems[1].setString("Restart"); menuItems[1].setPosition(centerX, 400.f);
        itemCount++;

        menuItems[2].setFont(font); menuItems[2].setFillColor(Color::White);
        menuItems[2].setString("Quit to Menu"); menuItems[2].setPosition(centerX, 500.f);
        itemCount++;
    }

    else if (state == 3) {              // game over screen , chicken dinner
        
        titleText.setString("GAME OVER");
        titleText.setPosition(720.f, 100.f);

        menuItems[0].setFont(font); menuItems[0].setFillColor(Color::Red);
        menuItems[0].setString("Save Score"); menuItems[0].setPosition(centerX, 300.f);
        itemCount++;

        menuItems[1].setFont(font); menuItems[1].setFillColor(Color::White);
        menuItems[1].setString("Main Menu"); menuItems[1].setPosition(centerX, 400.f);
        itemCount++;

        menuItems[2].setFont(font); menuItems[2].setFillColor(Color::White);
        menuItems[2].setString("Exit"); menuItems[2].setPosition(centerX, 500.f);
        itemCount++;
    }

    else if (state == 4) {                              // levle kn sa select krna h
            
        titleText.setString("SELECT LEVEL");
        titleText.setPosition(700.f, 100.f);

        menuItems[0].setFont(font); menuItems[0].setFillColor(Color::Red);
        menuItems[0].setString("Level 1 (Easy)"); menuItems[0].setPosition(centerX, 250.f);
        itemCount++;

        menuItems[1].setFont(font); menuItems[1].setFillColor(Color::White);
        menuItems[1].setString("Level 2 (Medium)"); menuItems[1].setPosition(centerX, 350.f);
        itemCount++;

        menuItems[2].setFont(font); menuItems[2].setFillColor(Color::White);
        menuItems[2].setString("Level 3 (Hard)"); menuItems[2].setPosition(centerX, 450.f);
        itemCount++;

        menuItems[3].setFont(font); menuItems[3].setFillColor(Color::White);
        menuItems[3].setString("Boss Battle"); menuItems[3].setPosition(centerX, 550.f);
        itemCount++;

        menuItems[4].setFont(font); menuItems[4].setFillColor(Color::White);
        menuItems[4].setString("Back"); menuItems[4].setPosition(centerX, 650.f);
        itemCount++;
    }

    else if (state == 7) {
        titleText.setString("MISSION ACCOMPLISHED");
        titleText.setFont(font);
        titleText.setCharacterSize(50);
        titleText.setFillColor(Color::Green); // Green for Victory
        titleText.setPosition(550.f, 100.f);

        menuItems[0].setFont(font); menuItems[0].setFillColor(Color::Red);
        menuItems[0].setString("Save Victory Score"); menuItems[0].setPosition(centerX, 300.f);
        itemCount++;

        menuItems[1].setFont(font); menuItems[1].setFillColor(Color::White);
        menuItems[1].setString("Main Menu"); menuItems[1].setPosition(centerX, 400.f);
        itemCount++;

        menuItems[2].setFont(font); menuItems[2].setFillColor(Color::White);
        menuItems[2].setString("Exit"); menuItems[2].setPosition(centerX, 500.f);
        itemCount++;
    }
}

void Menu::draw(RenderWindow& window) {                     // display draw
    
    window.draw(titleText);
    for (int i = 0; i < itemCount; i++) {
        window.draw(menuItems[i]);
    }
}

void Menu::moveup() {                               // arrrow keys sy uper, nechy
    
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(Color::Red);
    }
}

void Menu::movedown() {
    
    if (selectedItemIndex + 1 < itemCount) {
        menuItems[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(Color::Red);
    }
}

int Menu::GetPressedItem() {
    return selectedItemIndex;
}
