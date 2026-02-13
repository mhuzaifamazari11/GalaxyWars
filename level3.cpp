#include "level3.h"

Level3::Level3() {
    spawnInterval = 1.0f;
    spawnCounter = 0;
}

string Level3::bg() {
    return "bg.png";
}

Enemy* Level3::comingenemy(int width) {
    
    float randomX = static_cast<float>(rand() % (width - 50));
    int num2 = rand() % 100;

    spawnCounter++;

    if (num2 < 20) {                    // randonly geenrate krwa rhy hn, the enemies 
        return new Asteroid(randomX, -50.f, 2.0f);
    }
    else if (num2 < 50) {
        
        float startX = (spawnCounter % 2 == 0) ? width - 100.f : 50.f;
        return new PatternEnemy(startX, -50.f, spawnCounter, 1.5f);
    
    }
    else if (num2 < 80) {
        return new ShootingEnemy(randomX, -50.f, 1.5f);
    }
    else {
        return new MissileEnemy(randomX, -50.f, 1.2f);
    }
}
