#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    cout << (1ll * n * (n-1) * (n-2) * (n-3) / 24 + n * (n-1) / 2 + 1);
    return 0;
}