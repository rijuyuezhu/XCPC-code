#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
constexpr int MAXN = 4e5 + 5;

int n;
char s[MAXN];

void work() {
    cin >> (s+1);
    n = strlen(s+1);
    for(int i = 1; i <= n; i++)
        s[i+n] = s[i];
    int maxlen = 0, nowlen = 0;
    for(int i = 1; i <= 2 * n; i++) {
        if(s[i] == '1')
            nowlen++;
        else
            nowlen = 0;
        maxlen = max(maxlen, nowlen);
    }
    if(maxlen > n) {
        cout << 1ll * n * n << '\n';
        return ;
    }
    int k = (1 + maxlen) / 2;
    cout << 1ll * k * (1 + maxlen - k) << '\n';
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
