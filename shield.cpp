#include "shield.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

Shield::Shield(float x, float y) {
    
    this->loadTexture("shield.png");
    
    this->setPos(x, y);
    type = 0;
}
