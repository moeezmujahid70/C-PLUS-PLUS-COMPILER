#pragma once
#include "lib.h";

class Scanner
{
private:
	vector<int> MI;
	vector<State> S;
	Hash key_hash;
	vector<char> buffer;
	
	string lex;
	int st;
	State * curr_state;
	vector<vector<int>> TT;
	fstream input;

	void set_Keyword(char * filename);
	void make_Transition_Table(char * filename, int & records, int & col);
	void set_states(char * filename);
	void make_MI_table(char * filename);
	void reset();
	bool special_cases();

public:
	
	vector<char>::iterator fwd;   //forward pointer
	

	Scanner();
	~Scanner();

	
	void print_trans_table()const;
	void print_key_hash()const;
	void print_MI()const;
	void print_buffer();
	void print_states_status()const;
	void initialize_Compiler(char * Trans, char * MI, char *states, char * keyword,char * code);

	bool load_buffer();
	Token Next_Token(); //make a new token and return to parser
};

