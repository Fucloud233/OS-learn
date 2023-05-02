#include "AtomicList.h"
#include <iostream>

AtomicList::AtomicList() {
	header = NULL;
}

void AtomicList::push(int value) {
	// 1. 创建新的节点
	Node* new_node = new Node(value);
	// 2. 将原来的链表追加到新节点之后
	new_node->next = header.load();
	// 3. 比较当前的头节点和追加的头结点是否相同
	// 如果相同，更新链表头结点
	// 如果不相同，说明链表发生了变化，则将新的链表追加
	while(!header.compare_exchange_weak(new_node->next, new_node));
}

int AtomicList::pop() {
	// 0. 判断链表是否为空 防止出现段错误
	if(!header.load()) {
		cout<< "[Error] The list is empty!" << endl;
		return -1;
	}

	// 1. 将头结点替换成下一个
	Node* head_node = header.exchange(header.load()->next);
	// 2. 得到其值用于返回
	int value = head_node->value;
	// 3. 释放内存
	delete head_node;
	return value;
}

void AtomicList::display() {
	Node *cur = header.load();
	while(cur) {
		cout<< cur->value<<' ';
		cur = cur->next;
	}
	cout<<endl;
}
