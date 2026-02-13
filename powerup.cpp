#include "powerup.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

PowerUp::PowerUp() {
    
    speed = 100.f;
    type = -1;
    resourceValue = 10;
}

PowerUp::~PowerUp() {

}

void PowerUp::update(float dt) {
    
    sprite.move(0.f, speed * dt);
}

int PowerUp::getType() {
    return type;
}

int operator+(PowerUp& p1,  PowerUp& p2) {
    return p1.resourceValue + p2.resourceValue;
}
