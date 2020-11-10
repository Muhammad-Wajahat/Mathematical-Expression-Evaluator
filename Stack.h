#pragma once
#include<iostream>
using namespace std;
#include"Node.h"

template <typename T>
class Stack
{
private:
	Node<T>* top;
public:
	Stack()
	{
		top = NULL;
	}
	bool isEmpty() {
		return (top == NULL);
	}
	void push(T value) {
		Node<T>* temp, *p;
		temp = new Node<T>;
		temp->data = value;
		p = top;
		if (isEmpty()) {
			top = temp;
			temp->next = NULL;
		}
		else {
			temp->next = NULL;
			temp->next = p;
			top = temp;
		}
	}
	T pop() {
		int value;
		Node<T>* p;
		if (isEmpty()) {
			return NULL;
		}
		else {
			p = top;
			value = p->data;
			top = p->next;
			delete p;
			return value;
		}
	}
	T getTop() {
		return top->data;
	}
	void print() {
		Node *p;
		p = top;
		if (isEmpty()) {
			cout << "STACK IS EMPTY!!" << endl;
		}
		else
		{
			cout << "TOS->";
			while (p != NULL) {
				cout << p->data << " | ";
				p = p->next;
			}
			cout << endl;
		}
	}
};