#include <iostream>
#include <bits/stdc++.h>
using namespace std;

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
    if(node) cout<<node->val<<node->colour<<node->parent->val<<" "; else cout<<"null ";
}

class RBT{
public:
    Node* root = NULL;
    int size = 0;
    // void Make_BST(int arr[], int n);
    void Insert(int val);
    void Delete(int val);
    Node* Successor(int val);
    Node* Predecessor(int val);
    Node* Search(int val);
    int Min();
    int Max();
    int Height();

    void LevelOrder();
    void Inorder(Node* root);
    void PreOrder();
    void PostOrder();
};

int main(){
    RBT Tree;
    int x;
    while(true){
        cin>>x;
        Tree.Insert(x);
        Tree.Inorder(Tree.root);
        cout<<Tree.size<<endl;
    }
    return 0;
}

void RBT::Inorder(Node* root){
    Node* node = root;
    if(node){
        Inorder(node->left);
        print(node);
        Inorder(node->right);
    }
}

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