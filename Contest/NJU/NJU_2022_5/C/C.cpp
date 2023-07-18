#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
int ToNumber(char c) {return c - 'A';}
int ToLetter(int c) {return c + 'A';}

const int MAXN = 55;
int n, m, a[MAXN], b[MAXN], c[MAXN], x[MAXN], tp;
char buf[MAXN];
void work(int te) {
    scanf("%d%d", &n, &m);
    scanf("%s", buf+1);
    for(int i = 1; i <= n; i++) a[i] = ToNumber(buf[i]);
    scanf("%s", buf+1);
    for(int i = 1; i <= n; i++) b[i] = ToNumber(buf[i]);
    scanf("%s", buf+1);
    tp = a[1] - b[1];
    for(int i = 1; i <= m; i++) c[i] = ToNumber(buf[i]);
    printf("Case #%d: ", te);
    for(int i = 1; i <= m; i++) printf("%c", ToLetter((tp + c[i] + 26) % 26));
    printf("\n");


}
int main() {
    int T;
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) work(i);
    return 0;
}