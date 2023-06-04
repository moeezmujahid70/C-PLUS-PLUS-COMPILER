#include "Parser.h"
#include "Parser.h"


void Check_file(fstream &fin, char * file);
Token get_Token(string token_type = "");  //get token from lex


Parser::Parser() :S(150)       //constructor for parser stack initial size 150
{

	S.push(777);              //pushing $  and start of grammer
	S.push(-1);
}

void Parser::init_parser(char * table , char * map , char * grammer)
{
	make_LL1_Table(table);
	set_colmap(map);                // as lex return strings type token so colmap will help to convert these
	set_CFG(grammer);               //strings to assigned numbers 
}

void Parser::set_colmap(char * filename)
{
	string str;
	int id=0;

	fstream file;
	file.open(filename, ios::in);
	Check_file(file, filename);

	while (!file.eof())
	{
		file >> str;
		file >> id;
		colmap[str] = id;
	}

	file.close();
}

void Parser::set_CFG(char * filename)           //loading grammer in integer format
{
	fstream file;
	file.open(filename, ios::in);
	Check_file(file, filename);

	int data=0;
	vector <int> rowVector; // vector to add into 'array' (represents a row)
	
	// Read file
	// Dynamically store data into arraa
	while (!file.eof()) { // ... and while there are no errors,
		
		while (1) {
			file >> data; 

			if (data == end_of_production) //-999
				break;

			rowVector.push_back(data);
		}
		CFG.push_back(rowVector); // add a new row,
		rowVector.clear();
	}
	
	file.close();
}


void Parser::make_LL1_Table(char * filename)         // making an LL1 parsing table
{
	int records = 0, col = 0;
	
	fstream file;
	file.open(filename, ios::in);
	Check_file(file, filename);

	file >> records;
	file >> col;

	vector <int> rowVector(col); // vector to add into 'array' (represents a row)
	int row = 0; // Row counter

	// Read file

	// Dynamically store data into arraa
	while (row <= records) { // ... and while there are no errors,
		LL1.push_back(rowVector); // add a new row,
		for (int c = 0; c < col; c++) {
			file >> LL1[row][c]; // fill the row with col elements
		}
		row++; // Keep track of actual row 
	}

	file.close();
}

void Parser::print_LL1_table() const
{
	cout << endl;
	for (int i = 0; i < LL1.size(); i++)
	{
		for (int j = 0; j < LL1[i].size(); j++)
		{
			cout << setw(3) << LL1[i][j] << " ";
		}
		cout << endl;
	}
}

void Parser::print_colmap() 
{
	map<string, int>::iterator itr;
	cout << "\nThe map tabel is : \n";

	for (itr = colmap.begin(); itr != colmap.end(); ++itr) {
		cout << '\t' << itr->first
			 << '\t' << itr->second << '\n';
	}
	cout << endl;

}


void Parser::print_CFG() const
{
	cout << endl;
	for (int i = 0; i < CFG.size(); i++)
	{
		cout << i << " ---> ";
		for (int j = 0; j < CFG[i].size(); j++)
		{
			cout << setw(3)<< CFG[i][j] << " ";
		}
		cout << endl;
	}
}

Parser::~Parser()
{
	cout << "PARSER dist called " << endl;
	
	for (int i = 0; i < LL1.size(); i++)
	{
		vector<int>().swap(LL1[i]);
	}

	for (int i = 0; i < CFG.size(); i++)
	{
		vector<int>().swap(CFG[i]);
	}
}

Token T2; // global token to handle special cases

void Parser::parse(char * tk, char * err)   //this function will get token from lexical and send 
                                            //valid tokens to another fuction to check its syntax
{                                           
	ofstream f_token, f_error;
	f_token.open(tk, ios::trunc); // trunc mode 
	f_error.open(err, ios::trunc);
	
	bool error=0;

	if (!f_token.is_open() || !f_error.is_open())
	{
		cout << "Unable to open output files" << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	Token T;
	T = get_Token();

	do
	{
		T2 = get_Token();   //peeking the next token 

		if (T.get_error() == 1)
		{
			f_error << T;           
			
		}

		else if (T.get_error() == 0)
		{
			f_token << T;             //printing valid tokens in file

			error=Syntax_match(T);     //checking sytax of the code



			if (error)
				f_error << "Symtax error : " << T;
				
		}

		cout << T;

		T = T2;

	} while (T.get_error() >= 0);
	//error is -1 when no more input stream left ....
	f_token.close();
	f_error.close();
}

int Parser::get_token_id(Token & T,string & t) //converting token string id to assigned integer id
{
	t = T.get_Token_type();

	if (t == "keyword")
		t = T.get_Token_value();

	int input = -1;

	try {
		input = colmap[t];

		//cout << endl << colmap[t];
	}
	catch (const out_of_range &e)
	{
		input = -1;
		cerr << "Exception at " << e.what() << endl;
	}

	if (T.get_Token_type() != "id" &&  input == 0)
	{
		input = -1;
	}

	 return input;
}

bool Parser::Syntax_match(Token & T)  //0 return if syntax matched
{
	int rule = 0 , r=0 , focus=0;
	string t;
	int input = -1;
	input = get_token_id(T,t);

	cout << endl << input <<" -- "<< t<< endl;
	
	if (input < 0)
		return 1;

	while (focus != 777)
	{
	cout << S;  //printing stack;
	cout <<setw(3) <<"   ----->   " << t;
	cout << endl;

	focus = S.TOP();

	if (focus == input)
	{
		S.pop(r);
		return 0;
	}

	else if (focus < 0)          //if stack top is non terminal
	{
			try
			{
				rule = LL1[abs(focus)][input];

				//check if pop or skip rule triggered

				//panic mode
				if (rule == skip_rule)
					break;

				if (rule == pop_rule)
				{
					S.pop(r);
					continue;
				}
				//--------------------------------------------

				if (focus == -17 && T2.get_Token_value() != ":=")  //if focus == Expr
				{	rule++; }


				S.pop(r);

				for (auto ir = CFG[rule].rbegin(); ir != CFG[rule].rend(); ++ir)
				{
					if (*ir != 666)
						S.push(*ir);
				}

			}
			catch (const std::exception& e)
			{
				cerr <<endl<< "Exception at " << e.what() << endl;
			}

		}

	else           // (focus > 0)  means both are terminals that didnot matched
	{
		
		cout << "---stuck---";
		cout << endl;
		break;
		//system("pause");
	}

	}

	return 1;
}