#pragma once

#include <array>
#include <iostream>
#include <windows.h>

#include <board.h>
#include <player.h>

#define PressedKeyMask 0x8000

class GameEntity {
    private:
        static GameEntity* _gameInstance;
        std::array<PlayerEntity, 2> _players;
        BoardEntity _board;
        bool _gameState;
        bool _turn;
        GameEntity();

    public:
        bool CheckRules();
        void ExecuteInput();
        const PlayerEntity& Player() const;
        const bool& GameState() const;
        void GameState(const bool& gameState);
        const bool& Turn() const;
        void Turn(const bool& turn);
        BoardEntity& Board();

        static GameEntity* GameInstance();
};