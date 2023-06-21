#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;

vector<int>* increaseV(vector<int>& v, int inc) {
    vector<int> supp;
    for(int i = 0; i< v.size(); i++) {
        supp.push_back(v[i]+inc);
        v[i]+=inc;
    }

    return &v; 
}

void printVec(vector<int> v) {
    cout << "[";
    for(int i = 0; i < v.size()-1; i++) {
        cout << v[i] << ", ";
    }
    cout << v[v.size()-1] << "]" << endl;
    return;
} 

int main(int argc, char* argv[]) {
    int n = (argc > 1 ? atoi(argv[1]) : 10);
    int inc = (argc > 2 ? atoi(argv[2]) : 3);

    vector<int> v;

    for (int i = 0; i < n; i++)
        v.push_back(i);


    vector<int>* w = increaseV(v, inc);

    cout << "v = ";
    printVec(v);
    cout << endl;
    cout << "w = ";
    printVec(*w);
    cout << endl; 
    
    

    return 0;
}