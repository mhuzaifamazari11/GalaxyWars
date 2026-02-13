#pragma once
#include<string>
#include "base.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;
class Enemy : public Entity {
protected:
    float speed;
    bool destroyed;
    int health;
    int enemyType; 

public:
    Enemy();
    virtual ~Enemy();

    virtual void update(float dt) = 0;


    virtual bool shoots() { 
        return false; 
    }

    bool checkDestroyed();
    void setDestroyed(bool state);
    void takeDamage(int amount);


    int getType();
};