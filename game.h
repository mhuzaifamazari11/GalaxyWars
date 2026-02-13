#pragma once 
#include <SFML/Graphics.hpp>        // most imp class
#include <SFML/Audio.hpp>
#include <fstream>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "menu.h"        
#include "scoreboard.h"  
#include "levels.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"      
#include "boss.h"
#include "powerup.h"
#include "shield.h"
#include "doublescore.h"
#include "doublefire.h"
#include "aestroid.h"       
#include "shootingenemy.h"
#include "missile.h"
#include <iostream>

using namespace sf;
using namespace std;

class Game {
private:
    const int window_width = 1800;
    const int window_height = 900;
    const int frame_rate = 60;
    const int playarea = 1400;

    int maxenemies = 20;
    int maxbullets = 100;
    int maxpowerups = 5;

    RenderWindow window;
    Font font;
    Text scoreText;
    Text gameOverText;

    Texture bgTexture;
    Sprite bgSprite;

    Player* player;
    Level* levelman;
    int levelIndex;

    // Systems
    Menu* menu;
    Scoreboard* scoreBoard;

    Enemy* enemies[20];
    Bullet* bullets[100];
    PowerUp* powerups[5];

    int activeEn;
    int activeBu;
    int activePow;

    float poweruptime;

    int score;
    int currentState;


    string playerName;
    Text nameInputText;

    void events();
    void update(float dt);
    void handlein();
    void change();
    void checkCollisions();
    void powerupcome(float dt);

    void startLevel(int levelid); 

    Music bgmusic;                 // sound system instaled
    SoundBuffer shootbuffer;
    Sound shootsound;

    SoundBuffer explodebuffer;
    Sound explodesound;

    SoundBuffer winbuffer;
    Sound winsound;

    SoundBuffer losebuffer;
    Sound losesound;

public:
    Game();
    ~Game();
    void run();


    void highscore();
};
