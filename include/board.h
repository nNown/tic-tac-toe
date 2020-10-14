#pragma once

#include <array>
#include <iostream>
#include <windows.h>

#include <player.h>

class BoardEntity {
    private:
        std::array<std::array<char, 3>, 3> _grid;
        std::array<unsigned int, 2> _cursorPosition; 
    
    public:
        std::array<std::array<char, 3>, 3>& Grid();
        const std::array<unsigned int, 2>& CursorPosition() const;
        void CursorPosition(const std::array<unsigned int, 2>& cursorPosition);

        void Draw();

        bool PlayerAction(PlayerEntity player);

        BoardEntity();
        ~BoardEntity();
};