#include "aestroid.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

Texture Asteroid::tex;
bool Asteroid::texloaded = false;

Asteroid::Asteroid(float x, float y, float diffic) {
    
    if (!texloaded) {
        if (!tex.loadFromFile("aestorid.png")) { 
            cout << "Error: asteroid.png not found" << endl;
        }
        texloaded = true;
    }

    sprite.setTexture(tex);
    this->loadTexture("aestorid.png");
    this->setPos(x, y);
    speed = 150.f * diffic;
    health = 1;
    enemyType = 0;
}

void Asteroid::update(float dt) {               // movement dekh rhy, kitna move kia accoring to hte frame
                                                // and us ky bad utny coordinates sy update kr diya
    sprite.move(0.f, speed * dt);

    if (this->getPosy() > 900.f) {
        destroyed = true;
    }
}

