#pragma once
#include "ConsoleHelper.h"
enum
{
    BOARD_MAX_SIZE = 100
};

enum class TileTpye
{
    NONE = 0,
    EMPTY,
    WALL
};

class Board
{
public:
    Board();
    ~Board();

    void            Init(int32 size);
    void            Render();

    void            GenerateMap();
    TileTpye        GetTileType(Pos pos);
    ConsoleColor    GetTileColor(Pos pos);

private:
    TileTpye        _tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
    int32           _size = 0;
};

