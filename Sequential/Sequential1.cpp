#include <iostream>
#include <vector>       //for the vector<T> type
#include <functional>   //for functional stuff
#include <cstring>      //string functions such as strcmp


using namespace std;    //This might be bad habit, but for now I keep it


// Function that prints the matrix
void print2DVector(const vector< vector<double> > A, int row_start, int row_finish, int col_start, int col_finish) {
    for(int i=row_start; i<=row_finish; i++) {
        for(int j=col_start; j<=col_finish; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return;
}





int main(int argc, char* argv[]) {
    if(argc==2 && strcmp(argv[1],"-help")==0) {
        cout << "Usage is: " << argv[0] << " m n seed niter printflag" << endl;
        return 0;
    }

    int m = (argc > 1 ? atoi(argv[1]) : 100);           //rows
    int n = (argc > 2 ? atoi(argv[2]) : 100);           //cols
    int seed = (argc > 3 ? atoi(argv[3]) : 123);        //seed
    int niter = (argc > 4 ? atoi(argv[4]) : 1000);      //n° iterations
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
        cout << "Starting matrix: " << endl:
        print2DVector(A,0,m-1,0,n-1);
        cout << endl;
    }

    auto f = [] (vector<std::pair<int,int> > neigh) {

        return;
    }
    

    return 0;
}