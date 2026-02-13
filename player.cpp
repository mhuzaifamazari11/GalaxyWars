#include "player.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;


Player::Player() {
    this->loadTexture("player.png");
    this->setPos(750.f, 850.f);
    speed = 300.f;
    velocityx = 0.f;
    velocityy = 0.f;
    
    health = 100;
    score = 0; 
    healthget = 20;

    shielded = false; 
    shieldtime = 0.f;

    doublescore = false; 
    doublescoretime = 0.f;
    
    doublefire = false; 
    doublefiretime = 0.f;
}

void Player::movePlayer() {                     // up & down by keys pressing by me 
   
    velocityx = 0.f; velocityy = 0.f;

    if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
        velocityy = -speed;
    }

    if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
        velocityy = +speed;
    }

    if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
        velocityx = +speed;
    }

    if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
        velocityx = -speed;
    }

}

void Player::update(float dt) {                     // kia update hoa, mavemt kidhr gi
    movePlayer();
    
    sprite.move(velocityx * dt, velocityy * dt);

    float pos_x = sprite.getPosition().x;
    float pos_y = sprite.getPosition().y;
    FloatRect bounds = sprite.getGlobalBounds();

    if (pos_x < 0) {
        pos_x = 0;
    }

    if (pos_x + bounds.width > 1400) {
        pos_x = 1400 - bounds.width;
    }

    if (pos_y < 0) {
        pos_y = 0;
    }

    if (pos_y + bounds.height > 900) {
        pos_y = 900 - bounds.height;
    }

    sprite.setPosition(pos_x, pos_y);


    if (shielded) {                     // kia rewards dyny hn 
        shieldtime -= dt;
        if (shieldtime <= 0) {
            shielded = false;
        }
    }

    if (doublescore) {
        doublescoretime -= dt;
        if (doublescoretime <= 0) {
            doublescore = false;
        }
    }

    if (doublefire) {
        doublefiretime -= dt;
        if (doublefiretime <= 0) {
            doublefire = false;
        }
    }

}

void Player::takeDamage(int amount) {                           /// kitna damage hoga decide hoga
    
    if (shielded) {
        return;
    }

    if (damageClock.getElapsedTime().asSeconds() > 0.45f) {
        health -= amount;
        if (health < 0) {
            health = 0;
        }

        damageClock.restart();
    }
}

void Player::addScore(int amount) {
    if (doublescore) {
        amount *= 2;
    }
    score += amount;
}


void Player::shieldok() { 
    shielded = true; 
    shieldtime = 10.0f; 
}

void Player::doublescoreok() { 
    doublescore = true;
    doublescoretime = 10.0f; 
}

void Player::doublefireok() { 
    doublefire = true; 
    doublefiretime = 10.0f; 
}

bool Player::has_doublefire() {
    return doublefire; 
}


bool Player::isDead() {
    return health == 0; 
}

int Player::heal_get() {
    return health; 
}

void Player::heal() {
    int needed = 100 - health;
    health += needed; 
}

int Player::getScore() {
    return score; 
}