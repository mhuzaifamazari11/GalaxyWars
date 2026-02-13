#include "doublefire.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

DoubleFire::DoubleFire(float x, float y) {
    
    this->loadTexture("doublebullet.png");
    
    this->setPos(x, y);
    type = 2;
}

