#pragma once
#include <iostream>
using namespace std;

template <class T>

class Stack
{
	int size;
	T * arr;
	int top; // current idx

public:
	Stack(int s)
	{
		if (s > 0)
			size = s;
		else
			size = 50;

		arr = new T[size];
		top = -1; //0

	}

	Stack(const Stack<T> & St)
	{
		size = strlen(St.arr) + 1;
		arr = new T[size];
		strcpy_s(arr, size, St.arr);
		top = St.top;
	}

	~Stack()
	{
		delete[] arr;
	}

	bool isempty()
	{
		return top < 0;

	}

	bool isfull()
	{
		return top == size - 1;
	}


	bool push(T value)
	{
		if (isfull())
		{
			cout << endl << "stack was full :" << endl;
			//this->spaceadj();
		}

		arr[++top] = value;
		return 1;
	}


	bool pop(T & vref)
	{
		if (isempty())
		{
			return 0;
			cout << endl << "stack is already emplty" << endl;
		}


		vref = arr[top];
		arr[top] = -1;
		top--;
		return 1;

	}
	
	T TOP()             // for peeking top value 
	{
		return arr[top];
	}

	void print()
	{
		cout << "stack : ";
		for (int i = 0; i <= top; i++)
		{
			cout << arr[i] << " ";
		}

	}

	int getTOP()
	{
		return this->top;
	}

	Stack<T> & operator=(const Stack<T> &s)
	{
		size = strlen(s.arr) + 1;
		arr = new T[size];
		strcpy_s(arr, size, s.arr);
		top = s.top;
		return *this;

	}

};

template <typename T>
ostream& operator << (ostream &out, Stack<T> &s)
{
	s.print();
	return out;
}
