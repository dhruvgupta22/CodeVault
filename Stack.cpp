#include <iostream>
using namespace std;

class SNode{
public:
	int val;
	SNode* prev;
};

class Stack{
private:
	SNode* top;
	int length;
public:
	Stack(){
		length = 0;
		top = NULL;
	}
	bool Empty();
	int Size();
	int Top();
	void Push(int val);
	void Pop();
	void Display();
};

int main(){
	Stack S;
	int x;
	char c;
	while(true){
		cin >> c;
		if(c == 'e'){
			cin >> x;
			S.Push(x);
		}
		else if(c == 'd'){
			S.Pop();
		}
		else break;
		S.Display();
		cout << "size = " << S.Size();
		if(!S.Empty()) cout << " top = " << S.Top();
		cout << endl;
	}
	return 0;
}

bool Stack::Empty(){
	return (!top);
}
int Stack::Size(){
	return length;
}
int Stack::Top(){
	return top->val;
}

void Stack::Push(int val){
	SNode* new_node = new SNode;
	new_node->val = val;
	new_node->prev = top;
	top = new_node;
	length++;
}
void Stack::Pop(){
	if(!top) return;
	
	SNode* node = top;
	top = top->prev;
	delete node;
	length--;
}

void Stack::Display(){
	if(!top){
		cout << "Stack is Empty!" << endl;
	}
	else{
		SNode* it = top;
		while(it){
			cout << it->val << " ";
			it = it->prev;
		}
		cout << endl;
	}
}