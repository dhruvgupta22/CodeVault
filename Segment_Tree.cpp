#include <iostream>
#include <cmath>
using namespace std;
class SegmentTree{
public:
    int *Tree;
    int array_index;
    int size;
    SegmentTree(int arr[], int n, int filler = 0){
        int logn = ceil(log2(n));
        array_index = 1 << logn;
        size = 2 * array_index -1;

        Tree = new int[size+1];

        for(int i=0; i<n; i++){
            Tree[array_index + i] = arr[i];
        }
        for(int i = array_index + n; i <= size; i++){
            Tree[i] = filler;
        }
        Populate();
    }
    void Populate(){
        int l = array_index/2;
        for(int i = 2*l-1; i > 0; i--){
            Tree[i] = Tree[2*i] + Tree[2*i + 1];
        }
    }
    void update(int idx, int val){
        int node = array_index + idx;
        int change = val - Tree[node];
        while(node > 0){
            Tree[node] += change;
            node /= 2;
        }
    }
    int request(int l, int r){
        l = array_index + l;
        r = array_index + r;
        if(l == r) return Tree[l];
        int sum = Tree[l] + Tree[r];
        while(l/2 != r/2){
            if(!(l&1)){
                sum += Tree[l+1];
            }
            if(r&1){
                sum += Tree[r-1];
            }
            l = l/2;
            r = r/2;
        }
        return sum;
    }
    void display(){
        cout<<array_index<<" | "<<size<<" | "<<endl;
        for(int i=1; i<=size; i++){
            cout<<Tree[i]<<" ";
            if(ceil(log2(i+1)) == floor(log2(i+1))) cout<<endl;
        }
    }
};

class Query{
public:
    int type, l, r;
};
int main(){

    int num_shops, max_amt, num_queries; cin>>num_shops>>max_amt>>num_queries;
    int price[num_shops];
    Query q[num_queries];
    int x,y,z, sum;
    for(int i=0; i<num_shops; i++){
        cin>>price[i];
    }
    // for(int i=0; i<num_queries; i++){
    //     cin>>x>>y>>z;
    //     q[i].type = x;
    //     q[i].l = y;
    //     q[i].r = z;
    // }

    SegmentTree T(price,num_shops);
    for(int i=0; i<num_queries; i++){
        T.display();
        cin>>x>>y>>z;
        q[i].type = x;
        q[i].l = y;
        q[i].r = z;
        if(q[i].type == 1){
            T.update(q[i].l, q[i].r);
        }
        if(q[i].type == 2){
            sum = T.request(q[i].l, q[i].r);
            cout<<"sum = "<<sum;
            if(sum <= max_amt){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
        }
    }
    return 0;
}