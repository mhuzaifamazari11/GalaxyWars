#include "missile.h"

#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

Texture MissileEnemy::tex;
bool MissileEnemy::texloaded = false;

MissileEnemy::MissileEnemy(float x, float y, float difficulty) {            // parameter ewal cons
    
    if (!texloaded) {
        if (!tex.loadFromFile("missileenemy.png")) {
            cout << "Error: missileenemy.png not found" << endl;
        }
        texloaded = true;
    }
    sprite.setTexture(tex);

    this->loadTexture("missileenemy.png");
    this->setPos(x, y);

    speed = 50.f * difficulty;              // load, speed and health , type bhi defines
                                            // 
    health = 5;
    enemyType = 2;

    shootTimer = 0.f;
    direction = 1;
}

void MissileEnemy::update(float dt) {               // timer p depend krta h, and update krta h
    
    shootTimer += dt;                           // updating the deaminds

    sprite.move((speed * direction) * dt, 0.f);

    if (this->getPosx() <= 0) {
        direction = 1;
    }

    if (this->getPosx() >= 1350) {
        direction = -1;
    }

    sprite.move(0.f, 50.f * dt);

    if (this->getPosy() > 788.f) {
        destroyed = true;
    }

}

bool MissileEnemy::shoots() {
    if (shootTimer > 3.0f) {
        shootTimer = 0.f;
        return true;
    }
    return false;
}
