#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN = 1e5 + 5;
const int MAXM = 26;
const int MAXNODE = 140;
const int P = 128;
struct Node {
    int fa, ed, ch[2];
}e[MAXNODE]; // rt = 1;
int tot, n, m, multi_ans[2][MAXNODE], f[2][MAXNODE];
char s[MAXN];
int idy(int now) {
    return e[e[now].fa].ch[1] == now;
}
void work() {
    tot = 0;
    e[++tot] = {0, 0, {0, 0}};
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        static char ch[2], s[10];
        scanf("%s%s", ch, s);
        int len = strlen(s);
        int now = 1;
        for(int j = 0; j < len; j++) {
            int v = s[j] - '0';
            if(!e[now].ch[v])
                e[e[now].ch[v] = ++tot] = {now, 0, {0, 0}};
            now = e[now].ch[v];
        }
        e[now].ed++;
    }
    scanf("%s", s);
    for(int i = 1; i <= tot; i++)
        f[0][i] = f[1][i] = 0, multi_ans[0][i] = multi_ans[1][i] = 0;
    f[1][1] = 1;
    for(int i = 0; i < n; i++) {
        int now = i & 1, pre = now ^ 1;
        int v = s[i] - '0';
        f[now][1] = multi_ans[now][1] = 0;
        for(int j = 2; j <= tot; j++) {
            if(idy(j) == v) {
                f[now][j] = f[pre][e[j].fa];
                multi_ans[now][j] = multi_ans[pre][e[j].fa];
                if(e[j].ed > 0) {
                    f[now][1] += f[now][j] * e[j].ed;
                    multi_ans[now][1] |= multi_ans[now][j];
                }
            } else
                f[now][j] = multi_ans[now][j] = 0;
            if(f[now][1] >= P) {
                f[now][1] %= P;
                multi_ans[now][1] = 1;
            }
        }
    }
    int ans_now = (n-1) & 1;
    if(multi_ans[ans_now][1] || f[ans_now][1] >= 2)
        printf("puppymousecat %d\n", f[ans_now][1]);
    else if(f[ans_now][1] == 1)
        printf("happymorsecode\n");
    else
        printf("nonono\n");
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) work();
}