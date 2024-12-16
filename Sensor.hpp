#pragma once

#include <iostream>
using namespace std;

class Sensor {
    private:
        int range;
        int direcao;
        float noise;

    public:
        Sensor(int range, int direcao){
            this->range = range;
            this->noise = (rand() % 51 + 25) / 100.0; 
            this->direcao  = direcao;   
        }

        int getRange() {
            return range;
        }

        int getDirecao() {
            return direcao;
        }

        float readDistance() const{
            float distance = range*noise;
            return distance;
        }
        float setDistance(int distance){
            return distance;
        }
        
};