#include <atomic>
using namespace std;

struct Node {
	atomic<int> value;
	atomic<Node*> next;

	Node(int value, Node* next) {
		this->value.store(value);
		this->next.store(next);
	}
};

class AtomicList {
private:
	atomic<Node* > header;

public:
	AtomicList();

	void push(int value);
	int pop();
	void display();
};
	
