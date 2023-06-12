#include <iostream>
#include <vector>
#include <functional>

using namespace std;


int main(int argc, char* argv[]) {
    std::pair<int,int> p = {1,1};
    std::pair<int,int> q = {2,2};

    cout << "p = <" << p.first << "," << p.second << ">" << endl;

    vector<pair<int,int> > v;

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

        return {first,second}
    }
    

    return 0;
}