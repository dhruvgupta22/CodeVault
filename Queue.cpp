#include <iostream>
using namespace std;

class QNode{
public:
    int val;
    QNode* next = NULL;
};

class Queue{
private:
    QNode* front;
    QNode* back;
    int length;
public:
    Queue(){
        length = 0;
        front = NULL;
        back = NULL;
    }
    bool Empty();
    int Size();
    int Front();
    void Enqueue(int val);
    void Dequeue();
    void Display();
};

int main(){
    Queue Q;
    int x;
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

bool Queue::Empty(){
    return !front;
}
int Queue::Size(){
    return length;
}
int Queue::Front(){
    return front->val;
}

void Queue::Enqueue(int val){
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
void Queue::Dequeue(){
    if(!front) return;

    QNode* node = front;
    front = front->next;
    delete node;
    length--;
}

void Queue::Display(){
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