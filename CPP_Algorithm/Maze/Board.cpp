#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "Player.h"

const char* TILE = "��";

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
            // ���� ����, ����� �ʷ�
            ConsoleColor color = GetTileColor( Pos{ y, x } );
            ConsoleHelper::SetCursorColor(color);
            cout << TILE;
        }
        cout << endl;
    }
}

// Binary Tree �̷� ���� �˰���
// - Maze For Programmers ���� ���� �˰���
void Board::GenerateMap()
{
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            // �ܰ��� ���
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

    // �������� ���� Ȥ�� �Ʒ��� ���� �մ� �۾�
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            // �ʷϻ��� ���� ���� => ���� ���� ���� x
            if (x % 2 == 0 || y % 2 == 0)
                continue;

            // ���� ���� �������� �Ʒ��� ���� ������ ���� �ȶվ��ֵ���
            if (y == _size - 2 && x == _size - 2)
                continue;

            // �����࿡�� ���� ������ ������ �ո��� ���� �����ϱ� ����
            if (y == _size - 2)
            {
                // ������ ���������� �̵�
                _tile[y][x + 1] = TileTpye::EMPTY;
                continue;
            }

            // ���ο����� ���� ������ ������ �ո��� ���� �����ϱ� ����
            if (x == _size - 2)
            {
                // ������ �Ʒ��� �̵�
                _tile[y + 1][x] = TileTpye::EMPTY;
                continue;
            }

            const int32 randValue = ::rand() % 2;
            if (randValue == 0)
            {
                // �������� �̵�
                _tile[y][x + 1] = TileTpye::EMPTY;
            }
            else
            {
                // �Ʒ��� �̵�
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
