#pragma once

#include <string>
using namespace std;

class State
{
public:
	bool isAccepting;
	string T_type;
	bool rollback;


	State(bool accept = 0, string type = "",bool back=0)
	{
		isAccepting = accept;
		T_type = type;
		rollback = back;
	}

	void set_state(bool accept = 0, string type = "", bool back = 0)
	{
		isAccepting = accept;
		T_type = type;
		rollback = back;
	}

	void print_state_status()const
	{
		cout << "(" << isAccepting << ",";
		cout << T_type << ",";
		cout <<rollback<<")";

		cout << endl;
	}
};

