#include "game.h"
#include <cstdlib> 
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int menustate = 0;
int playstate = 1;
int pausestate = 2;
int gameoverstate = 3;
int levelselec = 4;
int name = 5;
int highscores = 6;
int victory = 7;


int level2scr = 500;
int level3scr = 1500;
int levelbscr = 3000;

// ------------------------- const --------------------------------------

Game::Game() {
    window.create(VideoMode(window_width, window_height), "Galaxy Wars");
    window.setFramerateLimit(frame_rate);

    menu = new Menu(window_width, window_height);
    scoreBoard = new Scoreboard();

    // ---------------------------   sounds  ------------------------------ ////
    if (!bgmusic.openFromFile("background.ogg")) {
        cout << "Error: bg_music.ogg not found!" << endl;
    }
    else {
        bgmusic.setLoop(true);
        bgmusic.setVolume(50); 
        bgmusic.play();       
    }


    if (shootbuffer.loadFromFile("laser.wav")) {
        shootsound.setBuffer(shootbuffer);
        shootsound.setVolume(40);
    }

    
    if (explodebuffer.loadFromFile("explosion.wav")) {
        explodesound.setBuffer(explodebuffer);
    }

    if (winbuffer.loadFromFile("win.wav")) {
        winsound.setBuffer(winbuffer);
    }

    if (losebuffer.loadFromFile("lose.wav")) {
        losesound.setBuffer(losebuffer);
    }

    if (!font.loadFromFile("COOPBL.ttf")) cout << "Error loading font" << endl;

    scoreText.setFont(font);
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(1420.f, 10.f);

    nameInputText.setFont(font);
    nameInputText.setCharacterSize(30);
    nameInputText.setPosition(600.f, 300.f);
    playerName = "";

    player = new Player();
    levelman = nullptr;

    maxenemies = 20;
    maxbullets = 100;                               // aik num specifically assign, and arrays ko nill
    maxpowerups = 5;

    for (int i = 0; i < maxenemies; i++) {
        enemies[i] = nullptr;
    }

    for (int i = 0; i < maxbullets; i++) {
        bullets[i] = nullptr;
    }

    for (int i = 0; i < maxpowerups; i++) {
        powerups[i] = nullptr;
    }

    activeEn = 0;
    activeBu = 0;
    activePow = 0;
    score = 0;

 
    currentState = name;

    startLevel(1);

    srand(time(0));
}

// ------------------------- destruct --------------------------------------

Game::~Game() {
    delete player;
    if (levelman) {
        delete levelman;
    }

    delete menu;
    delete scoreBoard;

    for (int i = 0; i < activeEn; i++) {
        if (enemies[i]) {
            delete enemies[i];
        }
    }

    for (int i = 0; i < activeBu; i++) {
        if (bullets[i]) {
            delete bullets[i];
        }
    }

    for (int i = 0; i < activePow; i++) {
        if (powerups[i]) {
            delete powerups[i];
        }
    }

}

// ------------------------- statrt --------------------------------------

void Game::startLevel(int levelnum) {               // as in startign , koi bhi bullet, eenmy n ho
    
    for (int i = 0; i < activeEn; i++) { 
        delete enemies[i]; 
        enemies[i] = nullptr; 
    }

    for (int i = 0; i < activeBu; i++) {
        delete bullets[i]; 
        bullets[i] = nullptr; 
    }

    for (int i = 0; i < activePow; i++) {
        delete powerups[i]; 
        powerups[i] = nullptr; 
    }

    activeEn = 0;
    activeBu = 0;
    activePow = 0;

    if (levelnum == 1) {
        score = 0;
    }

    delete player;
    player = new Player();

    if (levelman) {
        delete levelman;
    }

    levelIndex = levelnum;


    switch (levelnum) {
        case 1: 
            levelman = new Level1(); 
            break;
        case 2: 
            levelman = new Level2(); 
            break;
        case 3: 
            levelman = new Level3(); 
            break;     
        case 4: 
            levelman = new BossLevel();
            break;  
        default: 
            levelman = new Level1(); 
            break;
    }

    if (bgTexture.loadFromFile(levelman->bg())) {
        bgSprite.setTexture(bgTexture);

        Vector2u textureSize = bgTexture.getSize();
        float scaleX = window_width / textureSize.x;
        float scaleY = window_height / textureSize.y;

        bgSprite.setScale(scaleX, scaleY);
    }
}

// ------------------------- run kro --------------------------------------

void Game::run() {                          // the game main lloop
    Clock clock;
    while (window.isOpen()) {
        Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();
        events();
        update(dt);
        change();
    }
}

