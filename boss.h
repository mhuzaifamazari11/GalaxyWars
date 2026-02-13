#pragma once
#include "enemy.h"
#include "levels.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

class BossEnemy : public Enemy {
private:
    float shootTimer;
    int direction;

public:
    BossEnemy(float x, float y);
    void update(float dt) override;
    bool shoots() override;
};


class BossLevel : public Level {
private:
    bool bossSpawned;

public:
    BossLevel();
    string bg() override;
    Enemy* comingenemy(int width) override;
};
