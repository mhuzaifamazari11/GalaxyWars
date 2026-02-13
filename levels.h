#pragma once
#include "enemy.h"
#include "aestroid.h"
#include "shootingenemy.h"
#include <string>
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

class Level {
protected:
    float spawnTimer;
    float spawnInterval;

public:
    Level() {
        spawnTimer = 0.f; spawnInterval = 1.0f; 
    }
    
    virtual ~Level() {
    
    }

    virtual Enemy* update(float dt, int playAreaWidth) {            // 
        spawnTimer += dt;
        
        if (spawnTimer > spawnInterval) {
            spawnTimer = 0.f;
            
            return comingenemy(playAreaWidth);
        }
        return nullptr;
    }

    virtual Enemy* comingenemy(int width) = 0;

    virtual string bg() = 0;
};