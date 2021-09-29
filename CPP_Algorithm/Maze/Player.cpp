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

    // 목적지 도착하기 전에는 계속 실행
    Pos dest = board->GetExitPos();

    // 내가 현재 바라보는 방향을 알 때 한 칸 앞으로 가는 좌표을 구할 때 사용
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
        // 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인
        // 오른쪽으로 회전 했을 때 위치 계산
        int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
        if (CanGo(pos + front[newDir]))
        {
            // 오른쪽 방향으로 90도 회전
            _dir = newDir;
            // 앞으로 한 보 전진
            pos += front[_dir];
            _path.push_back(pos);
        }
        // 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
        else if (CanGo(pos + front[_dir]))
        {
            // 앞으로 한 보 전진
            pos += front[_dir];
            _path.push_back(pos);
        }
        else
        {
            // 왼쪽 방향으로 90도 회전
            _dir = (_dir + 1) % DIR_COUNT;
        }
    }

    stack<Pos> s;
    // 걸어온 길을 복귀 
    for (int i = 0; i < _path.size() - 1; i++)
    {
        // s.empty() == false => 이전에 걸어온 길이 있다
        // s.top() == _path[i + 1] => 최상위 원소를 체크해서 걔가 다음에 가야하는 길과 일치하는지 체크
        // 조건 만족 => 되돌아 가는 중이다 => pop으로 해당 길을 제거
        if (s.empty() == false && s.top() == _path[i + 1])
            s.pop();
        else
            s.push(_path[i]);
    }

    // 목적지 도착 => 목적지 좌표를 가장 마지막에 넣어줌
    if (_path.empty() == false)
        s.push(_path.back());

    // stack이라 거꾸로 나오기 때문에 다시 vector에 넣어줌
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

    // 100 다음에 이동
    if (_sumTick >= MOVE_TICK)
    {
        _sumTick = 0;
        // _path에 이동할 경로가 모두 저장되어 있기 때문에 
        // 값을 하나씩 꺼내와서 현재 플레이어가 이동해야할 좌표로 넣어준다.
        _pos = _path[_pathIndex];
        _pathIndex++;
    }
}

bool Player::CanGo(Pos pos)
{
    TileType tileType = _board->GetTileType(pos);
    return tileType == TileType::EMPTY;
}