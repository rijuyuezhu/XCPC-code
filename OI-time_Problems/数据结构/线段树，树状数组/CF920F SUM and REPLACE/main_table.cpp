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

int main() {
    for(int i = 1; i <= 100; i++) {
        int ans = 0;
        for(int j = 1; j * j <= i; j++) {
            if(i % j == 0) {
                ans++;
                if(j * j != i) ans++;
            }
        }
        printf("%d:%d\n", i, ans);
    }
    return 0;
}