#include "pattern.h"

PatternEnemy::PatternEnemy(float x, float y, int id, float diffi) {
    this->loadTexture("shootingenemy.png");
    this->setPos(x, y);

    this->id = id;
    speed = 100.f * diffi;
    health = 2;
    enemyType = 4;
    shootTimer = 0.f;

    if (id % 2 == 0) {
        direction = -1;
    }
    else {
        direction = 1;
    }
}

void PatternEnemy::update(float dt) {
    shootTimer += dt;

    sprite.move(speed * direction * dt, 0.f);

    if (this->getPosx() >= 1350.f) {                // left - roght direction chk
                                                    // even-odd sy movement dekhi
        direction = -1;
        sprite.move(0.f, 50.f);
    }
    else if (this->getPosx() <= 0.f) {
        direction = 1;
        sprite.move(0.f, 50.f);
    }

    if (this->getPosy() > 900.f) {
        destroyed = true;
    }
}

bool PatternEnemy::shoots() {
    if (shootTimer > 2.0f) {                // timer reset
        shootTimer = 0.f;
        return true;
    }
    return false;
}
