#include "Enemigo.h"
using namespace std;
int directionxpos = 1;
int directionxneg = -1;
int directionypos = 1;
int directionyneg = -1;
int positionxwidth = 1;
int positionyheight = 1;
Enemigo::Enemigo()
{
	spawn = { 0,0 };
	position = spawn;
	direction = { 0,0 };
}

Enemigo::Enemigo(COORD _spawn)
{
	spawn = _spawn;
	position = _spawn;
	direction = { 0,0 };

}

void Enemigo::Draw()
{
	ConsoleUtils::Console_SetPos(position);
	ConsoleUtils::Console_SetColor(foreground, background);
	cout << character;
}

void Enemigo::PowerUpPicked()
{
	powerup_countdown = TimeManager::getInstance().time + powerup_countdown_time;
}

Enemigo::ENEMY_STATE Enemigo::Update(Map* _map, COORD _player)
{


	RandomDirection();
	COORD  newPosition = position;
	newPosition.X += direction.X;
	newPosition.Y += direction.Y;

	if (newPosition.X < 0)
	{
		newPosition.X = _map->Width - positionxwidth;
	}
	newPosition.X %= _map->Width;
	if (newPosition.Y < 0)
	{
		newPosition.Y = _map->Height - positionyheight;
	}
	newPosition.Y %= _map->Height;

	switch (_map->GetTile(newPosition.X, newPosition.Y))
	{
	case Map::MAP_TILES::MAP_WALL:
		newPosition = position;
		break;
	}
	position = newPosition;
	ENEMY_STATE state = ENEMY_STATE::ENEMY_NONE;
	if (position.X == _player.X && position.Y == _player.Y)
	{
		if (powerup_countdown <= TimeManager::getInstance().time)
		{
			state = ENEMY_STATE::ENEMY_DEAD;
		}
		else
		{
			position = spawn;
			state = ENEMY_STATE::ENEMY_KILLED;
		}

	}
	if (powerup_countdown <= TimeManager::getInstance().time) {
		foreground = foreground_attack;
	}
	else
	{
		foreground = foreground_powerUp;
	}
	return state;
}

void Enemigo::RandomDirection()
{
	direction = { 0,0 };
	int random = rand() % 4;
	switch (random)
	{
	case 0:
		direction.X = directionxpos;
		break;
	case 1:
		direction.X = directionxneg;
		break;
	case 2:
		direction.Y = directionypos;
		break;
	case 3:
		direction.Y = directionyneg;
		break;
	default:
		break;
	}
}
