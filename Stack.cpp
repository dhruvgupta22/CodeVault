#include <iostream>
using namespace std;

template <typename T>
class Stack{
private:
	class SNode{
		public:
			T val;
			SNode* prev;
	};

	SNode* top;
	int length;
	
public:
	Stack(){
		length = 0;
		top = NULL;
	}
	bool Empty();
	int Size();
	T Top();
	void Push(T val);
	void Pop();
	void Display();
};

int main(){
	Stack<string> S;
	string x;
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

template <typename T>
bool Stack<T>::Empty(){
	return (!top);
}

template <typename T>
int Stack<T>::Size(){
	return length;
}

template <typename T>
T Stack<T>::Top(){
	return top->val;
}

template <typename T>
void Stack<T>::Push(T val){
	SNode* new_node = new SNode;
	new_node->val = val;
	new_node->prev = top;
	top = new_node;
	length++;
}

template <typename T>
void Stack<T>::Pop(){
	if(!top) return;
	
	SNode* node = top;
	top = top->prev;
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
void Stack<T>::Display(){
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
