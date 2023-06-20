#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    vector<pair<int,int> > v;
    int max = (argc > 1 ? atoi(argv[1]) : 10);

    for(int i=0; i < max; i++) {
        v.push_back({pow(-1,i)*i,(int) rand() % 20});
    }

    cout << "v = [";
    for(int i = 0; i < max; i++) {
        cout << " <" << v[i].first << "," << v[i].second << ">";
    }
    cout << " ]" << endl;

    vector<pair<int,int> >::iterator result1 = max_element(v.begin(), v.end());

    cout << "result1 = <" << (*result1).first << "," << (*result1).second << ">" << endl;

    vector<pair<int,int> >::iterator result2 = max_element(v.begin(),
                            v.end(),
                            [] (pair<int,int> a, pair<int,int> b) {
                                return a.second < b.second;
                                });

    cout << "result2 = <" << (*result2).first << "," << (*result2).second << ">" << endl;

    //vector<pair<int,int> > neigh = {{0,-1},{-1,0},{-2,0},{0,1},{0,2},{1,0},{2,0},{3,0}};
    vector<pair<int,int> > neigh = {{0,-1},{-1,0},{0,1},{1,0}};

    auto maxLeft = max_element(neigh.begin(),neigh.end(),[] (pair<int,int> a, pair<int,int> b) {return -a.second < -b.second;}); 
    auto maxTop = max_element(neigh.begin(),neigh.end(),[] (pair<int,int> a, pair<int,int> b) {return -a.first < -b.first;}); 

    cout << "neigh = [";
    for(int i = 0; i < neigh.size(); i++) cout << " <" << neigh[i].first << "," << neigh[i].second << ">";
    cout << " ]" << endl;
    //cout << "left found at index " << distance(neigh.begin(), maxLeft) << " has value <" << (*maxLeft).first << "," << (*maxLeft).second << ">" << endl;

    auto maxRight = max_element(neigh.begin(),neigh.end(),[] (pair<int,int> a, pair<int,int> b) {return a.second < b.second;}); 
    auto maxBottom = max_element(neigh.begin(),neigh.end(),[] (pair<int,int> a, pair<int,int> b) {return a.first < b.first;}); 


    vector<int> margins = {(*maxLeft).second, (*maxTop).first, (*maxRight).second, (*maxBottom).first};

    cout << "margins = [";
    for(auto el : margins) cout << el << ", ";
    cout << "]" << endl;

    return 0;
}