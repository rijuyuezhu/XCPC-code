#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

constexpr int MAXN = 5;
constexpr int INF = 0x3f3f3f3f;
int up[MAXN], down[MAXN];
string a, b;

void work() {
    cin >> a >> b;
    for(int i = 0; i < 4; i++) {
        up[i] = (int(b[i]) - int(a[i]) + 10) % 10;
        down[i] = (int(a[i]) - int(b[i]) + 10) % 10;
    }
    int U = 1 << 4;
    int ans = INF;
    for(int s = 0; s < U; s++) {
        for(int t = 0; t < U; t++) {
            for(int i = 0; i < 4; i++)
                if((t >> i) & 1)
                    up[i] += 10, down[i] += 10;
            int ret = 0;
            for(int i = 0; i < 4; i++) {
                if((s >> i) & 1) {
                    if(i == 0 || (~(s >> (i-1)) & 1))
                        ret += up[i];
                    else
                        ret += max(0, up[i] - up[i-1]);
                } else {
                    if(i == 0 || ((s >> (i-1)) & 1))
                        ret += down[i];
                    else
                        ret += max(0, down[i] - down[i-1]);
                }
            }
            for(int i = 0; i < 4; i++)
                if((t >> i) & 1)
                    up[i] -= 10, down[i] -= 10;
            ans = min(ans, ret);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--)
        work();
    return 0;
}
