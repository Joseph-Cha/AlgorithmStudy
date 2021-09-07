#include <iostream>
#include "pch.h"
#include "ConsoleHelper.h"

int main()
{
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

        ConsoleHelper::SetCursorPosition(0, 0);
        ConsoleHelper::ShowConsoleCursor(false);
        ConsoleHelper::SetCursorColor(ConsoleColor::RED);

        const char* TILE = "■";

        for (int32 y = 0; y < 25; y++)
        {
            for (int32 x = 0; x < 25; x++)
            {
                cout << TILE;
            }
            cout << endl;
        }
    }
}