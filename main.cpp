#include "Sensor.hpp"
#include "Robot.hpp"
#include "Obstacle.hpp"
#include "Environment.hpp"
#include <SDL2/SDL.h>

vector<Obstacle*> Environment::obstacles;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int GRID_SIZE = 10;
const int CELL_SIZE = SCREEN_WIDTH / GRID_SIZE;

static void printEnvironment(Environment env, Robot* robot) {
    char grid[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if(i < 2 && i >= 0 && j > 2 && j < 7)
                grid[i][j] = '#';
            else 
                grid[i][j] = '.';
        }
    }

    for (int j = 1; j < 6; j++) {
        grid[9 - env.obstacles[j]->getPosY()][env.obstacles[j]->getPosX()] = 'O';   
    }

    grid[9 - robot->getPosY()][robot->getPosX()] = 'R';

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void renderEnvironmentSDL(SDL_Renderer* renderer, Environment env, Robot* robot) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int j = 1; j < 6; j++) {
        SDL_Rect rect = {env.obstacles[j]->getPosX() * CELL_SIZE, (GRID_SIZE - 1 - env.obstacles[j]->getPosY()) * CELL_SIZE, CELL_SIZE, CELL_SIZE};
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect robotRect = {robot->getPosX() * CELL_SIZE, (GRID_SIZE - 1 - robot->getPosY()) * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_RenderFillRect(renderer, &robotRect);

    SDL_RenderPresent(renderer);
}

int main() {
    srand(time(NULL));

    Robot robot(0, 0, 90);
    robot.addSensor(Sensor(8, 0));
    robot.addSensor(Sensor(8, 90));
    robot.addSensor(Sensor(8, 180));
    robot.addSensor(Sensor(8, 270));

    Environment env(10, 10);

    for(int i=0; i<6; i++){
        Obstacle* obstacle = new Obstacle(rand()% 10, rand()% 10, 1);
        Environment::obstacles.push_back(obstacle);
        cout << "Obstaculo " << i << " posicionado em " << obstacle->getPosX() << ", " << obstacle->getPosY() << endl;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL não pôde ser inicializado! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Simulação de Robô", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Janela não pôde ser criada! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cout << "Renderizador não pôde ser criado! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        env.simulate(&robot);
        renderEnvironmentSDL(renderer, env, &robot);
        printEnvironment(env, &robot);
        cout << "Robot esta em " << robot.getPosX() << ", " << robot.getPosY() << endl;
        SDL_Delay(500);

        if (robot.getPosX() > 2 && robot.getPosX() < 7 && robot.getPosY() > 7 && robot.getPosY() <= 9) {
            cout << "Chegou ao destino!" << endl;
            quit = true;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}