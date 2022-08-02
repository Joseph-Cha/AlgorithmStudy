### STL map 자료구조 활용


#### 특정 단어가 입력 되었을 때 가장 많이 사용된 알파뱃 출력
* map은 기본적으로 레드 블랙 트리로 이루어져 있다.

``` Cpp
#include <iostream>
#include <fstream>
#include <map>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    ifstream cin;
    cin.open("input.txt");
    
    map<char, int> ch;
    map<char, int>::iterator it;
    char a[100];
    cin >> a;
    for (int i = 0; a[i] != '\0'; i++) {
        // key: 알파뱃
        // value: 알파뱃 갯수
        ch[a[i]]++; 
    }
    
    for (it = ch.begin(); it != ch.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }

    return 0;
}
```

#### 여러 단어 중 가장 많은 단어 출력
``` Cpp
#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    ifstream cin;
    cin.open("input.txt");
    
    map<string, int> ch;
    map<string, int>::iterator it;
    string a;
    int n = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        ch[a]++;
    }
    
    int max = 0;
    string res;
    for (it = ch.begin(); it != ch.end(); it++) {
        if (it->second > max) {
            max = it->second;
            res = it->first;
        }
    }

    return 0;
}
```