### 구조체를 이용한 STL vector 정렬

``` Cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Loc {
    int x, y, z;
    Loc(int a, int b, int c) {
        x = a;
        y = b;
        z = c;
    }
    bool operator<(const Loc& b) const{
        //return x < b.x; // 앞에가 작은 값 -> 오른차순 정렬
        if (x != b.x) return x < b.x;
        if (y != b.y) return y < b.y;
        if (z != b.z) return z < b.z; // x가 값을 때 y를 기준으로, y마저 같을 때 z를 기준으로
    }
};

int main() {
    vector<Loc> XY;
    XY.push_back(Loc(2, 3, 5));
    XY.push_back(Loc(3, 6, 7));
    XY.push_back(Loc(2, 3, 1));
    XY.push_back(Loc(5, 2, 3));
    XY.push_back(Loc(3, 1, 6));
    for (auto pos : XY) cout << pos.x << " " << pos.y << " " << pos.z << endl;

    cout << endl;

    sort(XY.begin(), XY.end()); // operator overriding을 통해 x를 기준으로 정렬
    for (auto pos : XY) cout << pos.x << " " << pos.y << " " << pos.z << endl;
    // 2 3 1
    // 2 3 5
    // 3 1 6
    // 3 6 7
    // 5 2 3
    return 0;
}
```

### 구조체와 vector를 사용해서 자료를 정리하는 방법
- 좌표 정렬 vector & pair를 사용
- 3개의 값이 한쌍을 이룰 때, 4개의 값을 한쌍을 이룰 때 정렬하는 방법
- tuple이 아니라 구조체와 vector를 사용해서 구현해 볼 예정
- 구조체를 사용하는 것이 정렬 기준을 설정할 때 편하다