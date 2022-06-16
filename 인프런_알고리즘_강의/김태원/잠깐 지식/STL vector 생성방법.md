### STL vector 생성 방법

``` Cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    FILE* fp = nullptr;
    freopen_s(&fp, "input.txt", "rt", stdin);

    vector<int> a;
    a[1] = 5; // a의 첫번째 공간이 아직 없기 때문에 에러 발생

    int n;
    cin >> n;
    vector<int> b(n);
    b[1] = 5; // b에 이미 5개 공간을 만들어 놨기 때문에(메모리 할당이 되었기 때문에) 가능
    cout << a[1] << endl; // 5

    a.push_back(6);
    a.push_back(8);
    a.push_back(11);
    cout << a.size() << endl; // 3
    cout << a[1] << endl;     // 8

     vector<int> c[3];  // vector<int>가 총 3개
     c[0].push_back(1);
     c[0].push_back(3);
     c[0].push_back(5);
     c[1].push_back(2);
     c[1].push_back(4);
     c[1].push_back(6);
     c[2].push_back(7);
     cout << c[1][1] << endl; // 4
     cout << c[2][0] << endl; // 7

     vector<pair<int, int>> graph[3];
     graph[1].push_back({ 3, 5 });  // pair를 { } 초기화로도 생성 가능
     graph[1].push_back({ 4, 7 });
     graph[1].push_back({ 5, 9 });
     graph[2].push_back(make_pair(7, 7));

     cout << graph[2][0].first << " " << graph[2][0].second << endl; // 7, 7
}
```