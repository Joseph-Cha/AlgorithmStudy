#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>

void Player::Init(Board* board)
{
    _pos = board->GetEnterPos();
    _board = board;

    //RightHand();
    //Bfs();
    AStar();
}

void Player::Update(uint64 deltaTick)
{
    if (_pathIndex >= _path.size())
    {
        _board->GenerateMap();
        Init(_board);
        return;
    }

    _sumTick += deltaTick;
    if (_sumTick >= MOVE_TICK)
    {
        _sumTick = 0;

        _pos = _path[_pathIndex];
        _pathIndex++;
    }
}

bool Player::CanGo(Pos pos)
{
    TileType tileType = _board->GetTileType(pos);
    return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
    Pos pos = _pos;

    _path.clear();
    _path.push_back(pos);

    // 목적지 도착하기 전에는 계속 실행
    Pos dest = _board->GetExitPos();

    Pos front[4] =
    {
        Pos { -1, 0},    // UP
        Pos { 0, -1},    // LEFT
        Pos { 1, 0},    // DOWN
        Pos { 0, 1},    // RIGHT
    };

    while (pos != dest)
    {
        // 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인.
        int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
        if (CanGo(pos + front[newDir]))
        {
            // 오른쪽 방향으로 90도 회전.
            _dir = newDir;
            // 앞으로 한 보 전진.
            pos += front[_dir];

            _path.push_back(pos);
        }
        // 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인.
        else if (CanGo(pos + front[_dir]))
        {
            // 앞으로 한 보 전진.
            pos += front[_dir];

            _path.push_back(pos);
        }
        else
        {
            // 왼쪽 방향으로 90도 회전.
            _dir = (_dir + 1) % DIR_COUNT;
        }
    }

    stack<Pos> s;

    for (int i = 0; i < _path.size() - 1; i++)
    {
        if (s.empty() == false && s.top() == _path[i + 1])
            s.pop();
        else
            s.push(_path[i]);
    }

    // 목적지 도착
    if (_path.empty() == false)
        s.push(_path.back());

    vector<Pos> path;
    while (s.empty() == false)
    {
        path.push_back(s.top());
        s.pop();
    }

    std::reverse(path.begin(), path.end());

    _path = path;
}

void Player::Bfs()
{
    Pos pos = _pos;

    // 목적지 도착하기 전에는 계속 실행
    Pos dest = _board->GetExitPos();

    Pos front[4] =
    {
        Pos { -1, 0},    // UP
        Pos { 0, -1},    // LEFT
        Pos { 1, 0},    // DOWN
        Pos { 0, 1},    // RIGHT
    };

    const int32 size = _board->GetSize();
    vector<vector<bool>> discovered(size, vector<bool>(size, false));

    //vector<vector<Pos>> parent;
    // parent[A] = B; -> A는 B로 인해 발견함
    map<Pos, Pos> parent;

    queue<Pos> q;
    q.push(pos);
    discovered[pos.y][pos.x] = true;
    parent[pos] = pos;

    while (q.empty() == false)
    {
        pos = q.front();
        q.pop();

        // 방문!
        if (pos == dest)
            break;

        for (int32 dir = 0; dir < 4; dir++)
        {
            Pos nextPos = pos + front[dir];
            // 갈 수 있는 지역은 맞는지 확인.
            if (CanGo(nextPos) == false)
                continue;
            // 이미 발견한 지역인지 확인.
            if (discovered[nextPos.y][nextPos.x])
                continue;

            q.push(nextPos);
            discovered[nextPos.y][nextPos.x] = true;
            parent[nextPos] = pos;
        }
    }

    _path.clear();

    // 거꾸로 거슬러 올라간다
    pos = dest;

    while (true)
    {
        _path.push_back(pos);

        // 시작점은 자신이 곧 부모이다
        if (pos == parent[pos])
            break;

        pos = parent[pos];
    }

    std::reverse(_path.begin(), _path.end());
}

struct PQNode
{
    bool operator<(const PQNode& other) const { return f < other.f; }
    bool operator>(const PQNode& other) const { return f > other.f; }

    int32    f; // f = g + h
    int32    g; 
    Pos        pos;
};

