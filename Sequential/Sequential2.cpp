#include <iostream>
#include <vector>       //for the vector<T> type
#include <functional>   //for functional stuff
#include <cstring>      //string functions such as strcmp


using namespace std;    //This might be bad habit, but for now I keep it


// Function that prints the matrix
void print2DVector(const vector< vector<double> > A) {
    for(int i=0; i< A.size(); i++) {
        for(int j=0; j<= A[i].size(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return;
}

auto stencil( vector<vector<double> >& A,
            function<double(vector<double>)> f, 
            vector<pair<int,int> > neighborhood, 
            int niter) {


    // we get the max dimensions
    vector<pair<int,int> >::iterator maxLeft = max_element(neighborhood.begin(),neighborhood.end(),[] (pair<int,int> a, pair<int,int> b) {return -a.second < -b.second;}); 
    vector<pair<int,int> >::iterator maxTop = max_element(neighborhood.begin(),neighborhood.end(),[] (pair<int,int> a, pair<int,int> b) {return -a.first < -b.first;}); 
    vector<pair<int,int> >::iterator maxRight = max_element(neighborhood.begin(),neighborhood.end(),[] (pair<int,int> a, pair<int,int> b) {return a.second < b.second;}); 
    vector<pair<int,int> >::iterator maxBottom = max_element(neighborhood.begin(),neighborhood.end(),[] (pair<int,int> a, pair<int,int> b) {return a.first < b.first;}); 

    vector<int> margins = {(*maxLeft).second, (*maxTop).first, (*maxRight).second, (*maxBottom).first};

    vector< vector<double> > Abis(A.size-margins[1]+margins[3], vector<double>(A[1].size()-margins[0]+margins[2], 0)); // full of zeroes...


    



    for (int k = 0; k < niter; k++) {

        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A[i].size(); j++) {
                vector<double> elems;
                elems.push_back(A[i][j]);
                for(auto pair : neighborhood) {
                    /* We also add "illegal ones". But this is the sequential version, 
                        so I can be a little bit less concerned with the issues that lead
                        to a failure with vectorization: the goal is to create the best
                        sequential version */
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
    return;
} 



int main(int argc, char* argv[]) {
    if(argc==2 && strcmp(argv[1],"-help")==0) {
        cout << "Usage is: " << argv[0] << " m n seed niter printflag" << endl;
        return 0;
    }

    int m = (argc > 1 ? atoi(argv[1]) : 20);           //rows
    int n = (argc > 2 ? atoi(argv[2]) : 20);           //cols
    int seed = (argc > 3 ? atoi(argv[3]) : 123);        //seed
    int niter = (argc > 4 ? atoi(argv[4]) : 100);      //n° iterations
    char printflag = (argc > 5 ? *argv[5] : 'n');

    // For now let me use vector< vector<double> > as a data structure
    vector< vector<double> > A(m, vector<double>(n,0));


    const int max = 150;        // random. Not very important

    //We fill in the matrix with random elements (given the seed)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = (double) (rand() % max);
        } 
    }
    
    if (printflag == 'y') {
        cout << "Starting matrix: " << endl;
        print2DVector(A);
        cout << endl;
    }


    function<double(vector<double>)> average = [](vector<double> v) {
        double sum = 0;
        for(double n : v) sum += n;
        return sum/(v.size());
    };

    vector<pair<int,int> > crossNeigh = {{-1,0},{1,0},{0,-1},{0,1}};
    vector<pair<int,int> > ringNeigh = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,1},{-1,-1}};

    stencil(A,average,crossNeigh,niter);

    cout<< "Final matrix: " << endl;
    print2DVector(A);
    cout << endl;
        

    return 0;
}



/* DISCARICA




    // For now, just a bit of random things.
    // For example, I want to figure out if it is better to use = or & (value or reference)
    auto average = [&] (vector<std::pair<int,int> > neighborhood) {
        bool exp1 = (i==0 || i==m-1); 
        bool exp2 = (j==0 || j==n-1);

            no check for offset. The huge padding approach is tempting,
            and I'm not the kind of guy that is worried about memory usage,
            but it seams very inefficient... 
            The problem is that I have no control on the function. So this is what it is
            I could thing about it more. 
        int sum = A[i][j];
        for(auto ind : neighborhood) {
            // Hopefully this works
            sum += (i+ind.first!=0)*(j+ind.second!=0)*A[(i+ind.first!=0)*(i+ind.first)][(j+ind.second!=0)*(j+ind.second)];
        }
        int den = 5 - (exp1 || exp2) - (exp1 && exp2);

        return;
    };


*/