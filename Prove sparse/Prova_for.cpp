#include <iostream>
#include <vector>       //for the vector<T> type
#include <cstring>      //string functions such as strcmp

using namespace std;

int main(int argc, char* argv[]) {
    int n = (argc > 1 ? atoi(argv[1]) : 0);

    for (int i = 0; i < n; i++) {
        cout << "nel for per la volta n°" << i << endl;
    }
    cout << "n = " << n << endl;

    return 0;
}