// ----------------------- GMAE KY EEENTS- --------------------------
void Game::events() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) window.close();

        if (currentState == name) {                             // name enter kia
            if (event.type == Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == 8 && playerName.size() > 0) {
                        playerName.pop_back();
                    }
                    else if (event.text.unicode != 8 && event.text.unicode != 13 && event.text.unicode != 27) {
                        if (playerName.size() < 15) {
                            playerName += static_cast<char>(event.text.unicode);
                        }
                    }
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                if (playerName.length() > 0) {
                    currentState = menustate;
                    menu->setMenuState(0);
                }
            }
        }

        else if (event.type == Event::KeyPressed) {

            if (currentState == highscores) {
                if (event.key.code == Keyboard::Escape || event.key.code == Keyboard::Enter) {
                    currentState = menustate;
                }
                return;
            }

            if (currentState != playstate) {
                if (event.key.code == Keyboard::Up) {
                    menu->moveup();
                }

                if (event.key.code == Keyboard::Down) {
                    menu->movedown();           // menu ki handling 
                }

                if (event.key.code == Keyboard::Enter) {           // menu ky andr , check krna kkn select kia
                    int choice = menu->GetPressedItem();

                    if (currentState == menustate) {
                        if (choice == 0) { 
                            currentState = levelselec;
                            menu->setMenuState(4); 
                        }

                        if (choice == 1) { 
                            currentState = highscores;
                        }

                        if (choice == 2) { 
                            window.close(); 
                        }

                    }
                    else if (currentState == levelselec) {
                        if (choice == 0) { 
                            startLevel(1); 
                            currentState = playstate; 
                        }

                        if (choice == 1) {
                            startLevel(2); 
                            currentState = playstate; 
                        }

                        if (choice == 2) {
                            startLevel(3); 
                            currentState = playstate; 
                        }

                        if (choice == 3) { 
                            startLevel(4); 
                            currentState = playstate; 
                        }

                        if (choice == 4) { 
                            currentState = menustate; 
                            menu->setMenuState(0); 
                        }

                    }
                    else if (currentState == pausestate) {
                        if (choice == 0) {
                            currentState = playstate;
                        }

                        if (choice == 1) { 
                            startLevel(levelIndex); 
                            currentState = playstate; 
                        }

                        if (choice == 2) { 
                            currentState = menustate; 
                            menu->setMenuState(0); 
                        }

                    }
               
                    else if (currentState == gameoverstate || currentState == victory) {
                        if (choice == 0) { 
                            highscore();
                            scoreBoard->saveScore(playerName, score);
                        }

                        if (choice == 1) {
                            currentState = menustate; 
                            menu->setMenuState(0); 
                        }

                        if (choice == 2) {
                            window.close();
                        }
                    }
                }
            }

            if (event.key.code == Keyboard::Escape) {
                if (currentState == playstate) {
                    currentState = pausestate;
                    menu->setMenuState(2);
                }
                else if (currentState == pausestate) {
                    currentState = playstate;
                }
            }
        }
    }
}

// ------------------------- UPADTAE FUNC --------------------------------------

void Game::update(float dt) {
    if (currentState != playstate) {
        return;
    }

    player->update(dt);

    if (player->getPosx() > playarea - 50) {            // player ki posiitono ko within the boundry rkhny ky liye
        player->setPos(playarea - 50, player->getPosy());
    }

    handlein();
    powerupcome(dt);

 
    if (levelIndex == 1 && score > level2scr) {         // levle progression set ki thi
        startLevel(2);
        player->heal(); 
    }
    else if (levelIndex == 2 && score > level3scr) {
        startLevel(3);
    }
    else if (levelIndex == 3 && score > levelbscr) {
        startLevel(4);
    }
    

    if (activeEn < maxenemies) {                    //  ckh ky new enemy aa skta h?
        Enemy* newEnemy = levelman->update(dt, playarea);
        if (newEnemy != nullptr) {
            enemies[activeEn] = newEnemy;
            activeEn++;
        }
    }

    for (int i = 0; i < activeEn; i++) {
        enemies[i]->update(dt);

        if (enemies[i]->shoots()) {             // chek ky buellets hn dhoot ky liye
            if (activeBu < maxbullets) {
                Bullet* newBullet = new Bullet(enemies[i]->getPosx() + 25, enemies[i]->getPosy() + 50, true);

                if (enemies[i]->getType() == 2) {
                    newBullet->settermoving(player);
                }

                if (enemies[i]->getType() == 3) {
                    newBullet = new Bullet(enemies[i]->getPosx(), enemies[i]->getPosy() + 80, true);
                }

                bullets[activeBu] = newBullet;
                activeBu++;
            }
        }

        if (enemies[i]->checkDestroyed()) {             // ckh ky agr enemy ddestroy ho rha h

            explodesound.play();
        
            if (enemies[i]->getType() == 3) {           // boos type enemy ++ scores
                player->addScore(4990);
                score += 4990;
                currentState = victory; 
                menu->setMenuState(7);

                bgmusic.stop();
                winsound.play();
            }
       

            delete enemies[i];
            enemies[i] = enemies[activeEn - 1];
            activeEn--;
            i--;
        }
    }

    for (int i = 0; i < activeBu; i++) {                // bullet khtam krni h colllison ky bad
        bullets[i]->update(dt);
        if (bullets[i]->isdestry()) {
            delete bullets[i];
            bullets[i] = bullets[activeBu - 1];
            activeBu--;
            i--;
        }
    }

    for (int i = 0; i < activePow; i++) {
        powerups[i]->update(dt);
        if (powerups[i]->getPosy() > 900.f) {
            delete powerups[i];
            powerups[i] = powerups[activePow - 1];
            activePow--;
            i--;
        }
    }

    checkCollisions();

    scoreText.setPosition(1500, 100);
    string status = "Score: " + to_string(player->getScore()) + " \n| Health: " + to_string(player->heal_get()) + " \n| Level: " + to_string(levelIndex);
    scoreText.setString(status);

    if (player->isDead()) {             // agr player mr jae
        currentState = gameoverstate;
        menu->setMenuState(3);

        highscore();

        bgmusic.stop();
        losesound.play();
    }
}

