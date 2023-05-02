#include <atomic>
using namespace std;

#ifndef NULL
#define NULL 0
#endif

struct Node {
	int value;
	Node* next;

	Node(int value) :value(value), next(nullptr) {}
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
	
