#pragma once
#include "ConsoleHelper.h"

class Player;

enum
{
    BOARD_MAX_SIZE = 100
};

enum class TileTpye
{
    // 아무것도 아님
    NONE = 0,
    // 갈 수 있는 길
    EMPTY,
    // 벽
    WALL
};

class Board
{
public:
    Board();
    ~Board();

    void            Init(int32 size, Player* player);
    void            Render();

    void            GenerateMap();
    TileTpye        GetTileType(Pos pos);
    ConsoleColor    GetTileColor(Pos pos);

    // 시작점
    Pos             GetEnterPos() { return Pos{ 1, 1 }; }
    // 출구
    Pos             GetExitPos() { return Pos{ _size - 2, _size - 2 }; }

private:    
    TileTpye        _tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
    int32           _size = 0;
    Player*         _player = nullptr;
};

