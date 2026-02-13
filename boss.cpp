#include "boss.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

// =========================================================BOSS ===============================

BossEnemy::BossEnemy(float x, float y) {

    this->loadTexture("boss.png");
    this->setPos(x, y);

    speed = 80.f;
    health = 50;  
    enemyType = 3;

    shootTimer = 0.f;
    direction = 1; 
}

void BossEnemy::update(float dt) {
    shootTimer += dt;

 
    sprite.move((speed * direction) * dt, 0.f);             // sirf above rogth left ho sky  =nboss


    if (this->getPosx() <= 0) {
        direction = 1;
    }

    if (this->getPosx() >= 1200) {
        direction = -1;
    }

}

bool BossEnemy::shoots() {

    if (shootTimer > 0.5f) {
        shootTimer = 0.f;
        return true;
    }
    return false;
}


BossLevel::BossLevel() {

    spawnInterval = 5.0f;                   // kitny time bad appear
    bossSpawned = false;
}

string BossLevel::bg() {
    return "bgboss.png"; 
}

Enemy* BossLevel::comingenemy(int width) {               // sifr boss ae
  
    if (!bossSpawned) {
        bossSpawned = true;
                            // for mid m rhny ky liye
        return new BossEnemy(width / 2.0f - 100.f, 50.f);
    }
    return nullptr;
}

