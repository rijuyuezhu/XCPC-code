#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAXN = 205;
const int MAXQ = 2e4 + 5;

int n, q, r[MAXN], d[MAXN][MAXN], id[MAXN], ans[MAXQ];
struct Que {
    int id, u, v, w;
    bool operator < (const Que& B)const {
        return w < B.w;
    }
}que[MAXQ];
bool cmp(int a, int b) {
    return r[a] < r[b];
}
void work(int te) {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &r[i]);
        id[i] = i;
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%d", &d[i][j]);
    for(int i = 1; i <= q; i++) {
        que[i].id = i;
        scanf("%d%d%d", &que[i].u, &que[i].v, &que[i].w);
    }
    sort(id + 1, id + 1 + n, cmp);
    sort(que + 1, que + 1 + q);
    int tot = 1;
    for(int i = 1; i <= q; i++) {
        while(tot <= n && r[id[tot]] <= que[i].w) {
            int k = id[tot];
            for(int ii = 1; ii <= n; ii++)
                for(int jj = 1; jj <= n; jj++)
                    d[ii][jj] = min(d[ii][jj], d[ii][k] + d[k][jj]);
            tot++;
        }
        ans[que[i].id] = d[que[i].u][que[i].v];
    }
    printf("Case #%d:\n", te);
    for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);
}
int main() {
    int T;
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) work(i);
    return 0;
}