#pragma once

#include <iostream>
#include <string>

using namespace std;

template<typename T>
class dabba
{
public:

	T data;
	dabba * next;

	dabba(T D, dabba*N = 0)
	{
		data = D;
		next = N;
	}
};

template<typename T>
class linklist
{

private:
	dabba<T> *front;
	dabba<T> *tail;

	int  FindmaxRec(int max, dabba<T> * start)
	{

		if (start->next == nullptr)
			return max;

		else
		{
			if (max < start->data)
				max = start->data;

			FindmaxRec(max, start->next);
		}
	}

public:

	linklist()
	{
		front = nullptr;
		tail = nullptr;
	}

	bool isempty()
	{
		return front == nullptr;
	}

	void insertatFront(T D)
	{
		if (isempty())
			tail = front = new dabba<T>(D);
		else
			front = new dabba<T>(D, front);
	}


	void insertatTail(T D)
	{
		if (tail == 0)
			tail = front = new dabba<T>(D);
		else
		{
			tail = tail->next = new dabba<T>(D);
		}
	}

	

	int Findmaxvalue()
	{
		if (isempty())
			return 0;
		else
			return 	FindmaxRec(front->data, front);
	}

	void deletefromFront()
	{
		if (isempty())
			return;

		dabba<T> *temp = front;
		front = front->next;

		delete temp;

		if (front == 0)
			tail = 0;
	}

	void printlist()
	{
		printrec(this->front);
	}

	T getFrontValue()
	{
		if (!isempty())
			return front->data;
		else
			return -1;
	}

	T  getTailValue()
	{
		if (!isempty())
			return tail->data;
		else
			return -1;
	}


	void deletefromTail()
	{
		if (isempty())
			return;

		if (tail == front)
		{
			delete tail;  // resetting list 
			front = 0;
			tail = 0;
		}
		else
		{
			dabba<T> *pre = front;
			while (pre->next != tail)
			{
				pre = pre->next;
			}

			delete tail;
			tail = pre;
			tail->next = 0;

		}
	}
	
	void deleteAt(T key)
	{
		if (isempty())
			return;

		if (front->data == key)
		{
			deletefromFront();
			return;
		}


		if (tail->data == key)
		{
			deletefromTail();
			return;
		}



		dabba <T> *pre = 0;
		dabba <T> *current = front;   // finding current to dekl node at current key at current->next 

		while (current->data != key)
		{
			pre = current;
			current = current->next;

			if (current == 0)
				return;
		}

		pre->next = current->next;
		current->next = 0;
		delete current;

	}

	dabba<T> * serch(T key)
	{
		dabba<T>*temp = front;

		while (temp->data != key)
		{
			temp = temp->next;
			if (temp == 0)
				return 0;
		}
		return temp;
	}


};

template<typename T>
void printrec(dabba<T>* temp)
{
	if (temp == 0)
	{
		cout << " X ";
		return;

	}
	cout << temp->data << " ---> ";
	printrec(temp->next);
}
