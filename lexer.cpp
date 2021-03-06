/* 
Group Members:
Paul Lindberg
Kunal Matthews
Jason Eirich

Project 1: Lexical analyzer which takes in characters form an input file, reads 
the file character by character and decipher what Lexeme/Token pair they are. This 
pair is written out to the output file and is seperate in the same way stated above.*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

class Lex {
private:
	//2 dimensional state table which shows all possible states and inputs
	int table[13][27] = {
		{ 2,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,6,1,5,1,1,1 },
	{ 2,7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,7,9,9,9 },
	{ 10,3,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,10,10,10,10,10,10,10,10 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,12,6,6,6,6,12 },
	{ 7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,8,8,8 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 13,11,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }

	};

	std::ofstream outputStream;
	std::ifstream inputStream;
	char c;
	char arr[30];
	std::string test = "while";

public:
	Lex(std::string, std::string);
	char getChar();
	~Lex();
	void flushArray();
	void DFSM();
	int char_to_col(char x);
	int final_state(int state);
	void parse(int state, int index);
	bool searchKeyword(char keyword[]);
};

//cleans the array used to store characters for use with functions
void Lex::flushArray() {
	for (int i = 0; arr[i] != '\0'; i++) {
		if (arr[i] != '\0')
			arr[i] = '\0';
	}
	return;
}

/*receives and array of characters that is read in from the input file and 
iteratively checks it against the key array which contains all of the keywords
in the RAT18 language*/
bool Lex::searchKeyword(char keyword[]) {
	//Declare string array that contains all keywords.
	std::string key[15] = { "int", "float", "bool", "if", "else", "then", "do",
		"while", "whileend", "do", "doend", "for", "and", "or", "function" };

	std::string word;
	/*take every element from the refrenced array and concatinate them
	to create a string*/
	for (int i = 0; i <= 30; i++) {
		if (keyword[i] != '\0')
			word = word + keyword[i];
	}
	//compare the string with the key array
	for (int j = 0; j <= 14; j++) {
		if (word == key[j])
			return true;
	}
	return false;
}


Lex::~Lex() {
	inputStream.close();
	outputStream.close();
}

char Lex::getChar() {
	char i;
	inputStream.get(i);
	return i;
}

Lex::Lex(std::string a, std::string b) {
	inputStream.open(a);
	if (inputStream.fail()) {
		std::cout << "Failed to open file, inputfile does not exist" << std::endl;
		exit(-1);
	}
	outputStream.open(b);
	outputStream << "TOKENS" << std::setw(25) << "LEXEMES" << std::endl;
	outputStream << "_____________________________" << std::endl;
}

//Logic behind the state table, used to switch states
int Lex::char_to_col(char x) {
	if (x == -52)
		return 26;
	if (isalpha(x))
		return 0;
	if (isdigit(x))
		return 1;
	if (x == '*')
		return 2;
	if (x == '+')
		return 3;
	if (x == '-')
		return 4;
	if (x == '=')
		return 5;
	if (x == '/')
		return 6;
	if (x == '>')
		return 7;
	if (x == '<')
		return 8;
	if (x == '%')
		return 9;
	if (x == 39)
		return 10;
	if (x == '(')
		return 11;
	if (x == ')')
		return 12;
	if (x == '{')
		return 13;
	if (x == '}')
		return 14;
	if (x == '[')
		return 15;
	if (x == ']')
		return 16;
	if (x == ',')
		return 17;
	if (x == '.')
		return 18;
	if (x == ':')
		return 19;
	if (x == ';')
		return 20;
	if (x == '!')
		return 21;
	if (x == ' ')
		return 22;
	if (x == '$')
		return 23;
	if (x == '\n')
		return 24;
	if (x == '\t')
		return 25;
	else
		return -1;

}

int Lex::final_state(int state) {
	int finals[] = { 4,5,8,9,10,12, 13 };
	for (int i = 0; i < 7; i++) {
		if (state == finals[i]) {
			return state;
		}
	}
	return 0;
}


void Lex::parse(int state, int index) {
	switch (state) {
	case(4):
		outputStream << "Operator  " << std::setw(20) << arr << std::endl;
		break;
	case(5):
		outputStream << "Separator " << std::setw(20) << arr << std::endl;
		break;
	case(8):
		arr[index] = '\0';
		outputStream << "Identifier" << std::setw(20) << arr << std::endl;
		break;
	case(9):
		arr[index] = '\0';
		if (searchKeyword(arr)) {
			outputStream << "Keyword   " << std::setw(20) << arr << std::endl;
		}
		else
			outputStream << "Identifier" << std::setw(20) << arr << std::endl;
		break;
	case(10):
		arr[index] = '\0';
		outputStream << "Integer   " << std::setw(20) << arr << std::endl;
		break;
	case (13):
		arr[index] = '\0';
		outputStream << "Float   " << std::setw(20) << arr << std::endl;
	case(12):
		break;
	}
}

/*DFSM function which drives the state switchig algoritim. The initial state is 1
and as the function procedes it reads the input character by character and switches states 
according to the results received from the functions above.*/
void Lex::DFSM() {
	int index = 0;
	int state = 1;
	int col = 0;
	char x;
	while (!inputStream.eof()) {
		x = getChar();
		col = char_to_col(x);

		state = table[state - 1][col];
		while (arr[index] != '\0')
			++index;
		if (state != 6 && x != '!' && x != '\n' && x != ' ' && x != '\t' && x > 0)
			arr[index] = x;


		if (final_state(state)) {
			if (state == 8 || state == 9 || state == 10 || state == 13)
				if (x > 0)
					inputStream.putback(x);
			parse(state, index);
			state = 1;
			index = 0;
			flushArray();

		}
	}
}


int main()
{
	Lex open("inputfile.txt", "outputfile.txt");

	open.DFSM();
	open.flushArray();

	return 0;
}
