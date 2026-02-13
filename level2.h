#pragma once
#include "levels.h"
#include "aestroid.h" 
#include "shootingenemy.h"
#include "missile.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

class Level2 : public Level {
    public:
        Level2() {
            spawnInterval = 1.2f;
        }


        string bg() override {
            return "bg.png";
        }

        Enemy* comingenemy(int width) override {
        
            float randomX = static_cast<float>(rand() % (width - 50));
        
            int num1 = rand() % 100; 

       
            if (num1 < 35) {                                //kis intensity p ain gy enenies
                return new Asteroid(randomX, -50.f, 1.5f);
            }
       
            else if (num1 < 20) {
                return new ShootingEnemy(randomX, -50.f, 1.2f);
            }
        
            else {
                return new MissileEnemy(randomX, -50.f, 1.0f);
            }
        }
};

