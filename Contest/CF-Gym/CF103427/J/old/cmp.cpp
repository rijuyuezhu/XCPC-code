#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main() {
    while(1) {
        system("data.exe > data.in");
        system("bf.exe < data.in > bf.out");
        system("J.exe < data.in > J.out");
        if(system("fc bf.out J.out")) {
            cout << "Wrong!\n";
            return 0;
        }
    }

    return 0;
}
