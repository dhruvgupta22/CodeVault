#include <bits/stdc++.h>
using namespace std;

// 0-indexing is used everywhere

class SparseTable{
public:
    int *A; // The array of size N from which sparse table was created
    int **Table; // The sparse table of size (N-1) * (logN + 1). Table[i][k] = OR(A[i], ... , A[i+2^k])
    int *Pow2; // Pow2[i] = largest power of 2 less than or equal to i
    int *Log2; // Log2[i] = largest k such that 2^k <= i
    int n; // n = N = size of given array

    // Constructor for building the Sparse Table using given array
    SparseTable(int arr[], int N){
        n = N;
        makeArrays(arr,N);
        makeTable(arr,N);
    }

    // This function allocates space for arrays A, Pow2, Log2 then fills them with appropiate values.
    void makeArrays(int arr[], int N){
        // Allocate memory to A
        A = new int[N];
        // Fill in A
        for(int i=0; i<N; i++){
            A[i] = arr[i];
        }

        // Allocate memory to Pow2 and Log2
        Pow2 = new int[N+1];
        Log2 = new int[N+1];

        // Fill in Pow2 and Log2
        int power = 1;
        int log = 0;
        while(power <= N){
            for(int i=power; i <= min(2*power-1,N); i++){
                Pow2[i] = power;
                Log2[i] = log;
            }
            power *= 2;
            log++;
        }
    }

    // This function allocates space to Table then poulates it.
    void makeTable(int arr[], int N){
        // Allocate memory
        Table = new int*[N-1];
        for (int i=0; i<N-1; i++) {
            Table[i] = new int[Log2[N]];
        }
        // Initialisation
        for(int i=0; i<N-1; i++){
            for(int k=0; k<=Log2[N]; k++){
                Table[i][k] = 0;
            }
        }
        // Fill the first column
        for(int i=0; i<N-1; i++){
            Table[i][0] = (arr[i] | arr[i+1]);
        }
        // Fill rest columns dynamically
        for(int k=1; k<=Log2[N]; k++){
            for(int i=0; i<N-2; i++){
                if(i + (1<<k) < N){
                    Table[i][k] = (Table[i][k-1] | Table[i+ (1<<(k-1))][k-1]);
                }
            }
        }
    }

    // This function calculates OR(A[i], ... ,A[j]) in O(1) time
    int Range(int i, int j){
        if(j==i) return A[i];
        int len = j-i;
        int len_pow2 = Pow2[len];
        int k = Log2[len];
        if(len_pow2==len) return Table[i][k];
        else return (Table[i][k] | Table[j-len_pow2][k]);
    }

    // This function prints the original array A
    void print_arr(){
        for(int i=0; i<n; i++){
            cout<< A[i] << " ";
        }
        cout<<endl;
    }

    // This function prints the Sparse Table
    void print_Table(){
        for(int i=0; i<n-1; i++){
            for(int k=0; k<=Log2[n]; k++){
                cout<< Table[i][k] << " ";
            }
            cout<<endl;
        }
    }
};

// This function returns the smallest index I such that (i) I >= idx  (ii) OR(A[idx], ... , A[I]) >= val
int bin_search(int idx, int val, SparseTable T){
    int l = idx, r = T.n-1;
    int mid;
    int last_mid = -2;
    int OR;
    while(l<=r){
        mid = (l+r)/2;
        OR = T.Range(idx,mid); 
        if(OR < val) l = mid+1;
        else{
            last_mid = mid;
            r = mid-1;
        }
    }
    return last_mid;
}

int main(){
    int N,Q;
    cin>>N;
    int arr[N];
    for(int i=0; i<N; i++) cin>>arr[i];
    
    cin>>Q;
    pair<int,int> queries[Q];
    int x,y;
    for(int q=0; q<Q; q++){
        cin>>x>>y;
        queries[q].first = x-1; 
        queries[q].second = y;
    }

    SparseTable T(arr,N);
    // T.print_arr();
    // T.print_Table();

    for(int q=0; q<Q; q++){
        int x = bin_search(queries[q].first, queries[q].second, T);
        cout<<x+1<<" ";
    }

    return 0;
}