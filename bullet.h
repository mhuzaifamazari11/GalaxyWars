#pragma once
#include "base.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;


class Player;

class Bullet : public Entity {
private:
    float speed;
    bool destroy;
    int direction;
    int damage;

    bool moving;
    Player* targ; ;             // target joa h enemy ka

    static Texture texbullet;
    static Texture texenemybullet;
    static Texture texdoublebullet;
    static Texture texmissile;
    static bool texturesloaded;

public:
    Bullet();

    Bullet(float x, float y, bool isEnemyBullet = false, bool doubleDamage = false);
    virtual ~Bullet();

    void update(float dt) override;
    void settermoving(Player* playerPtr);

    bool isdestry();
    void setdestroy(bool state);
    bool isEnemy();
    int getterDamage();
};