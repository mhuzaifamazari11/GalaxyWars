#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

class MissileEnemy : public Enemy {
private:
    float shootTimer;
    int direction;

    static Texture tex;
    static bool texloaded;

public:
    MissileEnemy(float x, float y, float difficulty = 1.0f);
    void update(float dt) override;
    bool shoots() override;
};
