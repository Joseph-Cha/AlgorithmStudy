#include <iostream>
#include <vector>

using namespace std;

int main()
{
	//FILE* fp = nullptr;
	//freopen_s(&fp, "input.txt", "rt", stdin);

	int n;
	cin >> n;
	vector<int> a;
	a.resize(n);

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	int max_sum = -1000000;
	int result = 0;
	for (int i = 0; i < n; i++)
	{
		int pre = a[i];
		int sum = 0;
		while (a[i] > 0)
		{
			int b = a[i] % 10;
			sum += b;
			a[i] = a[i] / 10;
		}
		if (max_sum < sum)
		{
			max_sum = sum;
			result = pre;
		}
		else if (max_sum == sum)
		{
			if (result < pre)
				result = pre;
		}
	}

	cout << result;

	return 0;
}