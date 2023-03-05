// http://noi-test.zzstep.com/contest/0x60%E3%80%8C%E5%9B%BE%E8%AE%BA%E3%80%8D%E4%BE%8B%E9%A2%98/6901%20%E9%AA%91%E5%A3%AB%E6%94%BE%E7%BD%AE
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
const int MAXN = 105;
const int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2};
const int dy[8] = {1, -1, 2, -2, 2, -2, 1, -1};

int n, m, t;
bool abd[MAXN][MAXN];
int matchx[MAXN][MAXN], matchy[MAXN][MAXN], ans;
bool vis[MAXN][MAXN];
bool legal(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m && !abd[x][y];
}
bool dfs(int x, int y) {
    for(int k = 0; k < 8; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if(!legal(nx, ny) || vis[nx][ny]) continue;
        vis[nx][ny] = 1;
        if(!matchx[nx][ny] || dfs(matchx[nx][ny], matchy[nx][ny])) {
            matchx[nx][ny] = x, matchy[nx][ny] = y;
            return 1;
        }
    }
    return 0;
}
int main() {
    n = read(), m = read(), t = read();
    ans = n * m;
    for(int i = 1; i <= t; i++) {
        int x = read(), y = read();
        abd[x][y] = 1; ans--;
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(((i + j) & 1) == 0 && !abd[i][j]) {
                memset(vis, 0x00, sizeof vis);
                if(dfs(i, j)) ans--;
            }
    printf("%d\n", ans);
    return 0;
}