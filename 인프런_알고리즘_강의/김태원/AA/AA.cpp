#include <iostream>
#include <vector>

using namespace std;

int main()
{
	//FILE* fp = nullptr;
	//freopen_s(&fp, "input.txt", "rt", stdin);
	char n[101];
	cin >> n;
	int a[10] = {0};

	for (int i = 0; n[i] != '\0'; i++) {
		int b = n[i];
		int digit = n[i] - 48;
		a[digit]++;
	}

	int sum = -10;
	int count = 0;
	for (int i = 0; i < 10; i++) {
		if (a[i] > sum) {
			sum = a[i];
			count = i;
		}
		else if (a[i] == sum) {
			if (i > count) {
				sum = a[i];
				count = i;
			}
		}
	}

	cout << count;

	return 0;
}