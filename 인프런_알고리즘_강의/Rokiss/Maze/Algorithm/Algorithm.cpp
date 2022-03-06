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
void SelectionSort(vector<int>& v)
{
	const int n = (int)v.size();

	// O(N^2)
	for (int i = 0; i < n - 1; i++)
	{
		int bestIdx = i;
		for (int j = i + 1; j < n; j++)
		{
			if (v[j] < v[bestIdx])
				bestIdx = j;
		}
		// 교환
		int tmp = v[i];
		v[i] = v[bestIdx];
		v[bestIdx] = tmp;
	}
}

// 3) 삽입 정렬 (Insertion Sort)
// 코딩 면접에서 자주 나오는 컨셉
// 문자열을 다룰 때 뒷부분부터 종종 다루게 된다 => 이때 주로 사용
// 정렬을 해야하는 데이터를 하나씩 뽑아서 
// 정렬이 되어 있는 데이터에 삽입을 하는 컨셉
// 삽입을 할 때 정렬 방식에 유의 해야 한다.
// 그리고 정렬이 되어 있는 데이터에 삽입하기 위해서 
// vector를 하나 새로 만들어야하는 것까지는 아니다.
void InsertSort(vector<int>& v)
{
	const int n = (int)v.size();
	// O(N^2)
	for (int i = 1; i < n; i++)
	{
		// 삽입을 해야할 데이터
		int insertData = v[i];
		
		// 어느 위치에 삽입을 해야하는지 체크
		int j;

		// 끝에서부터 역순서로 하나씩 체크
		for (j = i - 1; j >= 0; j--)
		{
			// 삽입을 해야하는 데이터가 j에 있는 데이터보다 작으면
			// => i보다 왼쪽 편에 있는 데이터들을 하나씩 체크하면서 이전에 있는 데이터를 오른쪽으로 이동시켜준다.
			if (v[j] > insertData)
				v[j + 1] = v[j];
			else
				break;
		}
		// 삽입을 해야할 위치에 insertData를 넣어준다.
		v[j + 1] = insertData;
	}
}

int main()
{
	vector<int> v{ 1, 5, 2, 4, 7, 3 };

	//BubbleSort(v);
	SelectionSort(v);

}