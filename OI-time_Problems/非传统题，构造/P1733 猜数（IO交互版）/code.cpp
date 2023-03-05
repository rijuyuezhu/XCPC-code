#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
int l = 1, r = 1e9 + 1;
int main() {
    while(l <= r) {
        int mid = (l + r) >> 1;
        printf("%d\n", mid); fflush(stdout);
        int opt = read();
        if(opt == 0) {return 0;}
        else if(opt == -1) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return 0;
}
