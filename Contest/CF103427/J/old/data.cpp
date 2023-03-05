#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
    srand(time(0));
    cout << 5 << '\n';
    for(int t = 0; t < 5; t++) {
        for(int i = 0; i < 4; i++)
            cout << rand() % 10;
        cout << ' ';
        for(int i = 0; i < 4; i++)
            cout << rand() % 10;
        cout << '\n';
    }
    return 0;
}
