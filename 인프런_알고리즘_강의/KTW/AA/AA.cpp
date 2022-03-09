/*
문제)
주민등록증의 번호가 주어지면 주민등록증 주인의 나이와 성별을 판단하여 출력하는 프로그램
을 작성하세요. 주민등록증의 번호는 -를 기준으로 앞자리와 뒷자리로 구분된다.
뒷자리의 첫 번째 수가 1이면 1900년대생 남자이고, 2이면 1900년대생 여자, 3이면 2000년대
생 남자, 4이면 2000년대생 여자이다.
올해는 2019년입니다. 해당 주민등록증 주인의 나이와 성별을 출력하세요.

예시)
780316-2376152

42 W
*/

#include <iostream>
#include <sstream>

using namespace std;

int main() 
{
	//FILE* fp = nullptr;
	//freopen_s(&fp, "input.txt", "rt", stdin);

	string num;

	cin >> num;

	string year = num.substr(0, 2);

	int age = 0;
	stringstream ssint(year);
	ssint >> age;

	if ((22 - age) < 0)
		cout << 22 - age + 100 << " ";
	else
		cout << 22 - age << " ";

	char a = num[7];

	int s = static_cast<int>(a) - 48;

	if (s == 1 || s == 3)
	{
		cout << "M";
	}
	else if (s == 2 || s == 4)
	{
		cout << "W";
	}

	return 0;
}