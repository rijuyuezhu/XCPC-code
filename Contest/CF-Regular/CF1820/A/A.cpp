#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string s;
int n;
vector<int> pos;

void work() {
    int ans = 0;
    cin >> s;
    n = s.length();
    if(n == 1 && s[0] == '^') {
        cout << 1 << '\n';
        return ;
    }
    pos = vector<int>(n + 1);
    for(int i = 0; i < n; i++) {
        if(s[i] == '_') {
            if((i == 0 || s[i-1] != '^') && !pos[i]) {
                ++ans;
                pos[i] = 1;
            }
            if((i == n-1 || s[i+1] != '^') && !pos[i+1]) {
                ++ans;
                pos[i+1] = 1;
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--)
        work();
    return 0;
}
