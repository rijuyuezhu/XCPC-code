// https://www.luogu.com.cn/problem/P1757
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
const int MAXN = 1005;
int m, n;
struct Graph {
    int v, w, nxt;
}g[MAXN];
int head[MAXN], cnt;
void addg(int v, int w, int c) {
    g[++cnt].v = v; g[cnt].w = w; g[cnt].nxt = head[c]; head[c] = cnt;
}
int maxc;
int f[MAXN];
int main() {
    m = read(); n = read();
    for(int i = 1; i <= n; i++) {
        int w = read(), v = read(), c = read();
        maxc = max(maxc, c);
        addg(v, w, c);
    }
    for(int i = 1; i <= maxc; i++) 
        for(int j = m; j >= 0; j--) 
            for(int k = head[i]; k; k = g[k].nxt) {
                int v = g[k].v, w = g[k].w;
                if(j >= w) f[j] = max(f[j], f[j - w] + v);
            }
    printf("%d", f[m]);
    return 0;
}