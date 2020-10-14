#include <game.h>

GameEntity* GameEntity::_gameInstance = nullptr;

bool GameEntity::CheckRules() {
    char playerLine[4] = { this->Player().Sign(), this->Player().Sign(), this->Player().Sign(), 0 };
    for(unsigned int i = 0; i < this->Board().Grid().size(); i++) {
        char horizontalLine[4] = { 0 };
        for(unsigned int j = 0; j < this->Board().Grid()[i].size(); j++) {
            horizontalLine[j] = this->Board().Grid()[i][j];
            playerLine[j] = this->Player().Sign();
        }
        if(!strcmp(horizontalLine, playerLine)) return true;
    }

    for(unsigned int i = 0; i < this->Board().Grid().size(); i++) {
        char verticalLine[4] = { 0 };
        for(unsigned int j = 0; j < this->Board().Grid()[i].size(); j++) {
            verticalLine[j] = this->Board().Grid()[j][i];
            playerLine[j] = this->Player().Sign();
        }
        if(!strcmp(verticalLine, playerLine)) return true;
    }

    char diagonalLine[4] = { this->Board().Grid()[0][0], this->Board().Grid()[1][1], this->Board().Grid()[2][2], 0 };
    char secondDiagonalLine[4] = { this->Board().Grid()[0][2], this->Board().Grid()[1][1], this->Board().Grid()[2][0], 0 };

    if(!strcmp(diagonalLine, playerLine)) return true;
    if(!strcmp(secondDiagonalLine, playerLine)) return true;

   return false;
}

void GameEntity::ExecuteInput() {
    if(GetKeyState(VK_LEFT) & PressedKeyMask || GetKeyState(0x41) & PressedKeyMask) { 
        auto CursorPosition = this->Board().CursorPosition();
        if(CursorPosition[1] == 0) {
            CursorPosition[1] = 2;
        } else {
            CursorPosition[1]--;
        }
        this->Board().CursorPosition(CursorPosition);
    }
    else if(GetKeyState(VK_UP) & PressedKeyMask || GetKeyState(0x57) & PressedKeyMask) { 
        auto CursorPosition = this->Board().CursorPosition();
        if(CursorPosition[0] == 0) {
            CursorPosition[0] = 2;
        } else {
            CursorPosition[0]--;
        }
        this->Board().CursorPosition(CursorPosition);
    }
    else if(GetKeyState(VK_RIGHT) & PressedKeyMask || GetKeyState(0x44) & PressedKeyMask) {
        auto CursorPosition = this->Board().CursorPosition();
        if(CursorPosition[1] == 2) {
            CursorPosition[1] = 0;
        } else {
            CursorPosition[1]++;
        }
        this->Board().CursorPosition(CursorPosition);
    }
    else if(GetKeyState(VK_DOWN) & PressedKeyMask || GetKeyState(0x53) & PressedKeyMask) {
        auto CursorPosition = this->Board().CursorPosition();
        if(CursorPosition[0] == 2) {
            CursorPosition[0] = 0;
        } else {
            CursorPosition[0]++;
        }
        this->Board().CursorPosition(CursorPosition);
    }
    else if(GetKeyState(VK_ESCAPE) & PressedKeyMask) { 
        this->GameState(false);
    }
    else if(GetKeyState(VK_SPACE) & PressedKeyMask) {
        if(this->Board().PlayerAction(this->Player())) {
            if(this->CheckRules()) {
                this->GameState(false);
                std::cout << this->Player().Sign() << " Won";
            }
            this->Turn(!this->Turn());
        }
    }
}

const PlayerEntity& GameEntity::Player() const {
    if(this->Turn()) {
        return this->_players[0];
    }

    return this->_players[1];
}

const bool& GameEntity::GameState() const { return this->_gameState; }
void GameEntity::GameState(const bool& gameState) { this->_gameState = gameState; }
const bool& GameEntity::Turn() const { return this->_turn; }
void GameEntity::Turn(const bool& turn) { this->_turn = turn; }
BoardEntity& GameEntity::Board() { return this->_board; }

GameEntity::GameEntity() : _players({PlayerEntity('X'), PlayerEntity('O')}), _board(BoardEntity()), _gameState(true), _turn(true) {}

GameEntity* GameEntity::GameInstance() {
    if(_gameInstance == nullptr) {
        _gameInstance = new GameEntity();
    }

    return _gameInstance;
}