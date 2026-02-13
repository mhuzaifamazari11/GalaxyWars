#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;


class ShootingEnemy : public Enemy {
private:
    float movetime;
    float shoottime;
    int direction;

    static Texture tex;
    static bool texloaded;

public:

    ShootingEnemy(float x, float y, float diffic = 1.0f);
    void update(float dt) override;
    bool shoots() override;
};

