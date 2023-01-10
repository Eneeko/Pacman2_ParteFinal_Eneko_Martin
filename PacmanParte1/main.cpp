#include "Map.h"
#include "Enemigo.h"
#include "TimeManager.h"
#include "Player.h"

#include <vector>

int numdeatchCount = 3;
int pacmanmappoints = 0;
int numplayerpoints = 50;
int numenemynumber = 0;
/// <summary>
/// Sets the needed variables
/// </summary>
void Setup();
/// <summary>
/// Handles the inputs
/// </summary>
void Input();
/// <summary>
/// Handles the logic of the game
/// </summary>
void Logic();
/// <summary>
/// Draws the screen
/// </summary>
void Draw();

Map pacman_map = Map();
std::vector<Enemigo> enemigos;
USER_INPUTS input = USER_INPUTS::NONE;
Player player = Player(pacman_map.spawn_player);
int deathCount = 0;

bool run = true;
bool win = false;
bool alive = true;


int main()
{

    Setup();
    while (run)
    {
        Input();
        Logic();
        Draw();
    }
}

void Setup()
{
    std::cout.sync_with_stdio(false);
    srand(time(NULL));

    unsigned short enemyNumber = numenemynumber;
    std::cout << "Cuantos enemigos quieres?";
    std::cin >> enemyNumber;
    for (size_t i = 0; i < enemyNumber; i++)
    {
        enemigos.push_back(Enemigo(pacman_map.spawn_enemy));
    }
}

void Input()
{
    input = USER_INPUTS::NONE;
    if (ConsoleUtils::KeyPressed(VK_UP) || ConsoleUtils::KeyPressed('W'))
    {
        input = USER_INPUTS::UP;
    }
    if (ConsoleUtils::KeyPressed(VK_DOWN) || ConsoleUtils::KeyPressed('S'))
    {
        input = USER_INPUTS::DOWN;
    }
    if (ConsoleUtils::KeyPressed(VK_RIGHT) || ConsoleUtils::KeyPressed('D'))
    {
        input = USER_INPUTS::RIGHT;
    }
    if (ConsoleUtils::KeyPressed(VK_LEFT) || ConsoleUtils::KeyPressed('A'))
    {
        input = USER_INPUTS::LEFT;
    }
    if (ConsoleUtils::KeyPressed(VK_ESCAPE) || ConsoleUtils::KeyPressed('Q'))
    {
        input = USER_INPUTS::QUIT;
    }
}

void Logic()
{
    if (win)
    {
        switch (input)
        {
         case QUIT:
            run = false;
            break;
        }
    }
    else if (!alive)
    {
        switch (input)
        {
         case QUIT:
            run = false;
            break;
        }
    }
    else
    {
        if (input == USER_INPUTS::QUIT)
        {
            run = false;
        }
        player.Update(&pacman_map, input, &enemigos);

        for (size_t i = 0; i < enemigos.size(); i++)
        {
            Enemigo::ENEMY_STATE enemystate = enemigos[i].Update(&pacman_map, player.position);
            switch (enemystate)
            {
            case Enemigo::ENEMY_KILLED:
                player.points += numplayerpoints;
                break;
            case Enemigo::ENEMY_DEAD:
                player.position.X = pacman_map.spawn_player.X;
                player.position.Y = pacman_map.spawn_player.Y;
                deathCount++;
                break;
            }


        }
        if (deathCount >= numdeatchCount)
        {
            alive = false;
        }
        if (pacman_map.points <= pacmanmappoints)
        {
            win = true;
        }

    }
}

void Draw()
{
    ConsoleUtils::Console_SetPos(0, 0);
    pacman_map.Draw();
    player.Draw();
    for (size_t i = 0; i < enemigos.size(); i++)
    {
        enemigos[i].Draw();
    }
    ConsoleUtils::Console_ClearCharacter({ 0,(short)pacman_map.Height });
    ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::CYAN);
    std::cout << "Puntuacion actual: " << player.points << " Puntuacion pendiente: " << pacman_map.points << std::endl;
    if (win)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::GREEN);
        std::cout << "Has ganado!" << std::endl;
    }
    if (!alive)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::DARK_RED);
        std::cout << "Has perdido..." << std::endl;
    }
    std::cout << "Fotogramas: " << TimeManager::getInstance().frameCount << std::endl;
    std::cout << "Time: " << TimeManager::getInstance().time << std::endl;
    std::cout << "DeltaTime: " << TimeManager::getInstance().deltaTime << std::endl;
    TimeManager::getInstance().NextFrame();
}
