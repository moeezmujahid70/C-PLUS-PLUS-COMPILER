#include "Scanner.h"
void Check_file(fstream &fin, char * file);


Scanner::Scanner():MI(128,0),S(total_states),key_hash(26),
         buffer(BUFFER_SIZE + 1, 0),lex(""),st(0),curr_state(nullptr)
{
}

void Scanner::set_Keyword(char * filename)  //stores keywors specified in file to a hash
{
	fstream file;
	string  k_word;

	file.open(filename, ios::in);
	Check_file(file,filename);

	while (!file.eof())
	{
		file >> k_word;
		this->key_hash.insertItem(k_word);
	}
}

void Scanner::make_Transition_Table(char * filename, int & records, int & col)

{
	fstream file;
	file.open(filename, ios::in);
	Check_file(file,filename);

	file >> records;
	file >> col;

	vector <int> rowVector(col); // vector to add into 'array' (represents a row)
	int row = 0; // Row counter

	// Read file

	// Dynamically store data into arraa
	while (row <= records ) { // ... and while there are no errors,
		TT.push_back(rowVector); // add a new row,
		for (int c = 0; c < col; c++) {
			file >> TT[row][c]; // fill the row with col elements
		}
		row++; // Keep track of actual row 
	}

	file.close();
}

void Scanner::print_trans_table() const
{
	cout << endl;
	for (int i = 0; i < TT.size(); i++)
	{
		for (int j = 0; j < TT[i].size(); j++)
		{
			cout << setw(3) << TT[i][j] << " ";
		}
		cout << endl;
	}
}

void Scanner::make_MI_table(char * filename)
{
	fstream file;
	file.open(filename, ios::in);
	Check_file(file,filename);
	int val;
	for (int i = 0; i < MI.size(); i++)
	{
		file >> val;
		MI[i] = val;
	}
	file.close();
}



void Scanner::print_MI() const
{
	for (int i = 0; i < MI.size(); i++)
	{
		cout << setw(1) << i << ":  " << MI[i];
		cout << endl;
	}
	cout << endl;
}

void Scanner::set_states(char * filename)
{
	fstream file;
	file.open(filename, ios::in);
	Check_file(file,filename);

	int start = 0;
	string st = "";
	bool rollback = 0;

	file >> start;

	//cout << endl << start;
	int len = S.size();

	while (start < len && !file.eof())
	{
		file >> st;
		file >> rollback;

		S[start].set_state(1, st, rollback);
		++start;
	}
	// to handle lexical error;
	//22 state defines an error state
	S[error_state].set_state(1, "error", 1);
	file.close();
}


void Scanner::print_buffer()
{
	vector<char>::iterator i;
	for (i = buffer.begin(); i != buffer.end(); ++i)
	{
		cout << *i;
	}

	cout << endl;
}

void Scanner::print_states_status() const
{
	cout << endl;
	int len = S.size();
	for (int i = 0; i < len; i++)
	{
		S[i].print_state_status();
	}
	cout << endl;
}

void Scanner::print_key_hash() const
{
	key_hash.displayHash();
}


void Scanner::initialize_Compiler(char * file1, char * file2, char * file3, char * file4,char * file5)
{
	int r = 0, c = 0;
	make_Transition_Table(file1, r, c);
	//cout << r << " ---- " << c << endl;

	make_MI_table(file2);     // making mapping table
	set_states(file3);        // setting accepting states information
	set_Keyword(file4);       

	input.open(file5, ios::in); //loading code file 
	Check_file(input, file5);

	load_buffer(); //loading buffer -- code 
}

bool Scanner::load_buffer()
{
	if (!input.eof())
	{
		input.read(buffer.data(), buffer.size());
		std::streamsize st_size = input.gcount();

		//cout << endl << "stsize" << st_size << " " << endl;
		//print_buffer();
		buffer.resize(st_size);

		fwd = buffer.begin();
		return 1;
	}
	
	return 0;
}

Token Scanner::Next_Token()
{

	 char ch;
	 Token T;

	while (fwd < buffer.end() || load_buffer())
	{
		//skipping spaces
		if ((st == 0 || st==CIN || st==COUT) && (*fwd == ' ' || *fwd == '\n'))
		{
			fwd++;
			continue;
		}


		ch = *fwd;
		st = TT[st][MI[ch]];
		curr_state = &S[st];
		lex = lex + ch;

		// cheepii to avoid undefined char  recheck in future
		if (st == error_state && MI[ch]==undefined)
		{
			st = 0;
			fwd++;
			T.set_Token("undifined lex", lex);
			T.set_error(1);
			return T;
		}


		if (curr_state->isAccepting)  //if current stste is accepting state ...
		{
			if (curr_state->rollback)
				lex.pop_back();

			if (curr_state->T_type == "keyword")
			{
				if (!key_hash.Find(lex))
					if(special_cases()) continue; //states info changed here..
					//curr_state = &S[error_state];
			}
			
			if (curr_state->T_type == "error")
				T.set_error(1);

			T.set_Token(curr_state->T_type, lex);
			//T.print_Token();

			if (curr_state->rollback && *fwd != ' ')
				fwd--;

			reset();
			return T;
		}

		fwd++;

	}

	T.set_error(end_of_stream);
	return T;
}

bool  Scanner::special_cases()
{
	if (lex == "cout")
	{
		st = COUT;
		curr_state = &S[st];
		return 1;
	}

	else if (lex == "cin")
	{
		st = CIN;
		curr_state= &S[st];
		return 1;
	}
	else if (lex == "endl")
	{
		lex = "";
		st = 0;
		curr_state = &S[st];
		return 1;
	}

	curr_state = &S[error_state];
	return 0;

}

void Scanner::reset()
{
	lex = "";
	st = 0;
	curr_state = nullptr;
	fwd++;
}


Scanner::~Scanner()
{
	cout << "scanner dist called "<<endl;
	vector<char>().swap(buffer);
	vector<int>().swap(MI);
	vector<State>().swap(S);

	for (int i = 0; i < TT.size(); i++)
	{
		vector<int>().swap(TT[i]);
	}

	if (input.is_open())
	{
		input.close();
	}
	
	curr_state = nullptr;
	lex.clear();
}