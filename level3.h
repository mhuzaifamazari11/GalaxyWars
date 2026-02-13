#pragma once
#include "levels.h"
#include "aestroid.h"
#include "shootingenemy.h"
#include "missile.h"
#include "pattern.h" 
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

class Level3 : public Level {
private:
    int spawnCounter;

public:
    Level3();
    string bg() override;
    Enemy* comingenemy(int width) override;
};
