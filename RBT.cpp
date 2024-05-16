#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* 

1. Parent of each node needs to be stored for Successor, Predecessor, Insert and Delete operations.
2. Parent of root is defined as the root itself.

3. Size of subtree at each node needs to be stored for KthSmallest and KthLargest operations.

4. colour(node) function is needed because we consider NULL nodes as 'black'.

5. O(n) time operations --> Height, all Traversals, KthSmallest and KthLargest.
6. O(log(n)) time operations --> Min, Max, Search, Successor, Predecessor, Insert and Delete.

*/
class Node{
public:
    int val;
    Node* left = NULL; 
    Node* right = NULL;
    Node* parent = NULL; 
    
    char colour; // 'r' = Red, 'b' = Black
    Node(int x=0, char c='b'){
        val = x;
        colour = c;
    }
};

char colour(Node* node){
    if(node) return node->colour;
    return 'b';
}
void print(Node* node){
    if(node) cout << node->val << node->colour << node->parent->val << " "; 
    else cout<<"null ";
}

class RBT{
public:
    Node* root = NULL;
    int size = 0;
    // void Make_BST(int arr[], int n);
    int Min();
    int Max();
    int Height();
    int Min(Node* root);
    int Max(Node* root);
    int Height(Node* root);

    void LevelOrder(Node* root);
    void Inorder(Node* root);
    void PreOrder(Node* root);
    void PostOrder(Node* root);

    Node* Search(int val);
    Node* Successor(int val);
    Node* Predecessor(int val);
    Node* KthSmallest(int k);
    Node* KthLargest(int k);

    void Insert(int val);
    void Delete(int val);

    void InsertMany(int val);
};

int main(){
    RBT Tree;
    int x;
    char c;
    while(true){ 
        cin>>c; cin>>x;
        if(c == 'i') Tree.Insert(x);
        if(c == 'd') Tree.Delete(x);
        
        // Tree.LevelOrder(Tree.root);
        // cout<<endl;
        Tree.Inorder(Tree.root);
        // Tree.PreOrder(Tree.root);
        // Tree.PostOrder(Tree.root);
        // cout<<Tree.size<<endl;
        // cout<<Tree.Height(Tree.root)<<endl;
        // cout<<Tree.Min(Tree.root)<<" "<<Tree.Max(Tree.root)<<endl;
        // int y;
        // cin>>y;
        // print(Tree.Successor(y));
        // cout<<endl;
    }
    return 0;
}


// Min, Max, Height
int RBT::Min(){
    if(!root){
        cerr<<"The tree is empty!"<<endl;
    }

    Node* node = root;
    int min = INT_MAX;
    while(node){
        min = (node->val < min) ? node->val : min;
        node = node->left;
    }
    return min;
}
int RBT::Max(){
    if(!root){
        cerr<<"The tree is empty!"<<endl;
    }

    Node* node = root;
    int max = INT_MIN;
    while(node){
        max = (node->val > max) ? node->val : max;
        node = node->right;
    }
    return max;
}
int RBT::Height(){
    int height = 0;
    queue<Node*> Q;
    if(root) Q.push(root);
    Node* node;
    while(!Q.empty()){
        int level_size = Q.size();
        for(int i=0; i<level_size; i++){
            node = Q.front();
            Q.pop();
            if(node->left) Q.push(node->left);
            if(node->right) Q.push(node->right);
        }
        height++;
    }
    return height;
}

// Min, Max, Height recursively. May be used to find Min, Max, Height of a subtree.
int RBT::Min(Node* root){
    return root ? min(root->val, Min(root->left)) : INT_MAX;
}
int RBT::Max(Node* root){
    return root ? max(root->val, Max(root->right)) : INT_MIN;
}
int RBT::Height(Node* root){
    return root ? max(Height(root->left), Height(root->right)) + 1 : 0;
}


// Traversals
void RBT::LevelOrder(Node* root){
    queue<Node*> Q;
    if(root) Q.push(root);
    Node* node;
    while(!Q.empty()){
        node = Q.front();
        Q.pop();
        print(node);
        if(node->left) Q.push(node->left);
        if(node->right) Q.push(node->right);
    }
}
void RBT::Inorder(Node* root){
    Node* node = root;
    if(node){
        Inorder(node->left);
        print(node);
        Inorder(node->right);
    }
}
void RBT::PreOrder(Node* root){
    Node* node = root;
    if(node){
        print(node);
        PreOrder(node->left);
        PreOrder(node->right);
    }
}
void RBT::PostOrder(Node* root){
    Node* node = root;
    if(node){
        PostOrder(node->left);
        PostOrder(node->right);
        print(node);
    }
}


