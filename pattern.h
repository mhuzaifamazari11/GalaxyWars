#pragma once
#include "enemy.h"

class PatternEnemy : public Enemy {
private:
    int direction;
    int id;
    float shootTimer;

public:
    PatternEnemy(float x, float y, int id, float diffic = 1.0f);
    void update(float dt) override;
    bool shoots() override;
};
