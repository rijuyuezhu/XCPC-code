//https://acm.njupt.edu.cn/problem/CH6703
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

int n, m, s, t;
void solve() {

}

void init() {


}
int main() {
    int T = read();
    while(T--) {
        init();
        solve();
    }
    return 0;
}