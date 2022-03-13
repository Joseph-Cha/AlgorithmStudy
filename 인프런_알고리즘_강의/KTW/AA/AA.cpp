/*
문제)
현수의 컴퓨터가 바이러스에 걸려 영어단어가 뛰어쓰기와 대소문자가 혼합되어 표현된다.
예를 들면 아름다운 이란 뜻을 가지고 있는 beautiful 단어가 “bE au T I fu L” 과 같이
컴퓨터에 표시되고 있습니다. 위와 같이 에러로 표시되는 영어단어를 원래의 표현대로 공백을
제거하고 소문자화 시켜 출력하는 프로그램을 작성하세요.

예시)
bE au T I fu L

beautiful
*/

#include <iostream>
#include <sstream>

using namespace std;

int main() 
{
	//FILE* fp = nullptr;
	//freopen_s(&fp, "input.txt", "rt", stdin);

	char word[100];
	cin.getline(word, 100, '\n');
	string res;
	for (int i = 0; i < strlen(word); i++)
	{
		if (word[i] == ' ')
			continue;

		res += tolower(word[i]);
	}
	cout << res;

	return 0;
}