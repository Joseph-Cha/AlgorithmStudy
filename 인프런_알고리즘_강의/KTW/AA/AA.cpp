/*
문제)
자연수 N이 입력되면 1부터 N까지의 수 중 M의 배수합을 출력하는 프로그램을 작성하세요.
*/

#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

int main() 
{
	//FILE* fp = nullptr;
	//freopen_s(&fp, "input.txt", "rt", stdin);

	int n, m, sum = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		if (i % m == 0)
			sum += i;
	}

	cout << sum;

	return 0;
}