//http://noi-test.zzstep.com/contest/0x60%E3%80%8C%E5%9B%BE%E8%AE%BA%E3%80%8D%E4%BE%8B%E9%A2%98/6801%20%E6%A3%8B%E7%9B%98%E8%A6%86%E7%9B%96
/*
二分图的原因
把格子看成节点，可以放置的骨牌看成边
交叉染成黑白色（是二分图）
1要素：每个节点只能与一个边相连(只能被一个骨牌覆盖)
0要素：二分图（一个骨牌不能覆盖两个格子）
*/
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
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int n, t, ans;
int match[MAXN][MAXN][2];
bool abd[MAXN][MAXN], vis[MAXN][MAXN];
bool legal(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n && !abd[x][y];
}
bool dfs(int x, int y) {
    for(int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if(!legal(nx, ny) || vis[nx][ny]) continue;
        vis[nx][ny] = 1;
        if(!match[nx][ny][0] || dfs(match[nx][ny][0], match[nx][ny][1])) {
            match[nx][ny][0] = x; match[nx][ny][1] = y;
            return 1;
        }
    }
    return 0;
}
int main() {
    n = read(); t = read();
    for(int i = 1, x, y; i <= t; i++) {
        x = read(), y = read();
        abd[x][y] = 1;
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(((i + j) & 1) == 0 && !abd[i][j]) {//黑色节点
            //位运算给我统统打括号！！！！！！！！！！！！！！！
                memset(vis, 0x00, sizeof vis);
                if(dfs(i, j)) ans++;
            }
    printf("%d\n", ans);
    return 0;
}