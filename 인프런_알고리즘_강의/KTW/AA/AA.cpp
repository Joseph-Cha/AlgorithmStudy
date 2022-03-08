﻿/*
문제)
N(2<=N<=100)명의 나이가 입력됩니다. 이 N명의 사람 중 가장 나이차이가 많이 나는 경우는
몇 살일까요? 최대 나이 차이를 출력하는 프로그램을 작성하세요.

예시)
10
13 15 34 23 45 65 33 11 26 42

54
*/

#include <iostream>

using namespace std;

int main() 
{
	//FILE* fp = nullptr;
	//freopen_s(&fp, "input.txt", "rt", stdin);

	int n, age = 0;
	int max = -2000000000;
	int min = 2000000000;

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> age;
		if (max < age)
			max = age;
		if (min > age)
			min = age;
	}

	cout << max - min;

	return 0;
}