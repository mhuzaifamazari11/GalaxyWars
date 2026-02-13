#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;


class Asteroid : public Enemy {
private:
    static Texture tex;
    static bool texloaded;

public:
    Asteroid(float x, float y, float diffic = 1.0f);

    void update(float dt) override;
};


