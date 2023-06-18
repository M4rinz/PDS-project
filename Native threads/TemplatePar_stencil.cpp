#include <iostream>
#include <vector>       //for the std::vector<T> type
#include <functional>   //for functional stuff
#include <thread>       //for thread obj
// #include <future>    //for the futures. I may need them




/* In the final version, the number of threads should be an optional:
The user can set it up, but if not it is automatically computed,
based on the performance (on the SPM machine) */

template <typename T>
std::vector<std::vector<T> >* stencil( 
            std::vector<std::vector<T> >& A,
            std::function<T(std::vector<T>)> f, 
            std::vector<std::pair<int,int> > neighborhood, 
            int niter,
            int nthreads) {

    std::vector< std::vector<T> > B(A.size(), std::vector<T>(A[1].size())); 

    auto ThreadBody = [&] (int from, int to) {
        std::vector<T> elems;
        for (int i = from; i < to; i++) {
            /* for now, each thread works on a "strip", that is
            on a set of rows of the matrix */
            for(int j = 0; j < A[i].size(); j++) {
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

        return;
    };

    for (int k = 0; k < niter; k++) {
        // splitting

        int portion = A.size()/nthreads;  //m divided by nthreads
        int nw;
        /* If there are more threads than rows, then each thread works on
        one single row and only an amount equal to the number of rows 
        are launched. This will for sure change in the future */
        if (portion == 0) {
            nw = A.size();
            portion == 1;
        }
        else nw = nthreads;        
    
        std::vector<std::thread> ths;
        for(int w = 0; w < nw-1; w++) {
            // classic split that leads to poor load balancing
            ths.push_back(std::thread(ThreadBody,portion*w,portion*(w+1)));  
        }
        ths.push_back(std::thread(ThreadBody,portion*(nw-1),A.size()));
        
        //for(auto th : ths) th.join();
        for(int i = 0; i < ths.size(); i++) ths[i].join();

        std::swap(A,B);

    }

    return &A;
} 




/*     
    DISCARICA    


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
*/



