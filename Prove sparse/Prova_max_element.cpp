#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main(int argc, char* argv[]) {
    vector<pair<int,int> > v;
    int max = (argc > 1 ? atoi(argv[1]) : 10);

    for(int i=0; i < max; i++) {
        v.push_back({(-1)^(i)*i,(int) rand() % 20});
    }

    cout << "v = [";
    for(int i = 0; i < max; i++) {
        cout << " <" << v[i].first << "," << v[i].second << ">";
    }
    cout << " ]" << endl;

    vector<pair<int,int> >::iterator result = max_element(v.begin(), v.end());

    cout << "result = " << (*result).first << endl;






    return 0;
}