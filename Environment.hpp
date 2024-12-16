#pragma once

#include "Sensor.hpp"
#include "Robot.hpp"
#include "Obstacle.hpp"
#include <vector>

class Environment
{
    private:
        int tamX;
        int tamY;

    public:
        Environment(int tamX, int tamY) {
            this->tamX = tamX;
            this->tamY = tamY;
        }

        static vector<Obstacle*> obstacles;
        static vector<Robot> robots;

        void simulate(Robot* robot){
                robot->detect(obstacles);
                robot->ajustaDireção();
                robot->move(1);
        }
};