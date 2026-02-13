#include "shootingenemy.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

Texture ShootingEnemy::tex;
bool ShootingEnemy::texloaded = false;

ShootingEnemy::ShootingEnemy(float x, float y, float diffi) {
    if (!texloaded) {
        if (!tex.loadFromFile("shootingenemy.png")) {
            cout << "Error: shootingenemy.png not found" << endl;
        }
        texloaded = true;
    }
    sprite.setTexture(tex);

    
    this->loadTexture("shootingenemy.png");
    this->setPos(x, y);

    speed = 80.f * diffi;
    health = 3;
    enemyType = 1;

    movetime = 0.f;
    shoottime = 0.f;
    direction = 1;
}

void ShootingEnemy::update(float dt) {                      // phir wohi updaete krn gy
    shoottime += dt;
    sprite.move(0.f, (speed * 0.5f) * dt);

    movetime += dt;
    if (movetime > 1.0f) {
        direction *= -1;
        movetime = 0.f;
    }
    sprite.move((speed * direction) * dt, 0.f);

    if (this->getPosy() > 900.f) {
        destroyed = true;
    }
}

bool ShootingEnemy::shoots() {                      // kityn time m shoot hoga
    if (shoottime > 2.0f) {
        shoottime = 0.f;
        return true;
    }
    return false;
}