// ------------------------- HANDLE --------------------------------------

void Game::handlein() {
    static float fireTimer = 0.f;               // aik timer lgaya h bullet fire krny ky liye
    fireTimer += 0.016f;

    if (Keyboard::isKeyPressed(Keyboard::Space) && fireTimer > 0.3f) {
        if (activeBu < maxbullets) {
            bool doubleDmg = player->has_doublefire();
            bullets[activeBu] = new Bullet(player->getPosx() + 65, player->getPosy(), false, doubleDmg);
            activeBu++;

            shootsound.play();

            fireTimer = 0.f;
        }
    }
}

// ------------------------- POWERUPS --------------------------------------

void Game::powerupcome(float dt) {              // power uo ae ga every 7 sec
    poweruptime += dt;

    if (poweruptime > 7.0f) {
        if (activePow < maxpowerups) {
            float num = static_cast<float>(rand() % (playarea - 50));

            int type = rand() % 3;              // randomly genrate kia, koi bhi aa gi 

            if (type == 0) {
                powerups[activePow] = new Shield(num, -50.f);
            }

            else if (type == 1) {
                powerups[activePow] = new DoubleScore(num, -50.f);
            }

            else {
                powerups[activePow] = new DoubleFire(num, -50.f);
            }

            activePow++;
            poweruptime = 0.f;
        }
    }
}

// ------------------------- COLLISION --------------------------------------

void Game::checkCollisions() {

    for (int i = 0; i < activeBu; i++) {                // bullrt and enenmy
        if (!bullets[i]) {
            continue;
        }

        float bulletX = bullets[i]->getPosx();              // chking kt bullet ki lefyt side enemy ki roght sidde p touch hoi
        float bulletY = bullets[i]->getPosy();              // and vise versa, pori width compare ki, ky koi edge touch ho jae
        float bulletW = bullets[i]->boundry().width;
        float bulletH = bullets[i]->boundry().height;

        if (bullets[i]->isEnemy()) {
            float playX = player->getPosx();
            float playY = player->getPosy();
            float playW = player->boundry().width;
            float playH = player->boundry().height;

            bool hitX = (bulletX + bulletW >= playX) && (bulletX <= playX + playW);     // main syttem
            bool hitY = (bulletY + bulletH >= playY) && (bulletY <= playY + playH);
                                // player should be below, bullet sy
            if (hitX && hitY) {
                player->takeDamage(10);
                bullets[i]->setdestroy(true);
            }
        }
        else {

            for (int j = 0; j < activeEn; j++) {
                
                if (!enemies[j]) {
                    continue;
                }

                float enemyX = enemies[j]->getPosx();
                float enemyY = enemies[j]->getPosy();
                float enemyW = enemies[j]->boundry().width;
                float enemyH = enemies[j]->boundry().height;

                bool hitX = (bulletX + bulletW >= enemyX) && (bulletX <= enemyX + enemyW);
                bool hitY = (bulletY + bulletH >= enemyY) && (bulletY <= enemyY + enemyH);

                if (hitX && hitY) {
                    bullets[i]->setdestroy(true);
                    enemies[j]->takeDamage(bullets[i]->getterDamage());
                    if (enemies[j]->checkDestroyed()) {
                        score += 10;
                        player->addScore(10);

                        explodesound.play();

                    }
                    break;
                }
                
            }
        }
    }

    float pleyX = player->getPosx();
    float pleyY = player->getPosy();
    float pleyW = player->boundry().width;
    float pleyH = player->boundry().height;

    for (int i = 0; i < activeEn; i++) {                // enemy & player
        float enemyX = enemies[i]->getPosx();
        float enemyY = enemies[i]->getPosy();
        float enemyW = enemies[i]->boundry().width;
        float enemyH = enemies[i]->boundry().height;

        bool collideX = (enemyX + enemyW >= pleyX) && (enemyX <= pleyX + pleyW);
        bool collideY = (enemyY + enemyH >= pleyY) && (enemyY <= pleyY + pleyH);

        if (collideX && collideY) {
            player->takeDamage(20);
            enemies[i]->setDestroyed(true);
            explodesound.play();

        }
    }

    for (int i = 0; i < activePow; i++) {               // Powerips adn player
        float puX = powerups[i]->getPosx();
        float puY = powerups[i]->getPosy();
        float puW = powerups[i]->boundry().width;
        float puH = powerups[i]->boundry().height;

        bool collideX = (puX + puW >= pleyX) && (puX <= pleyX + pleyW);
        bool collideY = (puY + puH >= pleyY) && (puY <= pleyY + pleyH);

        if (collideX && collideY) {
            int type = powerups[i]->getType();
            if (type == 0) {
                player->shieldok();
            }

            else if (type == 1) {                   // tpye chek ky kia award dyna h
                player->doublescoreok();
            }

            else if (type == 2) {
                player->doublefireok();
            }

            delete powerups[i];
            powerups[i] = powerups[activePow - 1];
            activePow--;
            i--;
        }
    }
}

