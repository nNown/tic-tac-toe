#include <game.h>

int main(void) {
    while(GameEntity::GameInstance()->GameState()) {
        GameEntity::GameInstance()->ExecuteInput();
        GameEntity::GameInstance()->Board().Draw();
        Sleep(250);
    }
    return 0;
}