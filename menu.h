#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

using namespace sf;
using namespace std;

class Menu {
private:
    int selectedItemIndex;
    Font font;


    static const int items = 5;
    Text menuItems[items];
    int itemCount;

    Text titleText;

public:
    Menu(float width, float height);
    ~Menu();

    void draw(RenderWindow& window);
    void moveup();
    void movedown();
    int GetPressedItem();

  
    void setMenuState(int state);
};