void Player::AStar()
{
    // 점수 매기기
    // F = G + H
    // F = 최종 점수(작을 수록 좋음, 경로에 따라 달라짐)
    // G = 시작점에서 해당 좌표까지 이동하는데 드는 비용(작을 수록 좋음, 경로에 따라 달라짐)
    // H = 목적지에서 얼마나 가까운지 (작을 수록 좋음, 고정)

    Pos start = _pos;
    Pos dest = _board->GetExitPos();

    enum
    {
        // DIR_COUNT를 8로 해주게 되면 대각선도 고려를 해서 
        // 경로를 찾아준다.
        DIR_COUNT = 8
    };

    Pos front[] =
    {
        Pos { -1, 0},        // UP
        Pos { 0, -1},        // LEFT
        Pos { 1, 0},        // DOWN
        Pos { 0, 1},        // RIGHT
        Pos { -1, -1 },        // UP_LEFT
        Pos { 1, -1},        // DOWN_LEFT
        Pos { 1, 1 },        // DOWN_RIGHT
        Pos { -1, 1 }        // UP_RIGHT
    };

    // 이동할 때 드는 비용
    // 상하좌우의 경우는 10 
    // 대각선으로 이동할 경우는 14 (10 * 1.4(루트 2))
    int32 cost[] =
    {
        10,    // UP
        10, // LEFT
        10, // DOWN
        10, // RIGHT
        14,    // 4사분면
        14, // 3사분면
        14, // 2사분면
        14, // 1사분면
    };

     const int32 size = _board->GetSize();

    // ClosedList
    // close[y][x] -> (y, x)에 방문 했는지 여부
    vector<vector<bool>> closed(size, vector<bool>(size, false));

    // best[y][x] -> 지금까지 (y, x)에 대한 가장 좋은 비용 (작을 수록 좋음)
    vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

    // 부모 추적 용도
    map<Pos, Pos> parent;

    // 1) 예약(발견) 시스템 구현
    // 내가 이리저리 어떤 정점을 방문할 때마다 인접한 즉 연결되어 있는 다른 정점들을 발견해서 
    // 새로 발견해서 그 정점에 대한 cost를 계산해서 예약을 해준다.
    // 그리고 루프를 돌면서 예약된 경로 중에서 가장 좋은 후보를 가지고
    // 방문을 하게 된다.
    // 이미 더 좋은 경로를 찾았다면 스킵
    
    // OpenList => 지금까지 예약된 데이터를 관리하는 자료구조
    // 이것을 어떤 방식으로 딱히 상관은 없지만 지금은 priority_queue를 사용할 예정
    // 방문을 끝낸 얘들은 ClosedList로 관리를 해주고
    // 방문은 하지 않았지만 발견은 한 상태를 OpenList에 해당 
    priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
    
    // 2) 뒤늦게 더 좋은 경로가 발견될 수 있음 -> 예외 처리 필수
    // openList에서 찾아서 제거한다거나
    // pq에서 pop을 한 다음에 무시한다거나
    // 위의 둘 중 하나를 선택할 수 있다.
    // 지금 우리 같은 경우 Priorty Queue 자체에서 최선에 해당하는 데이터를 중간에 꺼내서
    // 조작을 하는 것은 굉장히 힘들기 때문에 설령 미리 예약된 후보가 
    // 좋은 케이스가 아니더라도 일단을 꺼내서 
    // closed를 이용한 방법 또는 best를 이용하는 방법을 통해 걸러주는 방법으로 구현함

    // 초기값 
    {
        int32 g = 0;
        // y의 거리와 x의 거리를 더한 값에 가중치 10을 둬서(cost를 10의 배수로 두었기 때문에) 계산을 해준다.
        int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
        pq.push(PQNode{ g + h, g, start });
        best[start.y][start.x] = g + h;
        parent[start] = start;
    }

    while (pq.empty() == false)
    {
        // 제일 좋은 후보를 찾는다.
        PQNode node = pq.top();
        pq.pop();

        // 동일한 좌표를 여러 경로로 찾아서, 
        // 더 빠른 경로로 인해서 이미 방문(closed)된 경우 skip
        // 이 부분을 빼면 드라군이 왔다갔다 하는 현상이 일어남

        // [선택]
        // 1) closed를 이용한 방법
        // 해당 포지션이 closed일 때
        // => 내가 먼저 경로를 찾아서 PQ에 넣어두었는데 
        // => 가다보니 더 좋은 경로를 찾아서 새치기를 하는 현상이라고 이해하면 될 듯
        if (closed[node.pos.y][node.pos.x])
            continue;
        // 2) best를 이용하는 방법
        // best의 y,x 값이 현재 노드의 f값 보다 작으면 skip
        // => 기껏 best node에 등록을 했지만 누군가가 나보다 더 좋은 값을 가지고 있다는 의미
        if (best[node.pos.y][node.pos.x] < node.f)
            continue;

        // 방문
        closed[node.pos.y][node.pos.x] = true;

        // 목적지에 도착했으면 바로 종료
        if (node.pos == dest)
            break;
        // Q) 내가 방문을 한 다음에 그 다음에 더 우수한 후보를 찾을 수 있나요?
        // => 존재할 수가 없음

        for (int32 dir = 0; dir < DIR_COUNT; dir++)
        {
            Pos nextPos = node.pos + front[dir];
            
            // 잘 수 있는 지역은 맞는지 확인 => false라면 갈 필요가 없다
            if (CanGo(nextPos) == false)
                continue;
            // [선택] 이미 방문한 곳이면 스킵 => 위에서 이미 한번 걸렀기 때문에 선택
            if (closed[nextPos.y][nextPos.x])
                continue;

            // 비용 계산
            // node.g => 이전 우리가 nextPos를 발견하기전 이전 parent에 해당
            // 즉 이전 좌표에서 다음 좌표로 이동하는데 드는 비용 계산
            // h => 목적지를 기준으로 얼마만큼 떨어져 있느냐에 대한 계산 
            // 따라서 g + h가 가장 최소가 되는 값이 가장 좋은 경우의 수
            int32 g = node.g + cost[dir];
            int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
            // 다른 경로에서 더 빠른 길을 찾았으면 스킵
            if (best[nextPos.y][nextPos.x] <= g + h)
                continue;

            // 여기까지 오게 되면 내가 지금까지 찾은 경로보다
            // 무조껀 우수한 후보이다.

            // 예약 진행 
            best[nextPos.y][nextPos.x] = g + h;
            pq.push(PQNode{ g + h, g, nextPos });
            parent[nextPos] = node.pos;
        }
    }

    // 거꾸로 거슬러 올라간다
    Pos pos = dest;
    _path.clear();
    _pathIndex = 0;

    while (true)
    {
        _path.push_back(pos);

        // 시작점은 자신이 곧 부모이다
        if (pos == parent[pos])
            break;

        pos = parent[pos];
    }

    std::reverse(_path.begin(), _path.end());
}