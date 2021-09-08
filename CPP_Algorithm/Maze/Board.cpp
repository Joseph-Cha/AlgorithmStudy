#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "Player.h"

const char* TILE = "■";

Board::Board()
{

}

Board::~Board()
{

}

void Board::Init(int32 size, Player* player)
{
    _size = size;
    _player = player;
    GenerateMap();

}

void Board::Render()
{
    ConsoleHelper::SetCursorPosition(0, 0);
    ConsoleHelper::ShowConsoleCursor(false);

    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            // 벽은 빨강, 빈공간 초록
            ConsoleColor color = GetTileColor( Pos{ y, x } );
            ConsoleHelper::SetCursorColor(color);
            cout << TILE;
        }
        cout << endl;
    }
}

// Binary Tree 미로 생성 알고리즘
// - Maze For Programmers 에서 나온 알고리즘
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

    // 랜덤으로 우측 혹은 아래로 길을 뚫는 작업
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            // 초록색일 때만 실행 => 벽일 때는 실행 x
            if (x % 2 == 0 || y % 2 == 0)
                continue;

            // 우측 가장 마지막과 아래측 가장 마지막 쪽은 안뚫어주도록
            if (y == _size - 2 && x == _size - 2)
                continue;

            // 가로행에서 가장 마지막 벽면이 뚫리는 것을 방지하기 위함
            if (y == _size - 2)
            {
                // 무조건 오른쪽으로 이동
                _tile[y][x + 1] = TileTpye::EMPTY;
                continue;
            }

            // 세로열에서 가장 마지막 벽면이 뚫리는 것을 방지하기 위함
            if (x == _size - 2)
            {
                // 무조껀 아래로 이동
                _tile[y + 1][x] = TileTpye::EMPTY;
                continue;
            }

            const int32 randValue = ::rand() % 2;
            if (randValue == 0)
            {
                // 우측으로 이동
                _tile[y][x + 1] = TileTpye::EMPTY;
            }
            else
            {
                // 아래로 이동
                _tile[y + 1][x] = TileTpye::EMPTY;
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
    if (_player && _player->GetPos() == pos)
        return ConsoleColor::YELLOW;

    if (GetExitPos() == pos)
        return ConsoleColor::BLUE;

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
