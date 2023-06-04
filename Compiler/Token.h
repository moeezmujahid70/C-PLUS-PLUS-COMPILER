#pragma once

#include <string>
using namespace std;

class Token
{

private:
	string type;
	string value;
	int error;

public:
	
	/*
	error attr defines 3 things
	1 -> error in identified Token e.g unknown symbol incomplete identifier..
	0-> no error -> token is valid
	-1-> no input stream left to make token ...
	*/
	

	Token(string t_type = "", string  val = "", int err = 0)
	{
		type = t_type;
		value = val;
		error = err;
	}

	Token(const Token &t)
	{
		type=t.type;
		value = t.value;
		error = t.error;
	}

	//for setting token type and val ... 
	void set_Token(string t_type="", string  val="")
	{
		type = t_type;
		value = val;
	}

	void set_error(int err)
	{
		error = err;
	}

	int get_error()const
	{
		return error;
	}

	string get_Token_type()const
	{
		return type;
	}

	string get_Token_value()const
	{
		return value;
	}

	friend ostream &operator<<(ostream &out, const Token &T)
	{
		out << "< " << T.type << "," << T.value << " >";
		out << endl;
		return out;
	}

	~Token()
	{
		type = "";
		value = "";
	}

private:

};