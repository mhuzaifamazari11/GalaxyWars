#include <SFML/Graphics.hpp>
#include <iostream>
#include "base.h"
using namespace sf;
using namespace std;


    Entity :: ~Entity() {}

    void Entity::update(float dt) {
    
    }

    void Entity :: draw(RenderWindow& window) {                 // posiotns aari parent class sy
        window.draw(sprite);
    }

    void Entity::setPos(float x, float y) {
        sprite.setPosition(x, y);
    }

    float Entity::getPosx() {
        return sprite.getPosition().x;
    }

    float Entity::getPosy() {
        return sprite.getPosition().y;
    }

    FloatRect Entity::boundry() {
        return sprite.getGlobalBounds();
    }

    void Entity::loadTexture(string path) {                 // error parent sy ineritr
        if (!texture.loadFromFile(path)) {
            cout << "Error loading texture: " << path << endl;
        }
        sprite.setTexture(texture);
    }

