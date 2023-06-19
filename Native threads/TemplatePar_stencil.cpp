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

        /*
            int nw = nthreads;  //I'll replace it with (n*m)/gamma, where gamma is computed thanks to the sequential results
            int nPortions_row, nPortions_col, portionRow, portionCol;
            // remember that m and n are undefined...
            if (m =< n) {
                nPortions_row = (nw*m)/n;
                portionRow = n/nw;
                nPortions_col = n/m;
                portionCol = m;
            }
            else {
                nPortions_row = (nw*n)/m;
                portionRow = m/nw;
                nPortions_col = m/n;
                portionCol = n;            
            }
            // maybe some other stuff, if we get strange numbers

            // this for loop is not a good idea... E se avanza spazio su n invece che su m?
            // Forse è meglio fare una matrice con gli indici di inizio e fine...
            for (int i = 0; i < nPortions_row-1; i++) {
                for (int j = 0; j < nPortions_col-1; j++) {
                    ths.push_back(std::thread(ThreadBody,i*portionRow,(i+1)*portionRow,j*portionCol,(j+1)*portionCol));
                }
                ths.push_back(std::thread(ThreadBody,i*portionRow,(i+1)*portionRow,(nPortions_col-1)*portionCol,A[i].size()));
            }
            for (int j = 0; j < nPortions_col-1; j++) {
                ths.push_back(std::thread(ThreadBody,(nPortions_row-1)*portionRow,A.size(),j*portionCol,(j+1)*portionCol));
            }
            ths.push_back(std::thread(ThreadBody,(nPortions_row-1)*portionRow,A.size(),(nPortions_col-1)*portionCol,A[m].size()));
        */
        
        


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
        // classic split that leads to poor load balancing
        for(int w = 0; w < nw-1; w++) {
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



