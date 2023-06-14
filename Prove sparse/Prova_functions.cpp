#include <iostream>
#include <vector>
#include <functional>

using namespace std;


void myStencil(function<int(int)> f, vector<int>& v, int niter) {
    /* for(auto elem : v) {
        for (int i = 0; i < niter; i++) {
            elem = f(elem);
        }
    } */
    for(int j = 0; j < niter; j++) {
        for(int i = 0; i < v.size(); i++) {  
            v[i] = f(v[i]);
        }
    }

    return;
}

void printVec(vector<int> v) {
    for(int i = 0; i < v.size()-1; i++) {
        cout << v[i] << ", ";
    }
    cout << v[v.size()-1] << "]" << endl;

} 

int main(int argc, char* argv[]) {
    int n = (argc > 1 ? atoi(argv[1]) : 10);
    int niter = (argc > 2 ? atoi(argv[2]) : 5);

    auto f = [] (int x) {return x+1;};
    function<int(int)> g = [&](int x) {return x+1;};  

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = i+1;
    }

    cout << "previous v = [";
    printVec(v);

    myStencil(g, v, niter);
    cout << "v after " << niter << " applications of the function: [";
    printVec(v);
    

    return 0;
}