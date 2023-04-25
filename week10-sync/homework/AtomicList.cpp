#include "AtomicList.h"
#include <iostream>

AtomicList::AtomicList() {
	header.store(new Node(-1, NULL));
}

void AtomicList::push(int value) {
	header.load()->next.store(new Node(value, header.load()->next.load()));
}

int AtomicList::pop() {
	Node* cur = header.load()->next.load();
	
	int value = cur->value.load();
	header.load()->next.store(cur->next.load());
	
	delete cur;
	return value;
}

void AtomicList::display() {
	atomic<Node*> cur(header.load()->next.load());
	while(cur.load()) {
		cout<< cur.load()->value<<' ';
		cur.store(cur.load()->next.load());
	}
	cout<<endl;
}

void test() {
	AtomicList list;

	for(int i=0; i<5; i++) 
		list.push(i+1);
//	list.push(4);
	list.display();
	
	for(int i=0; i<5; i++)
		list.pop();

	list.display();

}
