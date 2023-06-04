#pragma once
#include "linklist.h"

// using linklist to implement hashing with chaining ...

class Hash
{
public:
	 int t_size;    
	 linklist<string> *table;
	
      Hash(int b)
	{
		this->t_size = b;
		table = new linklist<string>[t_size];
	}


	void insertItem(string key)
	{
		int x = key[0];
		int index = hashFunction(x);
		table[index].insertatTail(key);
	}

	void displayHash() const {
		for (int i = 0; i < t_size; i++) {
			cout << i<<" ";
			table[i].printlist();
			cout << endl;
		}
	}

	bool Find(string key)
	{
		int x = key[0];
		int index = hashFunction(x);
		return table[index].serch(key);
	}

private:

	int hashFunction(int x) {
		return (x % t_size);
	}

};

