#include <iostream>
#include <vector>
#include <functional>

using namespace std;


vector<vector<int> >* myStencil(function<int(int)> f, vector<vector<int> >& A, int niter) {
    //vector<vector<int> >* B = new vector<vector<int> >(A.size(), A[1].size());
    
    for(int k = 0; k < niter; k++) {
        for(int i = 0; i < A.size(); i++) {  
            for(int j = 0; j < A[i].size(); j++)
                //(*B)[i].push_back(f(A[i][j]));// = f(A[i][j]);
                A[i][j]=f(A[i][j]);
        }
    }
    //swap(A,*B);

    return &A;
}

// Function that prints the matrix
void print2DVector(const vector< vector<int> > A) {
    for(int i=0; i<A.size(); i++) {
        for(int j=0; j<A[i].size(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return;
}

int main(int argc, char* argv[]) {
    int m = (argc > 1 ? atoi(argv[1]) : 5);
    int n = (argc > 2 ? atoi(argv[2]) : 10);
    int niter = (argc > 3 ? atoi(argv[3]) : 3);

    auto f = [] (int x) {return x+1;};
    function<int(int)> g = [&](int x) {return x+1;};  


    vector< vector<int> > A(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = i+j;
        }            
    }

    cout << "previous A =" << endl;
    print2DVector(A);

    cout << "A.size() = " << A.size() << '\t' << "m = " << m << endl;
    cout << "A[1].size() = " << A[1].size() << '\t' << "n = " << n << endl;

    vector< vector<int> >* B = myStencil(g, A, niter);
    cout << "A after " << niter << " applications of the function =" << endl;
    print2DVector(*B);
    

    return 0;
}