#include <iostream>
#include <vector>       //for the std::vector<T> type
#include <functional>   //for functional stuff
#include <thread>       //for thread obj
// #include <future>    //for the futures. I may need them



template <typename T>
std::vector<std::vector<T> >* stencil( std::vector<std::vector<T> >& A,
            std::function<T(std::vector<T>)> f, 
            std::vector<std::pair<int,int> > neighborhood, 
            int niter) {

    std::vector< std::vector<T> > B(A.size(), std::vector<T>(A[1].size())); 

    for (int k = 0; k < niter; k++) {

        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A[i].size(); j++) {
                std::vector<T> elems;
                elems.push_back(A[i][j]);
                for(auto pair : neighborhood) {
                    int ipf = i+pair.first;
                    int jps = j+pair.second;
                    if((0 <= ipf && ipf < A.size()) && (0 <= jps && jps < A[i].size()))
                        elems.push_back(A[ipf][jps]);  
                }
                B[i][j] = f(elems);

            }            
        }
        std::swap(A,B);

    }
    return &A;
} 






