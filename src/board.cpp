#include <board.h>

std::array<std::array<char, 3>, 3>& BoardEntity::Grid() { return this->_grid; }
const std::array<unsigned int, 2>& BoardEntity::CursorPosition() const { return this->_cursorPosition; }
void BoardEntity::CursorPosition(const std::array<unsigned int, 2>& cursorPosition) { this->_cursorPosition = cursorPosition; }

void BoardEntity::Draw() {
    static const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    CONSOLE_CURSOR_INFO cursorInfo;
    WORD saved_attributes;

    if(!GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) abort();
    saved_attributes = consoleInfo.wAttributes;

    COORD DrawStartingPosition = { (SHORT)0, (SHORT)0 };
    DWORD length = 256;
    DWORD written;

    if(!GetConsoleCursorInfo(hConsole, &cursorInfo)) abort();
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    FillConsoleOutputCharacter(hConsole, TEXT(' '), length, DrawStartingPosition, &written);
    FillConsoleOutputAttribute(hConsole, consoleInfo.wAttributes, length, DrawStartingPosition, &written);

    SetConsoleCursorPosition(hConsole, { 0, 0 });

    for(unsigned int i = 0; i < this->Grid().size(); i++) {
        for(unsigned int j = 0; j < this->Grid()[i].size(); j++) {
            if(i == this->CursorPosition()[0] && j == this->CursorPosition()[1]) {
                SetConsoleTextAttribute(hConsole, 0x0070);
                std::cout << this->Grid()[i][j];
                SetConsoleTextAttribute(hConsole, saved_attributes);
                continue;
            }
            SetConsoleTextAttribute(hConsole, 0x0050);
            std::cout << this->Grid()[i][j];
            SetConsoleTextAttribute(hConsole, saved_attributes);
        }
        std::cout << std::endl;
    }
}

bool BoardEntity::PlayerAction(PlayerEntity player) {
    if(this->Grid()[this->CursorPosition()[0]][this->CursorPosition()[1]] != ' ') return false; 
    this->Grid()[this->CursorPosition()[0]][this->CursorPosition()[1]] = player.Sign();
    return true;
}

BoardEntity::BoardEntity() {
    _cursorPosition = std::array<unsigned int, 2>({0, 0});
    for(auto& row : this->_grid) {
        for(auto& element : row) {
            element = ' ';
        }
    }
}
BoardEntity::~BoardEntity() {}