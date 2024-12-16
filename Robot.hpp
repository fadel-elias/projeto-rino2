#pragma once

#include "Sensor.hpp"
#include "Obstacle.hpp"
#include <vector>
#include <cmath>
#include <algorithm>

class Robot {

    private:
        int posX;
        int posY;
        int theta;
        int adjustCount;

    public:
        vector<Sensor> sensors;
        vector<Obstacle*> detectedObstacles;

        Robot(int posX, int posY, int theta) : adjustCount(0) {
            this->posX = posX;
            this->posY = posY;
            this->theta = theta;

            int angulos[4] = {0, 90, 180, 270};
        }
        void move(int units) {
            if (theta == 90) {
                posX += units;
            } else if (theta == 0) {
                posY += units;
            } else if (theta == 270) {
                posX -= units;
            } else if (theta == 180) {
                posY -= units;
            }
            else    
                cout << "Angulo Invalido" << endl;
            adjustCount = 0;
        }

        void turn(int angle) {
            theta = (theta + angle) % 360;
            cout << "Robot rotacionou para " << theta << " graus" << endl;
        }

        bool detect(vector<Obstacle*> obstacles) {
            for(int i = 0; i < 4; i++) {
                if(sensors[i].getDirecao() == 0){
                    for(int r = 0; r < sensors[i].readDistance(); r++) {
                        for(int j = 0; j < obstacles.size(); j++) {
                            if(obstacles[j]->isColliding(posX, posY + r)) {
                                cout << "Obstaculo detectado em " << posX << ", " << posY + r << endl;
                                if (std::find(detectedObstacles.begin(), detectedObstacles.end(), obstacles[j]) == detectedObstacles.end()) {
                                    detectedObstacles.push_back(obstacles[j]);
                                }
                                return true;
                            }
                        }
                    }
                } else if(sensors[i].getDirecao() == 90){
                    for(int r = 0; r < sensors[i].readDistance(); r++) {
                        for(int j = 0; j < obstacles.size(); j++) {
                            if(obstacles[j]->isColliding(posX + r, posY)) {
                                cout << "Obstaculo detectado em " << posX + r << ", " << posY << endl;
                                if (std::find(detectedObstacles.begin(), detectedObstacles.end(), obstacles[j]) == detectedObstacles.end()) {
                                    detectedObstacles.push_back(obstacles[j]);
                                }
                                return true;
                            }
                        }
                    }
                } else if(sensors[i].getDirecao() == 180){
                    for(int r = 0; r < sensors[i].readDistance(); r++) {
                        for(int j = 0; j < obstacles.size(); j++) {
                            if(obstacles[j]->isColliding(posX, posY - r)) {
                                cout << "Obstaculo detectado em " << posX << ", " << posY - r << endl;
                                if (std::find(detectedObstacles.begin(), detectedObstacles.end(), obstacles[j]) == detectedObstacles.end()) {
                                    detectedObstacles.push_back(obstacles[j]);
                                }
                                return true;
                            }
                        }
                    }
                } else if(sensors[i].getDirecao() == 270){
                    for(int r = 0; r < sensors[i].readDistance(); r++) {
                        for(int j = 0; j < obstacles.size(); j++) {
                            if(obstacles[j]->isColliding(posX - r, posY)) {
                                cout << "Obstaculo detectado em " << posX - r << ", " << posY << endl;
                                if (std::find(detectedObstacles.begin(), detectedObstacles.end(), obstacles[j]) == detectedObstacles.end()) {
                                    detectedObstacles.push_back(obstacles[j]);
                                }
                                return true;
                            }
                        }
                    }
                }
                else    
                    return false;
            }
            return false;
        }

        void addSensor(Sensor sensor) {
            sensors.push_back(sensor);
        }

        void ajustaDireção(){
            if (adjustCount > 4) {
                if(theta == 0){
                        turn(90);
                        adjustCount++;
                } else if(theta == 90){
                        turn(90);
                        adjustCount++;
                } else if(theta == 180){
                        turn(-90);
                        adjustCount++;
                } else if(theta == 270){
                        turn(-270);
                        adjustCount++;
                }
                adjustCount = 0;
                return;
            }

            for(int i = 0; i < detectedObstacles.size(); i++){
                if((detectedObstacles[i]->getPosX() == posX
                 && detectedObstacles[i]->getPosY() == posY + 1)){
                    if(theta == 0){
                        turn(270);
                        adjustCount++;
                    }
                } else if((detectedObstacles[i]->getPosX() == posX + 1
                 && detectedObstacles[i]->getPosY() == posY)){
                    if(theta == 90){
                        turn(-90);
                        adjustCount++;
                    }
                } else if((detectedObstacles[i]->getPosX() == posX
                 && detectedObstacles[i]->getPosY() == posY - 1)){
                    if(theta == 180){
                        turn(90);
                        adjustCount++;
                    }
                } else if((detectedObstacles[i]->getPosX() == posX - 1
                 && detectedObstacles[i]->getPosY() == posY)){
                    if(theta == 270){
                        turn(90);
                        adjustCount++;
                    }
                }
            }

            if (posX == 0 && theta == 270) {
                if(posY == 9){
                    turn(-90);
                    adjustCount++;
                } else{
                    turn(-270);
                    adjustCount++;
                }
           } else if (posX == 9 && theta == 90) {
                if(posY == 9){
                    turn(90);
                    adjustCount++;
                } else{
                    turn(-90);
                    adjustCount++;
                }
           } else if (posY == 9 && theta == 0) {
                if(posX <= 2){
                    turn(90);
                    adjustCount++;
                } else{
                    turn(270);
                    adjustCount++;
                }
           } else if (posY == 0 && theta == 180) {
                if(posX <= 2){
                    turn(-90);
                    adjustCount++;
                } else{
                    turn(90);
                    adjustCount++;
                }
           }
        }

        bool fimDaLinha() {
            if ((posX == 9 && posY == 8) || (posX == 8 && posY == 9))
                return true;
            else    
                return false;
        }

        int getPosX() {
            return posX;
        }

        int getPosY() {
            return posY;
        }

};