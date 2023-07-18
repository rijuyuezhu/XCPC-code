#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    int cnt = 0;
    for(int i = 0; i < (int)s.length()-4; i++)
        if(s.substr(i, 5) == "edgnb")
            ++cnt;
    cout << cnt << '\n';
    return 0;
}
