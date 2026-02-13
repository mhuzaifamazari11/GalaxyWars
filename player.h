#pragma once
#include "base.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;


class Player : public Entity {
private:
    float velocityx;
    float velocityy;
    float speed;
    int health; 
    int score;
    int healthget;
    Clock damageClock;


    bool shielded;
    float shieldtime;
    bool doublescore;
    float doublescoretime;
    bool doublefire;
    float doublefiretime;

    void movePlayer();

public:
    Player();
    void update(float dt) override;

    void takeDamage(int amount);
    void heal();
    void addScore(int amount);

    void shieldok();
    
    void doublescoreok();
    void doublefireok();
    bool has_doublefire();


    bool isDead();
    int getScore();

    int heal_get();
};