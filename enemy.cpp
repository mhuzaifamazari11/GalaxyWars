#include "enemy.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;
Enemy::Enemy() {                    // ths class is Parent
    destroyed = false;
    health = 1;
    speed = 100.f;
    enemyType = 0;
}

Enemy::~Enemy() {
}

bool Enemy::checkDestroyed() {
    return destroyed;
}

void Enemy::setDestroyed(bool state) {
    destroyed = state;
}

void Enemy::takeDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        destroyed = true;
    }
}

int Enemy::getType() {
    return enemyType;
}