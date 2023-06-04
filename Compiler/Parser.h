#pragma once

#include"lib.h"
#include <map>
#include "Stack.h"

class Parser
{


private:
	map<string, int> colmap;
	vector<vector<int>> LL1;
	vector<vector<int>> CFG;
	Stack<int> S;

	void make_LL1_Table(char * filename);
	void set_colmap(char * );
	void set_CFG(char *);
	bool Syntax_match(Token &);
	int get_token_id(Token & , string & );

public:
	Parser();
    ~Parser();


	void parse(char * tk, char * err );
	void print_LL1_table()const;
	void print_colmap();
	void print_CFG()const;
	void init_parser(char *  , char * ,char *);
};