// Search, Successor, Predecessor
Node* RBT::Search(int val){
    if(!root) return NULL;
    bool found = false;
    Node* node = root;
    while(!found && node){
        if(val < node->val) node = node->left;
        else if(val > node->val) node = node->right;
        else found = true;
    }
    return node;
}
Node* RBT::Predecessor(int val){
    Node* node = Search(val);
    Node* pred = NULL;
    
    if(node){
        Node* par = node->parent;
        if(node->left){
            pred = node->left;
            while(pred->right) pred = pred->right;
        }
        else if(node == par->right){
            pred = par;
        }
        else{
            
            while(par != par->parent->right && par != root){
                node = par;
                par = node->parent;
            }
            if(par != root) pred = par->parent;
        }
    }
    else{
        node = root;
        while(node){
            if(node->val > val){
                node = node->left;
            }
            else{
                pred = node;
                node = node->right;
            }
        }
    }
    return pred;
}
Node* RBT::Successor(int val){
    Node* node = Search(val);
    Node* succ = NULL;
    if(node){
        Node* par = node->parent;
        if(node->right){
            succ = node->right;
            while(succ->left) succ = succ->left;
        }
        else if(node == par->left){
            succ = par;
        }
        else{
            while(par != par->parent->left && par != root){
                node = par;
                par = node->parent;
            }
            if(par != root) succ = par->parent;
        }
    }
    else{
        node = root;
        while(node){
            if(node->val < val){
                node = node->right;
            }
            else{
                succ = node;
                node = node->left;
            }
        }
    }
    return succ;
}


