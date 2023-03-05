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
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int n, m, p[MAXN][MAXN];
bool vis[MAXN][MAXN];
int que[MAXN * MAXN][2], hd, tl;
bool check(int lim) {
    hd = 1; tl = 0;
    memset(vis, 0x00, sizeof vis);
    vis[1][1] = 1; que[++tl][0] = 1, que[tl][1] = 1;
    while(hd <= tl) {
        int x = que[hd][0], y = que[hd++][1];
        for(int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if(nx < 1 || nx > n || ny < 1 || ny > m || p[nx][ny] > lim || vis[nx][ny]) continue;
            vis[nx][ny] = 1;
            que[++tl][0] = nx, que[tl][1] = ny;
        }
    }
    for(int i = 1; i <= m; i++)
        if(!vis[n][i]) return 0;
    return 1;
}
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            p[i][j] = read();
    int l = 0, r = 1000, ans = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) {ans = mid; r = mid - 1;}
        else l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}
