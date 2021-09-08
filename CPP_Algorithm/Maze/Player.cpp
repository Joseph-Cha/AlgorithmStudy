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

    // 목적지 도착하기 전에는 계속 실행
    Pos dest = board->GetExitPos();

    // 내가 현재 바라보는 방향을 알 때 한 칸 앞으로 가는 좌표을 구할 때 사용
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
        else if(CanGo(pos + front[_dir]))
        {
             // 앞으로 한 보 전진
            pos += front[_dir];
            _path.push_back(pos);
        }
        else
        {
            // 왼쪽 방향으로 90도 회전
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
    TileTpye tileType = _board->GetTileType(pos);
    return tileType == TileTpye::EMPTY;
}
