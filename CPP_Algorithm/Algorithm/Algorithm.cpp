#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// 오늘의 주제 : 정렬
// 1) 버블 정렬 (Bubble Sort)
void BubbleSort(vector<int>& v)
{
	const int n = (int)v.size();
	// (N - 1) + (N - 2) ... 2 + 1
	// 등차 수열의 합 = N * (N - 1) / 2
	// O(N^2)
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < (n - 1 - i); j++)
		{
			if (v[j] > v[j + 1])
			{
				int tmp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = tmp;
			}
		}
	}
}

// 2) 선택 정렬 (Selection Sort)



// 3) 삽입 정렬 (Insertion Sort)



int main()
{
	vector<int> v{ 1, 5, 2, 4, 7, 3 };


	BubbleSort(v);


}