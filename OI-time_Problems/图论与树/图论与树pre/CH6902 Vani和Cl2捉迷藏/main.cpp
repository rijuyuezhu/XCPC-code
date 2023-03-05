// http://noi-test.zzstep.com/contest/0x60%E3%80%8C%E5%9B%BE%E8%AE%BA%E3%80%8D%E4%BE%8B%E9%A2%98/6902%20Vani%E5%92%8CCl2%E6%8D%89%E8%BF%B7%E8%97%8F
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
const int MAXN = 205;
int n, m, e[MAXN][MAXN], ans, match[MAXN], hid[MAXN], tot;
bool vis[MAXN], succ[MAXN];
bool dfs(int u) {
    for(int v = 1; v <= n; v++) {
        if(!e[u][v] || vis[v]) continue;
        vis[v] = 1;
        if(!match[v] || dfs(match[v])) {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}
int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; i++) {
        int x = read(), y = read();
        e[x][y] = 1;
    }
    //for(int i = 1; i <= n; i++) e[i][i] = 1;
    for(int k = 1; k <= n; k++)
      for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            e[i][j] |= (e[i][k] & e[k][j]);
    //for(int i = 1; i <= n; i++) e[i][i] = 0;
    ans = n;
    for(int i = 1; i <= n; i++) {
        fill(vis + 1, vis + 1 + n, 0);
        if(dfs(i)) ans--;
    }
    printf("%d\n", ans);
    for(int i = 1; i <= n; i++) succ[match[i]] = 1;
    for(int i = 1; i <= n; i++)
        if(!succ[i])
            hid[++tot] = i;
    fill(vis + 1, vis + 1 + n, 0);
    int mdy = 1;
    while(mdy) {
        mdy = 0;
        for(int i = 1; i <= ans; i++)
            for(int j = 1; j <= n; j++)
                if(e[hid[i]][j]) vis[j] = 1;
        for(int i = 1; i <= ans; i++)
            if(vis[hid[i]]) {
                mdy = 1;
                while(vis[hid[i]]) hid[i] = match[hid[i]];
            }
    }
    for(int i = 1; i <= ans; i++) printf("%d%c", hid[i], i == ans ? '\n' : ' ');
    return 0;
}