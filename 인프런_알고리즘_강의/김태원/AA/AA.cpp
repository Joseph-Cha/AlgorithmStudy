// 약수 a의 갯수 => n에서 a의 배수의 갯수 
// ex n == 8
// 1 1			=> 1
// 2 1 1		=> 2
// 3 1 1		=> 2
// 4 1 1 1		=> 3
// 5 1 1		=> 2
// 6 1 1 1 1	=> 4
// 7 1 1		=> 2
// 8 1 1 1 1	=> 4
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
	a.resize(n + 1);

	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j += i)
		{
			a[j]++;
		}

		cout <<  a[i];
		if (i != n)
			cout << " ";
	}

	return 0;
}