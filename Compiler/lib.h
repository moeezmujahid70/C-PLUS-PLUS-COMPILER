#pragma once
#include <cstdlib>
#include <fstream>

#include <iomanip>
#include <iostream>
#include <string>
#include <vector> 
#include <iterator>

#include "Token.h"
#include "State.h"
#include "Hash.h"

using namespace std;


#define end_of_stream -1
#define BUFFER_SIZE 1024

#define end_of_production -999

#define undefined 26
#define skip_rule 888
#define pop_rule  999

enum STATES {
	total_states = 83,
	COUT = 25,
	CIN = 23,
	error_state = 22
};

//used this file to define macros and to include dependencies