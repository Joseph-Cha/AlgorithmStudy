#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
    _pos = board->GetEnterPos();
    _board = board;

    Pos pos = _pos;

    _path.clear();
    _path.push_back(pos);

    // ������ �����ϱ� ������ ��� ����
    Pos dest = board->GetExitPos();

    // ���� ���� �ٶ󺸴� ������ �� �� �� ĭ ������ ���� ��ǥ�� ���� �� ���
    Pos front[4] =
    {
        //     y, x
        Pos { -1, 0 },      // UP
        Pos { 0, -1 },      // LEFT
        Pos { 1, 0 },       // DOWN
        Pos { 0, 1 }        // RIGHT
    };

    while (pos != dest)
    {
        // 1. ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ��� Ȯ��
        // ���������� ȸ�� ���� �� ��ġ ���
        int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
        if (CanGo(pos + front[newDir]))
        {
            // ������ �������� 90�� ȸ��
            _dir = newDir;
            // ������ �� �� ����
            pos += front[_dir];
            _path.push_back(pos);
        }
        // 2. ���� �ٶ󺸴� ������ �������� ������ �� �ִ��� Ȯ��
        else if(CanGo(pos + front[_dir]))
        {
             // ������ �� �� ����
            pos += front[_dir];
            _path.push_back(pos);
        }
        else
        {
            // ���� �������� 90�� ȸ��
            _dir = (_dir + 1) % DIR_DOWN;
            /*
            switch (_dir)
            {
            case DIR_UP:
                _dir = DIR_LEFT;
                break;
            case DIR_LEFT:
                _dir = DIR_DOWN;
                break;
            case DIR_DOWN:
                _dir = DIR_RIGHT;
                break;
            case DIR_RIGHT:
                _dir = DIR_UP;
                break;
            default:
                break;
            }
            */
        }
    }
}

void Player::Update(uint64 deltaTick)
{
    if (_pathIndex >= _path.size())
        return;
    _sumTick += deltaTick;

    // 100 ������ �̵�
    if (_sumTick >= MOVE_TICK)
    {
        _sumTick = 0;
        // _path�� �̵��� ��ΰ� ��� ����Ǿ� �ֱ� ������ 
        // ���� �ϳ��� �����ͼ� ���� �÷��̾ �̵��ؾ��� ��ǥ�� �־��ش�.
        _pos = _path[_pathIndex];
        _pathIndex++;
    }
}

bool Player::CanGo(Pos pos)
{
    TileTpye tileType = _board->GetTileType(pos);
    return tileType == TileTpye::EMPTY;
}
