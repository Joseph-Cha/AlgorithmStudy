#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

struct Vertex
{
	// int data
};

vector<Vertex> vertices;
vector<vector<int>> adjacent; // 인접 행렬
vector<int> parent(6, -1);

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));

	adjacent[0][1] = 15;
	adjacent[0][3] = 35;
	
	adjacent[1][0] = 15;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;

	adjacent[3][4] = 5;
	adjacent[5][4] = 5;
}

void Dijikstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};

	// 발견 목록 => Queue가 아닌 점에 유의 
	// 먼저 발견한 곳으로 간다는 보장이 없기 때문에 list로 관리
	list<VertexCost> discovered; 

	// 각 정점별로 지금까지 발견한 최소 거리
	// 이전에 발견한 정점의 최소 거리와 비교를 할 수 있기 때문
	vector<int> best(6, INT32_MAX); 
	
	// 초기화
	discovered.push_back(VertexCost{ here, 0 });
	best[here] = 0;
	parent[here] = here;

	while (discovered.empty() == false)
	{
		// 제일 좋은 후보를 찾는다.
		list<VertexCost>::iterator bestlt;
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin(); it != discovered.end(); it++)
		{
			const int cost = it->cost;

			if (cost < bestCost)
			{
				bestCost = cost;
				bestlt = it;
			}
		}

		int cost = bestlt->cost;
		here = bestlt->vertex;
		discovered.erase(bestlt);

		// 방문? 더 짧은 경로를 뒤늦게 찾았다면 스킵
		if (best[here] < cost)
			continue;

		// 방문!
		for (int there = 0; there < 6; there++)
		{
			// 연결되지 않았다면 스킵.
			if (adjacent[here][there] == -1)
				continue;
			int nextCost = best[here] + adjacent[here][there]; // 현재 최소 비용 + 다음으로 들어가는 비용

			// 더 좋은 경로를 과거에 찾았으면 스킵
			if (nextCost >= best[there])
				continue;

			discovered.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
		}
	}

	int a = 3;
}

int main() 
{
	CreateGraph();
	Dijikstra(0);
}