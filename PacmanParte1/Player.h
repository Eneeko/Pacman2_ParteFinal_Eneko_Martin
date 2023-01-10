#pragma once
#include "ConsoleUtils.h"
#include "Map.h"
#include "Enemigo.h"
#include <vector>

enum USER_INPUTS { NONE, UP, DOWN, RIGHT, LEFT, QUIT };

class Player
{
private:
    COORD direction;
    char character = 'O';
    ConsoleUtils::CONSOLE_COLOR foreground = ConsoleUtils::CONSOLE_COLOR::YELLOW;
    ConsoleUtils::CONSOLE_COLOR background = ConsoleUtils::CONSOLE_COLOR::BLACK;

public:
    COORD spawn;
    COORD position;
    int points = 0;
    Player(COORD _spawn);
    void Update(Map* _map, USER_INPUTS input, std::vector<Enemigo>* enemigos);
    void Draw();
};

