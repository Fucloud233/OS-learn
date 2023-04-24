#include <atomic>
#include <iostream>

using namespace std;

struct Node {
	atomic<int> value;
	atomic<Node *> next;

	Node(int value, Node* next) {
		this->value.store(value);
		this->next.store(next);
	}
};

int main() {
	atomic<Node *> header(new Node(-1, NULL));;
	int value = 5;
	
	// 这是一个原子类型呀	
	cout<< header.load()->next.load()<<endl;
	
	header.load()->next.store(new Node(value, header.load()->next.load()));
	
	// 访问头指针的下一个节点的value
	cout<< header.load()->next.load()->value<<endl;
//	Node* temp_node = new Node(atomic<int>(value), header);
//	header.exchange(new Node(atomic<int>(value), header));
}
