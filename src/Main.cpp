#include "game/Game.h"

int main(int argc, char* argv[]) {
    Game game;

    game.Initialise();
    game.Run();
    game.Destroy();

    return 0;
}