// Insert & Delete
void RBT::Insert(int val){
    if(size == 0){
        root = new Node(val);
        root->parent = root;
    }
    else{
        Node* node = new Node(val, 'r');
        Node* par = root;
        Node* grand_par = NULL;
        Node* uncle = NULL;

        bool inserted = false;
        while(!inserted){
            if(par->val < node->val){
                if(par->right) par = par->right;
                else { par->right = node; inserted = true; }
            }
            else if(par->val > node->val){
                if(par->left) par = par->left;
                else { par->left = node; inserted = true; }
            }
            else return;
        }
        node->parent = par;
        if(par != root) grand_par = par->parent;
        if(grand_par != NULL) uncle = (grand_par->left == par) ? grand_par->right : grand_par->left;
        
        // Re-colour
        while(colour(par) == 'r' && node != root){
            if(colour(uncle) == 'r'){
                par->colour = grand_par->colour;
                uncle->colour = grand_par->colour;
                grand_par->colour = 'r';
                node = grand_par;
                par = node->parent;
                grand_par = par->parent;
                if(par == root) break;
                else uncle = (grand_par->left == par) ? grand_par->right : grand_par->left;
            }
            else{
                // Non trivial case
                if(par == grand_par->left){
                    if(node == par->left){
                        // Right rotaion on grand parent
                        grand_par->left = par->right;
                        par->right = grand_par;

                        if(grand_par != root){
                            if(grand_par == grand_par->parent->left) grand_par->parent->left = par;
                            else grand_par->parent->right = par;
                            par->parent = grand_par->parent;
                        }
                        else { par->parent = par; root = par; }

                        grand_par->parent = par;
                        if(grand_par->left) grand_par->left->parent = grand_par;

                        grand_par = par->parent;
                        uncle = (grand_par->left == par) ? grand_par->right : grand_par->left;

                        par->colour = 'b';
                        if(par->right) par->right->colour = 'r';
                    }
                    else{
                        // Left rotation on parent
                        par->right = node->left;
                        node->left = par;
                        grand_par->left = node;
                        node->parent = grand_par;
                        par->parent = node;
                        if(par->right) par->right->parent = par;

                        node = par;
                        par = node->parent;
                    }
                }
                else{
                    if(node == par->right){
                        // Left rotaion on grand parent
                        grand_par->right = par->left;
                        par->left = grand_par;
                        if(grand_par != root){
                            if(grand_par == grand_par->parent->left) grand_par->parent->left = par;
                            else grand_par->parent->right = par;
                            par->parent = grand_par->parent;
                        }
                        else { par->parent = par; root = par; }

                        grand_par->parent = par;
                        if(grand_par->right) grand_par->right->parent = grand_par;

                        grand_par = par->parent;
                        uncle = (grand_par->left == par) ? grand_par->right : grand_par->left;

                        par->colour = 'b';
                        if(par->left) par->left->colour = 'r';
                    }
                    else{
                        // Right rotation on parent
                        par->left = node->right;
                        node->right = par;
                        grand_par->right = node;
                        node->parent = grand_par;
                        par->parent = node;
                        if(par->left) par->left->parent = par;

                        node = par;
                        par = node->parent;
                    }
                }                
            }
        }
        root->colour = 'b';
    }
    size++;
}
void RBT::Delete(int val){
    Node* node = Search(val);
    if(!node) return;
    size--;
    if(node->left && node->right){
        Node* pred = Predecessor(node->val);
        int temp = pred->val;
        pred->val = node->val;
        node->val = temp;
        node = pred;
    }
    if(node == root){
        root = node->left ? node->left : node->right;
        if(root) { root->colour = 'b'; root->parent = root; }
        delete node;
        return;
    }

    Node* child = node->left ? node->left : node->right;
    Node* par = node->parent;
    Node* sibling = (node == par->left) ? par->right : par->left;

    if(node == par->left){
        par->left = (node->left) ? node->left : node->right;
        if(par->left) par->left->parent = par;
    }
    else{
        par->right = (node->left) ? node->left : node->right;
        if(par->right) par->right->parent = par;
    }

    if(colour(node) == 'r'){
        delete node;
        return;
    }
    else if(colour(node) == 'b'){
        if(colour(node->left) == 'r'){
            node->left->colour = 'b';
            delete node;
            return;
        }
        else if(colour(node->right) == 'r'){
            node->right->colour = 'b';
            delete node;
            return;
        }
        else{
            // Difficult case

            /* Note that sibling will not be a null node */
            if(node == par->left) par->left = child;
            else par->right = child;
            delete node;
            if(child == par->left){
                // If sibling is red, change it to black
                if(colour(sibling) == 'r'){
                    // Left rotation at parent
                    par->right = sibling->left;
                    if(sibling->left) sibling->left->parent = par;
                    if(par == par->parent->left) par->parent->left = sibling;
                    else par->parent->right = sibling;
                    if(par == root){
                        root = sibling;
                        sibling->parent = sibling;
                    }
                    sibling->left = par;
                    par->parent = sibling;

                    // make parent red and sibling black
                    sibling->colour = 'b';
                    par->colour = 'r';

                    // new sibling is now right child of parent
                    sibling = par->right;
                }
                // At this point, sibling must be black

                // If both children of sibling are black
                if(colour(sibling->left) == 'b' && colour(sibling->right) == 'b'){
                    // Handle main case 1
                    par->colour = 'b';
                    sibling->colour = 'r';
                }
                // If atleast one child of sibling is red
                else{
                    // If right child of sibling is black, make it red
                    if(colour(sibling->right) == 'b'){
                        // Right rotation at sibling
                        Node* left_child = sibling->left;
                        sibling->left = left_child->right;
                        left_child->right->parent = sibling;
                        left_child->parent = par;
                        par->right = left_child;
                        left_child->right = sibling;
                        sibling->parent = left_child;

                        // make sibling red and left_child black
                        sibling->colour = 'r';
                        left_child->colour = 'b';

                        // left_child becomes the new sibling
                        sibling = left_child;
                    }
                    // At this point right child of sibling must be red

                    // Handle main case 2
                    
                    // Left rotation at parent
                    par->right = sibling->left;
                    if(sibling->left) sibling->left->parent = par;
                    if(par == par->parent->left) par->parent->left = sibling;
                    else par->parent->right = sibling;
                    if(par == root){
                        root = sibling;
                        sibling->parent = sibling;
                    }
                    sibling->left = par;
                    par->parent = sibling;

                    sibling->colour = par->colour;
                    par->colour = 'b';
                    sibling->right->colour = 'b';
                }
            }
            else{
                 // If sibling is red, change it to black
                if(colour(sibling) == 'r'){
                    // Right rotation at parent
                    par->left = sibling->right;
                    if(sibling->right) sibling->right->parent = par;
                    if(par == par->parent->left) par->parent->left = sibling;
                    else par->parent->right = sibling;
                    if(par == root){
                        root = sibling;
                        sibling->parent = sibling;
                    }
                    sibling->right = par;
                    par->parent = sibling;

                    // make parent red and sibling black
                    sibling->colour = 'b';
                    par->colour = 'r';

                    // new sibling is now right child of parent
                    sibling = par->left;
                }
                // At this point, sibling must be black
                // If both children of sibling are black
                if(colour(sibling->left) == 'b' && colour(sibling->right) == 'b'){
                    // Handle main case 1
                    par->colour = 'b';
                    sibling->colour = 'r';
                }
                // If atleast one child of sibling is red
                else{
                    // If left child of sibling is black, make it red
                    if(colour(sibling->left) == 'b'){
                        // Left rotation at sibling
                        Node* right_child = sibling->right;
                        sibling->right = right_child->left;
                        right_child->left->parent = sibling;
                        right_child->parent = par;
                        par->left = right_child;
                        right_child->left = sibling;
                        sibling->parent = right_child;

                        // make sibling red and left_child black
                        sibling->colour = 'r';
                        right_child->colour = 'b';

                        // right_child becomes the new sibling
                        sibling = right_child;
                    }
                    // At this point left child of sibling must be red

                    // Handle main case 2
                    
                    // Right rotation at parent
                    par->left = sibling->right;
                    if(sibling->right) sibling->right->parent = par;
                    if(par == par->parent->left) par->parent->left = sibling;
                    else par->parent->right = sibling;
                    if(par == root){
                        root = sibling;
                        sibling->parent = sibling;
                    }
                    sibling->right = par;
                    par->parent = sibling;

                    sibling->colour = par->colour;
                    par->colour = 'b';
                    sibling->right->colour = 'b';
                }
            }
        }
    }
}
void RBT::InsertMany(int val){
    if(size == 0){
        root = new Node(val);
        root->parent = root;
    }
    else{
        Node* node = new Node(val, 'r');
        Node* par = root;
        Node* grand_par = NULL;
        Node* uncle = NULL;

        bool inserted = false;
        while(!inserted){
            if(par->val < node->val){
                if(par->right) par = par->right;
                else { par->right = node; inserted = true; }
            }
            else{
                if(par->left) par = par->left;
                else { par->left = node; inserted = true; }
            }
        }
        node->parent = par;
        if(par != root) grand_par = par->parent;
        if(grand_par != NULL) uncle = (grand_par->left == par) ? grand_par->right : grand_par->left;
        
        // Re-colour
        while(colour(par) == 'r' && node != root){
            if(colour(uncle) == 'r'){
                par->colour = grand_par->colour;
                uncle->colour = grand_par->colour;
                grand_par->colour = 'r';
                node = grand_par;
                par = node->parent;
                grand_par = par->parent;
                if(par == root) break;
                else uncle = (grand_par->left == par) ? grand_par->right : grand_par->left;
            }
            else{
                // Non trivial case
                if(par == grand_par->left){
                    if(node == par->left){
                        // Right rotaion on grand parent
                        grand_par->left = par->right;
                        par->right = grand_par;

                        if(grand_par != root){
                            if(grand_par == grand_par->parent->left) grand_par->parent->left = par;
                            else grand_par->parent->right = par;
                            par->parent = grand_par->parent;
                        }
                        else { par->parent = par; root = par; }

                        grand_par->parent = par;
                        if(grand_par->left) grand_par->left->parent = grand_par;

                        grand_par = par->parent;
                        uncle = (grand_par->left == par) ? grand_par->right : grand_par->left;

                        par->colour = 'b';
                        if(par->right) par->right->colour = 'r';
                    }
                    else{
                        // Left rotation on parent
                        par->right = node->left;
                        node->left = par;
                        grand_par->left = node;
                        node->parent = grand_par;
                        par->parent = node;
                        if(par->right) par->right->parent = par;

                        node = par;
                        par = node->parent;
                    }
                }
                else{
                    if(node == par->right){
                        // Left rotaion on grand parent
                        grand_par->right = par->left;
                        par->left = grand_par;
                        if(grand_par != root){
                            if(grand_par == grand_par->parent->left) grand_par->parent->left = par;
                            else grand_par->parent->right = par;
                            par->parent = grand_par->parent;
                        }
                        else { par->parent = par; root = par; }

                        grand_par->parent = par;
                        if(grand_par->right) grand_par->right->parent = grand_par;

                        grand_par = par->parent;
                        uncle = (grand_par->left == par) ? grand_par->right : grand_par->left;

                        par->colour = 'b';
                        if(par->left) par->left->colour = 'r';
                    }
                    else{
                        // Right rotation on parent
                        par->left = node->right;
                        node->right = par;
                        grand_par->right = node;
                        node->parent = grand_par;
                        par->parent = node;
                        if(par->left) par->left->parent = par;

                        node = par;
                        par = node->parent;
                    }
                }                
            }
        }
        root->colour = 'b';
    }
    size++;
}
