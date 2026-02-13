#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;



class Entity {                      // parent h sb ki y class
protected:

    Sprite sprite;
    Texture texture;

public:
    
    virtual ~Entity() ;
    virtual void update(float dt) = 0;

    void draw(RenderWindow& window);

    void setPos(float x, float y);

    float getPosx();

    float getPosy();

    FloatRect boundry();

    void loadTexture(string path); 

};