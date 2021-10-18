#include <new>
#include <iostream>
#pragma once

using namespace std;
template <class T>
class MyStack
{
public:
	MyStack() {
		this->pointer = nullptr;
		this->size = 0;
	}

	void push(T data) {
		T* tmpPointer;
		try{
			tmpPointer = this->pointer;
			this->pointer = new T[this->size + 1];
			this->size++;
			for (int i = 0; i < this->size - 1; i++) {
				this->pointer[i] = tmpPointer[i];
			}
			this->pointer[this->size - 1] = data;
			if (this->size > 1) {
				delete[] tmpPointer;
			}
		}
		catch (bad_alloc e) {
			cout << e.what() << endl;
		}
	}

	T pop() {
		if (this->isEmpty()) {
			throw exception("Stack does`nt have elements to delete!");
		}
		this->size--;
		return this->pointer[this->size];
	}

	T head() {
		if (this->isEmpty()) {
			throw exception("Stack does`nt have elements to show head element!");
		}
		return this->pointer[this->size - 1];
	}

	MyStack(const MyStack& copy) {
		try {
			this->pointer = new T[copy.size];
			this->size = copy.size;
			for (int i = 0; i < this->size; i++) {
				this->pointer[i] = copy.pointer[i];
			}
		}
		catch (bad_alloc e) {
			cout << e.what() << endl;
		}
	}

	MyStack operator=(const MyStack& copy) {
		if (this->size > 0) {
			this->size = 0;
			delete[] this->pointer;
		}
		try {
			this->pointer = new T[copy.size];
			this->size = copy.size;
			for (int i = 0; i < this->size; i++) {
				this->pointer[i] = copy.pointer[i];
			}
		}
		catch (bad_alloc e) {
			cout << e.what() << endl;
		}
		return *this;
	}

	int getSize() {
		return this->size;
	}

	bool isEmpty() {
		return (this->size == 0);
	}

	void Print() {
		T* tmpPointer;
		tmpPointer = this->pointer;
		cout << "Stack:" << endl;
		if (this->isEmpty()) {
			cout << "is empty now." << endl;
		}

		for (int i = 0; i < this->size; i++) {
			cout << "Item " << i << " is " << *tmpPointer << endl;
			tmpPointer++;
			if (i == this->size - 1) {
				cout << endl;
			}
		}
	}

	~MyStack() {
		if (this->size > 0) {
			delete[] this->pointer;
		}
	}

private:
	T* pointer;
	int size;
};

