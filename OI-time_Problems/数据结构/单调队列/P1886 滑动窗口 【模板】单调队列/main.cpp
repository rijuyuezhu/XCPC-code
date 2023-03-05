//https://www.luogu.com.cn/problem/P1886
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 1e6 + 5;
int n, k;
int a[MAXN];
struct Que {
    int q[MAXN];
    int h, t;//[h,t)
    Que() {
        h = t = 0;
    }
    void clear() {
        h = t = 0;
    }
    bool empty() {return h == t;}
    int front() {return q[h];}
    int back() {return q[t-1];}
    void push_back(int x) {
        q[t++] = x;
    }
    void pop_back() {
        t--;
    }
    void pop_front() {
        h++;
    }
}Q;
int main() {
    n = read(); k = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    for(int i = 1; i <= n; i++) {
        while(!Q.empty() && a[Q.back()] >= a[i]) Q.pop_back();
        Q.push_back(i);
        while(!Q.empty() && i - Q.front() + 1 > k) Q.pop_front();
        if(i >= k) printf("%d ", a[Q.front()]); 
    }
    printf("\n");
    Q.clear();
    for(int i = 1; i <= n; i++) {
        while(!Q.empty() && a[Q.back()] <= a[i]) Q.pop_back();
        Q.push_back(i);
        while(!Q.empty() && i - Q.front() + 1 > k) Q.pop_front();
        if(i >= k) printf("%d ", a[Q.front()]);
    }
    printf("\n");
    return 0;
}