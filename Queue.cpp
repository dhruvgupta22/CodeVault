#include <iostream>
using namespace std;

template <typename T>
class Queue{
private:
    class QNode{
        public:
            T val;
            QNode* next = NULL;
    };

    QNode* front;   
    QNode* back;
    int length;
public:
    Queue<T>(){
        length = 0;
        front = NULL;
        back = NULL;
    }
    bool Empty();
    int Size();
    T Front();
    void Enqueue(T val);
    void Dequeue();
    void Display();
};

int main(){
    Queue<string> Q;
    string x;
    char c;
    while(true){
        cin>>c;
        if(c == 'e'){
            cin>>x;
            Q.Enqueue(x);
        }
        else if(c == 'd'){
            Q.Dequeue();
        }
        else break;

        Q.Display();
        cout << "size = " << Q.Size();
        if(!Q.Empty()) cout<< " front = " << Q.Front();
        cout << endl;
    }
    return 0;
}

template <typename T>
bool Queue<T>::Empty(){
    return !front;
}

template <typename T>
int Queue<T>::Size(){
    return length;
}

template <typename T>
T Queue<T>::Front(){
    return front->val;
}

template <typename T>
void Queue<T>::Enqueue(T val){
    QNode* new_node = new QNode;
    new_node->val = val;
    if(!front){
        front = new_node;
        back = new_node;
    }
    else{
        back->next = new_node;
        back = new_node;
    }
    length++;
}

template <typename T>
void Queue<T>::Dequeue(){
    if(!front) return;

    QNode* node = front;
    front = front->next;
    delete node;
    length--;
}

/*
 Note : For Display function to work, allowed datatypes for T are - 
 		1. int, long long int, unsigned int, etc.
		2. float, double, long double, etc.
		3. char, string
		In other words, all the primitive data types can be used.
		
		For all other functions any data type can be used.
*/
template <typename T>
void Queue<T>::Display(){
    if(!front){
        cout<<"Queue is Empty!"<<endl;
    }
    else{
        QNode* it = front;
        while(it){
            cout<<it->val<<" ";
            it = it->next;
        }
        cout<<endl;
    }
}