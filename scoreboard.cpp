#include "scoreboard.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

Scoreboard::Scoreboard() {
    filename = "scores.txt";
    scoreCount = 0;
    loadScores();
}

void Scoreboard::bubbleSort() {                         // descendinf  order m sort krna h
    for (int i = 0; i < scoreCount - 1; i++) {
        for (int j = 0; j < scoreCount - i - 1; j++) {
            if (scores[j].score < scores[j + 1].score) {
                ScoreEntry temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }
}

void Scoreboard::loadScores() {                 // file appending , reading
    scoreCount = 0;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Scores file not found. Creating a new one..." << endl;

        ofstream newFile(filename);
        newFile.close();

        return;
    }

    string name;
    int score;
    while (scoreCount < maxscore && file >> name >> score) {
        scores[scoreCount].name = name;
        scores[scoreCount].score = score;
        scoreCount++;
    }
    file.close();

    bubbleSort();
}

void Scoreboard::saveScore(string name, int score) {
    
    if (scoreCount < maxscore) {
        scores[scoreCount].name = name;
        scores[scoreCount].score = score;
        scoreCount++;
    }

    else {
        if (score > scores[maxscore - 1].score) {
            scores[maxscore - 1].name = name;
            scores[maxscore - 1].score = score;
        }
    }

    bubbleSort();

    ofstream file(filename);                    // fiel wriitng
    if (file.is_open()) {
        for (int i = 0; i < scoreCount; i++) {
            file << scores[i].name << " " << scores[i].score << endl;
        }
        file.close();
    }
}

int Scoreboard::getCount() { 
    return scoreCount; 
}

ScoreEntry Scoreboard::getEntry(int index) {
    if (index >= 0 && index < scoreCount) {
        return scores[index];
    }


}
