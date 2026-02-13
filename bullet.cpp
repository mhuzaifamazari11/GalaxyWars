#include "bullet.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

Texture Bullet::texbullet;
Texture Bullet::texenemybullet;
Texture Bullet::texdoublebullet;
Texture Bullet::texmissile;
bool Bullet::texturesloaded = false;


Bullet::Bullet() {
    speed = 0;
    destroy = 0;
    direction = 0;
    damage = 0;


}

Bullet::Bullet(float x, float y, bool enemybul, bool damage2) {
    damage = 1;
    
    if (enemybul) {
        this->loadTexture("enemybullet.png");
        direction = 1;                                    /// chck the bullet belings to whome & powerup m h simple
        speed = 300.f;
    }
    
    else {
    
        if (damage2) {
            this->loadTexture("doublebullet.png");
            damage = 2;
        }

        else {
            this->loadTexture("bullet.png");
        }

        direction = -1;
        speed = 400.f;

    }
    
    this->setPos(x, y);
    destroy = false;
    moving = false;
    targ = nullptr;

    if (!texturesloaded) {
        if (!texbullet.loadFromFile("bullet.png")) {
            cout << "Error: bullet.png" << endl;
        }

        if (!texenemybullet.loadFromFile("enemybullet.png")) {
            cout << "Error: enemybullet.png" << endl;
        }

        if (!texdoublebullet.loadFromFile("doublebullet.png")) {
            cout << "Error: doublebullet.png" << endl;
        }

        if (!texmissile.loadFromFile("missile.png")) {
            cout << "Error: missile.png" << endl;
        }


        texturesloaded = true;
    }
}

Bullet::~Bullet() {}

void Bullet::settermoving(Player* playerPtr) {
    
    moving = true;
    targ = playerPtr;
    this->loadTexture("missile.png");
    speed = 180.f;
}

void Bullet::update(float dt) {
    
    if (moving && targ != nullptr) {                // y disttance ko normalize kr diya taky missile alwauys pomit the player
                                                    // player and missile ka disrance adn direciton cal kia and then
                                                    // usi ko point kr diya
                                                    // aik constant speed generate kr rkn, n ky slow down ho jae when near to player
        
        float myX = this->getPosx();
        float myY = this->getPosy();
        float playerx = targ->getPosx();
        float playery = targ->getPosy();

        float diffX = playerx - myX;
        float diffY = playery - myY;
        float length = sqrt(diffX * diffX + diffY * diffY);

        if (length != 0) {
            diffX /= length; 
            diffY /= length; 
        }

        sprite.move(diffX * speed * dt, diffY * speed * dt);
    }
    else {
        sprite.move(0.f, (speed * direction) * dt);
    }

    if (this->getPosy() < -50.f || this->getPosy() > 950.f) {
        destroy = true;
    }
}

bool Bullet::isdestry() {
    return destroy; 
}

void Bullet::setdestroy(bool state) {
    destroy = state; 
}

bool Bullet::isEnemy() {
    return (direction == 1);
}

int Bullet::getterDamage() {
    return damage; 
}