#pragma once

class Board;

class Player
{
public:
    void        Init(Board* board);
    // 매프레임 마다 Update를 돌려서 이전 프레임 대비 경과시간을 deltaTick에 넣어서
    // 계속 업데이트가 됨
    void        Update(uint64 deltaTick);

    void        SetPos(Pos pos) { _pos = pos; }
    Pos         GetPos() { return _pos; }

private:
    Pos         _pos = {};
    int32       _dir = DIR_UP;
    Board*      _board = nullptr;
};

