#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>

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
        Pos { -1, 0 },      // UP       0
        Pos { 0, -1 },      // LEFT     1
        Pos { 1, 0 },       // DOWN     2
        Pos { 0, 1 }        // RIGHT    3
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
        else if (CanGo(pos + front[_dir]))
        {
            // ������ �� �� ����
            pos += front[_dir];
            _path.push_back(pos);
        }
        else
        {
            // ���� �������� 90�� ȸ��
            _dir = (_dir + 1) % DIR_COUNT;
        }
    }

    stack<Pos> s;
    // �ɾ�� ���� ���� 
    for (int i = 0; i < _path.size() - 1; i++)
    {
        // s.empty() == false => ������ �ɾ�� ���� �ִ�
        // s.top() == _path[i + 1] => �ֻ��� ���Ҹ� üũ�ؼ� �°� ������ �����ϴ� ��� ��ġ�ϴ��� üũ
        // ���� ���� => �ǵ��� ���� ���̴� => pop���� �ش� ���� ����
        if (s.empty() == false && s.top() == _path[i + 1])
            s.pop();
        else
            s.push(_path[i]);
    }

    // ������ ���� => ������ ��ǥ�� ���� �������� �־���
    if (_path.empty() == false)
        s.push(_path.back());

    // stack�̶� �Ųٷ� ������ ������ �ٽ� vector�� �־���
    vector<Pos> path;
    while (s.empty() == false)
    {
        path.push_back(s.top());
        s.pop();
    }
    std::reverse(path.begin(), path.end());
    _path = path;
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
    TileType tileType = _board->GetTileType(pos);
    return tileType == TileType::EMPTY;
}