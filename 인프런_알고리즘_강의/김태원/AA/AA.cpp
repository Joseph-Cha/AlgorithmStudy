#include <iostream>
#include <vector>

using namespace std;

int main()
{
	//FILE* fp = nullptr;
	//freopen_s(&fp, "input.txt", "rt", stdin);

	int n;
	cin >> n;
	int count = 0;
	for (int i = 1; i <= n; i++) {
		int a = i;
		while (a > 0) {
			a = a / 10;
			count++;
		}
	}
	cout << count;
	return 0;
}