#include <iostream>
#include <set>
using namespace std;
int x, y;
set<int> p;
void divide(int v) {
    int tmp = v;
    for(int i = 2; 1ll * i * i <= v; i++) 
        if(tmp % i == 0) {
            p.insert(i);
            while(tmp % i == 0)
                tmp /= i;
        }
    if(tmp > 1)
        p.insert(tmp);
}
int main() {
    cin >> x >> y;
    divide(abs(x));
    divide(abs(y));
    cout << (1ull << p.size());
    return 0;
}