#include <iostream>
#include <vector>
#include <functional>

using namespace std;


int main(int argc, char* argv[]) {
    std::pair<int,int> p = {1,1};
    std::pair<int,int> q = {2,2};

    cout << "p = <" << p.first << "," << p.second << ">" << endl;

    vector<pair<int,int> > v;
    vector<pair<int,int> > w = {{69,420}};

    for(int i = 0; i < 5; i++) {
        v.push_back({i,i});
    }

    cout << "v = [";
    for(int i = 0; i < 5; i++) {
        cout << " <" << v[i].first << "," << v[i].second << ">";
    }
    cout << " ]" << endl;
    
    auto sum_pair = [] (vector<pair<int,int> > v) {
        int first = 0;
        int second = 0;

        for(auto pair : v) {
            first+= pair.first;
            second+= pair.second;
        }
        pair<int,int> res = {first,second};

        return res;
    };
    cout << "w = <" << sum_pair(w).first << "," << sum_pair(w).second << ">" << endl;
    
    cout << "Somma pairwise degli elementi di v = <" << sum_pair(v).first << "," << sum_pair(v).second << ">" << endl;

    return 0;
}