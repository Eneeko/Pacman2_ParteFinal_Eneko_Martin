#include "Player.h"
int numpointspowerup = 25;
int numwidth = 1;
int numheight = 1;
int numpositionx = 0;
int numpositiony = 0;
Player::Player(COORD _spawn)
{
    spawn = _spawn;
    position = _spawn;
    direction = { 0,0 };
}

void Player::Update(Map* _map, USER_INPUTS input, std::vector<Enemigo>* enemigos)
{
    COORD newPosition = position;

    switch (input)
    {
    case UP:
        newPosition.Y--;
        break;
    case DOWN:
        newPosition.Y++;
        break;
    case RIGHT:
        newPosition.X++;
        break;
    case LEFT:
        newPosition.X--;
        break;
    }
    if (newPosition.X < numpositionx)
    {
        newPosition.X = _map->Width - numwidth;
    }
    newPosition.X %= _map->Width;
    if (newPosition.Y < numpositiony)
    {
        newPosition.Y = _map->Height - numheight;
    }
    newPosition.Y %= _map->Height;

    switch (_map->GetTile(newPosition.X, newPosition.Y))
    {
    case Map::MAP_TILES::MAP_WALL:
        newPosition.Y = position.Y;
        newPosition.X = position.X;
        break;
    case Map::MAP_TILES::MAP_POINT:
        _map->points--;
        points++;
        _map->SetTile(newPosition.X, newPosition.Y, Map::MAP_TILES::MAP_EMPTY);
        break;

    case Map::MAP_TILES::MAP_POWERUP:
        points += numpointspowerup;
        for (size_t i = 0; i < enemigos->size(); i++)
        {
            (*enemigos)[i].PowerUpPicked();
        }

        _map->SetTile(newPosition.X, newPosition.Y, Map::MAP_TILES::MAP_EMPTY);
        break;
    }

    position = newPosition;
}

void Player::Draw()
{
    ConsoleUtils::Console_SetPos(position);
    ConsoleUtils::Console_SetColor(foreground, background);
    std::cout << character;
}