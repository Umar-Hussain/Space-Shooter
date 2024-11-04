#pragma once
#ifndef FIGHTER_H
#define FIGHTER_H

#include "Bullet.h"
#include "Player.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
using namespace sf;

class Fighter : public Player {
private:

public:
    Fighter() : Player() {}

    void handleMovements() {
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            moveUp();
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            moveLeft();
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            moveDown();
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            moveRight();
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            shoot();
        }
    }
};

#endif
