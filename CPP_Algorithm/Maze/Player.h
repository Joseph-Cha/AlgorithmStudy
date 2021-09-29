#pragma once

class Board;

class Player
{
    enum
    {
        MOVE_TICK = 100
    };
public:
    void        Init(Board* board);
    // 매프레임 마다 Update 를 돌려서 이전 프레임 대비 경과시간을 deltaTick에 넣어서
    // 계속 업데이트가 됨
    void        Update(uint64 deltaTick);

    void        SetPos(Pos pos) { _pos = pos; }
    Pos         GetPos() { return _pos; }

    bool        CanGo(Pos pos);

private:
    Pos         _pos = {};
    int32       _dir = DIR_UP;
    Board*      _board = nullptr;

    // 내가 지금까지 가야하는 길을 저장
    vector<Pos> _path;

    // 내가 현재 경로를 기준으로 어디까지 이동했는지 추적
    uint32      _pathIndex = 0;
    uint64      _sumTick = 0;
};