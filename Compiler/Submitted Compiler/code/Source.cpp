#include "Scanner.h"
#include "Parser.h"


void Check_file(fstream &fin, char * file)  //check files for errors...
{
	if (!fin.is_open())
	{
		cout << endl << "Unable to open File :" << file << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
}


Scanner L;

Token get_Token(string token_type="")       //used by parser class to get token from scanner
{
	return L.Next_Token();
}

int main()
{
	

	char file1[] = "Transition.txt";
	char file2[] = "AsciiMap.txt";
	char file3[] = "states.txt";
	char file4[] = "keywords.txt";
	char file5[] = "Sourcecode.txt";
	char file6[] = "token.txt";
	char file7[] = "error.txt";
	char file8[] = "parsetable.txt";
	char file9[] = "LL1map_str2int.txt";
	char file10[] = "CFG_productions.txt";

	
	L.initialize_Compiler(file1, file2, file3, file4,file5);

	//L.print_trans_table();
	//L.print_MI();
	//L.print_states_status();
	L.print_buffer();
	//L.print_key_hash();

	Parser P;
	P.init_parser(file8,file9,file10);
	//P.print_LL1_table();
	//P.print_colmap();
	//P.print_CFG();
	
	
	P.parse(file6, file7);
	//L.~Scanner();


	cout << endl << endl;
	system("pause");
	return 0;

}