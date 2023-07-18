#include <algorithm>
#include <iostream>
using namespace std;

constexpr int MAXB = 30;
constexpr int MAXN = 1e5 + 5;
int n, cnt[MAXB], ans;
void applydec(int B) {
    for(int t = B; t >= 0; t--)
        cnt[t]--;
    for(int t = 0; t < MAXB; t++)
        if(cnt[t] < 0)
            cnt[t] += 2, cnt[t+1]--;
}
void work() {
    cin >> n;
    for(int t = 0; t < MAXB; t++)
        cnt[t] = 0;
    ans = 0;
    for(int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        for(int t = 0; t < MAXB; t++)
            if((v >> t) & 1)
                cnt[t]++;
    }
    while(1) {
        int mxbit = -1, haszero = 0;
        for(int t = MAXB-1; t >= 0; t--) {
            if(cnt[t] > 0) {
                mxbit = t;
                break;
            }
        }
        if(mxbit == -1)
            break;
        if(cnt[mxbit] == 1) {
            for(int t = mxbit - 1; t >= 0; t--)
                if(cnt[t] == 0) {
                    haszero = 1;
                    break;
                } else if(cnt[t] >= 2) 
                    break;
        }
        if(cnt[mxbit] == 1 && haszero)
            applydec(mxbit-1);
        else
            applydec(mxbit);
        ++ans;
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
