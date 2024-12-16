#pragma once

#include "Sensor.hpp"
#include "Robot.hpp"

class Obstacle {
    private: 
        int posX;
        int posY;
        int size;

    public:
        Obstacle(int posX, int posY, int size) {
            this->posX = posX;
            this->posY = posY;
            this->size = size;
        }

        bool isColliding(int x, int y) {
            return x == posX && y == posY;
        }

        int getPosX() {
            return posX;
        }

        int getPosY() {
            return posY;
        }

        int getSize() {
            return size;
        }
};