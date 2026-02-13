#include "doublescore.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

DoubleScore::DoubleScore(float x, float y) {
   
    this->loadTexture("doublescore.png");
    
    this->setPos(x, y);
    type = 1;
}
