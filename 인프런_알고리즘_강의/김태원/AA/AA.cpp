/*
문제)
괄호가 입력되면 올바른 괄호이면 “YES", 올바르지 않으면 ”NO"를 출력합니다.
(())() 이것은 괄호의 쌍이 올바르게 위치하는 거지만, (()()))은 올바른 괄호가 아니다.

예시)
(()(()))(()

NO
*/

#include <iostream>
#include <sstream>

using namespace std;

int main() 
{
	//FILE* fp = nullptr;
	//freopen_s(&fp, "input.txt", "rt", stdin);

	char word[30];
	cin >> word;
	int a = 0, b = 0;
	bool success = false;
	if (word[0] != '(' || word[strlen(word) - 1] != ')')
	{
		success = false;
		cout << "NO";
		return 0;
	}

	for (int i = 0; word[i] != '\0'; i++)
	{
		if (word[i] == '(')
			a++;
		else
			b++;
		if (a == b) success = true;
		else success = false;
	}

	success ? cout << "YES" : cout << "NO";
	return 0;
}