// ------------------------- CHANGE THE WINDOW --------------------------------------

void Game::change() {       // window change krny ky liye, gamae khatm hoi t ab kia hoga
    window.clear();
    window.draw(bgSprite);

    if (currentState == playstate) {                // draw kr rhy hn player, sprite ko
        player->draw(window);
        for (int i = 0; i < activeEn; i++) {
            enemies[i]->draw(window);
        }

        for (int i = 0; i < activeBu; i++) {
            bullets[i]->draw(window);
        }

        for (int i = 0; i < activePow; i++) {
            powerups[i]->draw(window);
        }
        window.draw(scoreText);
    }

    else if (currentState == name) {
        nameInputText.setString("Enter Player Name:\n\n> " + playerName + "_");
        FloatRect textRect = nameInputText.getLocalBounds();
        nameInputText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        nameInputText.setPosition(window_width / 2.0f, window_height / 2.0f);
        window.draw(nameInputText);
    }

    else if (currentState == highscores) {
        Text headerText;
        headerText.setFont(font);
        headerText.setString("TOP SCORES");
        headerText.setCharacterSize(50);
        headerText.setFillColor(Color::Cyan);
        headerText.setPosition(750.f, 50.f);
        window.draw(headerText);

        int count = scoreBoard->getCount();
        if (count > 10) count = 10;

        for (int i = 0; i < count; i++) {
            ScoreEntry se = scoreBoard->getEntry(i);
            string line = to_string(i + 1) + ". " + se.name + " - " + to_string(se.score);
            
            Text entryText;
            entryText.setFont(font);                    // high score m likh rhy hn
            entryText.setCharacterSize(30);
            entryText.setFillColor(Color::White);
            entryText.setString(line);
            entryText.setPosition(700.f, 150.f + (i * 50.f));
            window.draw(entryText);
        }

        Text backText;
        backText.setFont(font);
        backText.setCharacterSize(20);
        backText.setFillColor(Color::Yellow);
        backText.setString("Press Esc or Enter to Back");
        backText.setPosition(780.f, 800.f);
        window.draw(backText);
    }

    else if (currentState == menustate || currentState == pausestate  || currentState == levelselec || currentState == victory || currentState == gameoverstate) {
        menu->draw(window);
        if (currentState == victory) {
            nameInputText.setString("Player : " + playerName + "\nScore: " + to_string(score) + "\n\nCongrats");
            nameInputText.setPosition(600.f, 200.f);
            window.draw(nameInputText);
        }
        else if (currentState == gameoverstate) {
            //menu->draw(window);
            nameInputText.setString("Player : " + playerName + "\nScore: " + to_string(score) + "\n\nDefeats");
            nameInputText.setPosition(600.f, 200.f);
            window.draw(nameInputText);
        }
    }
    
    

    window.display();
}

// ------------------------- SCORES --------------------------------------

void Game::highscore() {

    scoreBoard->saveScore(playerName, score);
}
