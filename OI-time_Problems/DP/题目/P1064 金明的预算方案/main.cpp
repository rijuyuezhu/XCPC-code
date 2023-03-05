// https://www.luogu.com.cn/problem/P1064
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
const int MAXN = 3.2e4 + 5;
const int MAXM = 65;
int n, m;
int v[MAXM], p[MAXM], q[MAXM], son[MAXM][3];
int f[MAXN];
int V(int u, int i) {return v[son[u][i]];}
int W(int u, int i) {return v[son[u][i]] * p[son[u][i]];}
int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; i++) {
        v[i] = read(), p[i] = read(), q[i] = read();
        son[i][0] = i;
        if(q[i]) {
            int u = q[i];
            if(son[u][1]) son[u][2] = i;
            else son[u][1] = i;
        }
    }
    for(int i = 1; i <= m; i++) if(!q[i]) {
        for(int j = n; j >= 0; j--) {
            if(j >= V(i, 0))
                f[j] = max(f[j], f[j - V(i, 0)] + W(i, 0));
            if(j >= V(i, 0) + V(i, 1))
                f[j] = max(f[j], f[j - V(i, 0) - V(i, 1)] + W(i, 0) + W(i, 1));
            if(j >= V(i, 0) + V(i, 2))
                f[j] = max(f[j], f[j - V(i, 0) - V(i, 2)] + W(i, 0) + W(i, 2));
            if(j >= V(i, 0) + V(i, 1) + V(i, 2))
                f[j] = max(f[j], f[j - V(i, 0) - V(i, 1) - V(i, 2)] + W(i, 0) + W(i, 1) + W(i, 2));
        }
    }
    printf("%d\n", f[n]);
    return 0;
}