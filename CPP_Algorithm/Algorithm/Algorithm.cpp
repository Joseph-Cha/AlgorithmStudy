#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// DFS (Depth First Search) 깊이 우선 탐색
// BFS (Breadth First Search) 너비 우선 탐색

struct Vertex
{
	// int data
};
 

// 정점 목록
vector<Vertex> vertices;
// 인접 목록
vector<vector<int>> adjacent;

// 방문했는지 여부를 체크 => 순환 반복 방지
vector<bool> discovered;

void CreateGraph()
{
	vertices.reserve(6);
	adjacent = vector<vector<int>>(6);

	// 인접 리스트
	adjacent[0].push_back(1);
	adjacent[0].push_back(3);
	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);
	adjacent[3].push_back(4);
	adjacent[5].push_back(4);

	// 인접 행렬
	//adjacent = vector<vector<int>>
	//{
	//	{ 0, 1, 0, 1, 0, 0},
	//	{ 1, 0, 1, 1, 0, 0},
	//	{ 0, 0, 0, 0, 0, 0},
	//	{ 0, 0, 0, 0, 1, 0},
	//	{ 0, 0, 0, 0, 0, 0},
	//	{ 0, 0, 0, 0, 1, 0},
	//};
}

void Bfs(int here)
{

	// 누구에 의해서 발견 되었는지
	vector<int> parent(6, -1);

	// 시작점에서 얼만큼 떨어져 있는지?
	vector<int> distance(6, -1);

	// 내가 지금 발견한 순서를 저장 
	queue<int> q;
	q.push(here);
	discovered[here] = true;

	parent[here] = here;
	distance[here] = 0;
	
	while (q.empty() == false)
	{
		// 다음에 방문할 정점
		here = q.front();
		q.pop();
		
		cout << "Visited : " << here << endl;

		// adjacent[here] : 현재 위치와 인접한 정점
		for (int there : adjacent[here])
		{
			// 이미 발견한 곳이면 return
			if (discovered[there])
				continue;

			// 처음 발견
			q.push(there);
			discovered[there] = true;

			// there는 here가 발견했다.
			parent[there] = here;

			// there의 거리가 here를 기준으로 1씩 늘어나기 때문
			distance[there] = distance[here] + 1;
		}
	}

	int a = 3;
}

void BfsAll()
{
	for (int i = 0; i < 6; i++)
		if (discovered[i] == false)
			Bfs(i);
}

int main()
{
	CreateGraph();
	discovered = vector<bool>(6, false);

	Bfs(0);
}