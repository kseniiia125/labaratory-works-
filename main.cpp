#include <SFML/Graphics.hpp>
#include <Circle.hpp>
#include <Game.hpp>

int main()
{
    mt::Game game(1000, 800, "Game");

    if (!game.Setup(1))
        return -1;

    game.LifeCycle();

    return 0;
}
