#pragma once
#include "levels.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

class Level1 : public Level {

public:
    Level1() {
        spawnInterval = 1.5f;
    }

    string bg() override {
        return "bg.png";
    }

    Enemy* comingenemy(int width) override {
        
        float randomX = static_cast<float>(rand() % (width - 50));
        int type = rand() % 2;

        if (type == 0) {
            return new Asteroid(randomX, -50.f, 1.0f);          //kis intensity p ain gy enenies
        }
        else {
            return new ShootingEnemy(randomX, -50.f, 1.0f);
        }
    }
};

