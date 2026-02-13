#pragma once
#include "base.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class PowerUp : public Entity {
    protected:
        float speed;
        int type;
        int resourceValue;

    public:
        PowerUp();
        
        virtual ~PowerUp();
        void update(float dt) override;
        int getType();

        friend int operator+(PowerUp& p1, PowerUp& p2);
};
