#pragma once
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

class ScoreEntry {
    public:
        string name;
        int score;
};

class Scoreboard {
private:
    static const int maxscore = 50;
    ScoreEntry scores[maxscore];
    int scoreCount;
    string filename;

    void bubbleSort();                      // sort krna h in descending order

public:
    Scoreboard();
    void loadScores();
    void saveScore(string name, int score);

    int getCount();
    ScoreEntry getEntry(int index);
};

