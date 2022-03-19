// 10 ~ 15 = 15 - 10 + 1
// 100 150 = 150 - 100 + 1

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
	int temp = n;
	while (n > 0) {
		n = n / 10;
		count++;
	}
	long long sum = 0;
	for (int i = 1; i <= count - 1; i++) {
		sum += i * (9 * (pow(10, i - 1)));
	}

	int a = (temp - pow(10, count - 1) + 1);
	sum += a * count;

	cout << sum;
	return 0;
}