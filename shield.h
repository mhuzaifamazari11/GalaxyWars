#pragma once
#include "powerup.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

class Shield : public PowerUp {             // inherts ho rha h powerup sy
    public:

        Shield(float x, float y);
};