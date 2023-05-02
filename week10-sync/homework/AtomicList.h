#include <atomic>
using namespace std;

// 定义节点
struct Node {
	int value;
	Node* next;

	Node(int value) :value(value), next(nullptr) {}
};

// 定义原子链表
class AtomicList {
private:
	// 使用原子变量来存储链表
	atomic<Node* > header;

public:
	AtomicList();

	void push(int value);
	int pop();
	void display();
};
	
