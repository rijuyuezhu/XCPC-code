// https://www.luogu.com.cn/problem/P2704
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
char readc() {
    char ch = getchar();
    while(ch != 'P' && ch != 'H') ch = getchar();
    return ch;
}
const int MAXN = 100;
const int MAXM = 10;
const int MAXU = (1 << MAXM);

int n, m, U, num[MAXU], mp[MAXN];
int f[MAXU][MAXU][3];
bool check(int x, int l) {
    return !((x & mp[l]) || (x & (x << 1)) || (x & (x << 2)));
}
int main() {
    n = read(); m = read(); U = (1 << m) - 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char ch = readc();
            mp[i] = (mp[i] << 1) + (ch == 'H');//1 is yes, 0 is not
        }
    }
    for(int i = 0; i <= U; i++) {
        int x = i;
        while(x) {
            if(x & 1) num[i]++;
            x >>= 1;
        }
    }
    for(int s = 0; s <= U; s++) 
        if(check(s, 0))
            f[0][s][0] = num[s];
    for(int l = 0; l <= U; l++)
        if(check(l, 0))
            for(int s = 0; s <= U; s++)
                if(check(s, 1) && !(l & s)) 
                    f[l][s][1] = num[s] + num[l];
    for(int i = 2; i < n; i++) 
        for(int l = 0; l <= U; l++)
            if(check(l, i-1))
                for(int s = 0; s <= U; s++)
                    if(check(s, i) && !(l & s))
                        for(int fl = 0; fl <= U; fl++)
                            if(check(fl, i-2) && !(fl & l) && !(fl & s)) {
                                f[l][s][i%3] = max(f[l][s][i%3], f[fl][l][(i-1)%3] + num[s]);
                            }
    int ans = 0;
    for(int l = 0; l <= U; l++)
        for(int s = 0; s <= U; s++)
            ans = max(ans, f[l][s][(n-1)%3]);
    printf("%d\n", ans);
    return 0;
}