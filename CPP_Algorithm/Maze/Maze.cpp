#include <iostream>
#include "pch.h"
#include "ConsoleHelper.h"
#include "Board.h"

Board board;

int main()
{
    board.Init(25);

    uint64 lastTick = 0;
    while (true)
    {
        // 고정 프레임 => 1초 동안 고정된 프레임으로 동작
        // 변동 프레임 => 1초 동안 변동된 프레임으로 동작
#pragma region 프레임 관리
        // 현재 시간
        const uint64 currnectTick = ::GetTickCount64();
        // 현재 시간 - 이전 시간 = 경과시간
        const uint64 deltaTick = currnectTick - lastTick;
        lastTick = currnectTick;
#pragma endregion


        // 입력

        // 로직

        // 렌더링
        board.Render();

    }
}