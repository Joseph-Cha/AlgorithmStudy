#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"

const char* TILE = "■";

Board::Board()
{

}

Board::~Board()
{

}

void Board::Init(int32 size)
{
    _size = size;
    GenerateMap();

}

void Board::Render()
{
    ConsoleHelper::SetCursorPosition(0, 0);
    ConsoleHelper::ShowConsoleCursor(false);

    for (int32 y = 0; y < 25; y++)
    {
        for (int32 x = 0; x < 25; x++)
        {
            // 벽은 빨강, 빈공간 초록
            ConsoleColor color = GetTileColor(Pos{ y, x });
            ConsoleHelper::SetCursorColor(color);
            cout << TILE;
        }
        cout << endl;
    }
}

// Binary Tree 미로 생성 알고리즘
// - Maze For Programmers
void Board::GenerateMap()
{
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            // 외각일 경우
            if (x % 2 == 0 || y % 2 == 0)
            {
                _tile[y][x] = TileTpye::WALL;
            }
            else
            {
                _tile[y][x] = TileTpye::EMPTY;
            }
        }
    }
}

TileTpye Board::GetTileType(Pos pos)
{
    if (pos.x < 0 || pos.x >= _size)
        return TileTpye::NONE;
    if (pos.y < 0 || pos.y >= _size)
        return TileTpye::NONE;
    return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
    TileTpye tileType = GetTileType(pos);
    switch (tileType)
    {
    case TileTpye::NONE:
        break;
    case TileTpye::EMPTY:
        return ConsoleColor::GREEN;
        break;
    case TileTpye::WALL:
        return ConsoleColor::RED;
        break;
    default:
        break;
    }
    return ConsoleColor::WHITE;
}
