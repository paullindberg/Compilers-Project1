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
#include <vector>


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


	std::ifstream inputStream;
	char c;
	char arr[30];

public:
	std::ofstream outputStream;
	Lex(std::string, std::string);
	char getChar();
	~Lex();
	void flushArray();
	void DFSM();
	int char_to_col(char x);
	int final_state(int state);
	void parse(int state, int index);
	void sendtoGrammar(std::string name);
	bool First(std::string id);
	bool Follows(std::string id);
	bool searchKeyword(char keyword[]);
	void E();
	void Ep();
	void T();
	void Tp();
	void F();
	void S();
	bool WL();
	bool STATE();
	bool COND();
	bool EXP();
	void if_else();
	bool CheckSingleT(std::string input);
	int vptr = 0;
	bool KEY();
	struct token{
		std::string name;
		std::string type;
	};
	std::vector<token> tokens; //PURGE THIS WHEN A CORRECT GRAMMAR IS FOUND OR 
};

void Lex::S() {
	if (tokens[vptr].type == "Identifier") {
		outputStream << "Identifier" << std::setw(20) << tokens[vptr].name << std::endl;
		vptr++;
	}
	else {
		outputStream << "Error: ID Expected" << std::endl;
		exit(-1);
	}
	if (tokens[vptr].name == "=") {
		outputStream << "Operator" << std::setw(20) << "=" << std::endl;
		vptr++;
	}
	else {
		outputStream << "Error: = Expected" << std::endl;
		exit(-1);
	}
	outputStream << "S -> id = E" << std::endl;
	E();



}

bool Lex::Follows(std::string id) {
	if (id == "E" || id == "Ep") {
		if (tokens[vptr].type == "$" || tokens[vptr].name == ")" || tokens[vptr].name == ";")
			return true;
		else
			return false;
	}
	if (id == "T" || id == "Tp") {
		if (tokens[vptr].name == "+" || tokens[vptr].name == "-" || tokens[vptr].type == "$" || tokens[vptr].name == ")" || tokens[vptr].name == ";")
			return true;
		else
			return false;
	}
	if (id == "F") {
		if (tokens[vptr].name == "*" || tokens[vptr].name == "/" || tokens[vptr].name == "+" || tokens[vptr].name == "-" || tokens[vptr].type == "$" || tokens[vptr].name == ")" || tokens[vptr].name == ";")
			return true;
		else
			return false;
	}
}


bool Lex::First(std::string id) {
	if (id == "E" || id == "T" || id == "F") {
		if (tokens[vptr].name == "(" || tokens[vptr].type == "Identifier")
			return true;
		else
			return false;
	}
	if (id == "Ep") {
		if (tokens[vptr].name == "+" || tokens[vptr].name == "-")
			return true;
		else
			return false;
	}


	if (id == "Tp") {
		if (tokens[vptr].name == "*" || tokens[vptr].name == "/")
			return true;
		else
			return false;
	}


}







void Lex::sendtoGrammar(std::string name) {
	token item;
	item.name = arr;
	item.type = name;
	tokens.push_back(item);

}

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

void Lex::E()
{
	if (First("E")) {
		outputStream << "E -> TE'" << std::endl;
		T();
		Ep();
	}
	else {
		outputStream << "Error: token in First(E) expected " << std::endl;
		return;
	}
}



void Lex::Ep() {
	if (tokens[vptr].name == "+") {
		outputStream << "Operator" << std::setw(20) << "+" << std::endl;
		++vptr;
		outputStream << "E' -> +TE'" << std::endl;
		T();
		Ep();
	}
	if (tokens[vptr].name == "-") {
		outputStream << "Operator" << std::setw(20) << "-" << std::endl;
		++vptr;
		outputStream << "E' -> -TE'" << std::endl;
		T();
		Ep();
	}
	else if (!Follows("Ep")) {
		outputStream << "Error: Token is not in Follows of (E')" << std::endl;
		return;
	}

}

void Lex::T() {
	if (First("T")) {
		outputStream << "T -> FT'" << std::endl;
		F();
		Tp();
	}
	else {
		outputStream << "Error: Token not in First of (T)" << std::endl;
		return;
	}

}


void Lex::Tp() {
	if (tokens[vptr].name == "*") {
		outputStream << "Operator" << std::setw(20) << "*" << std::endl;
		++vptr;
		outputStream << "T' -> *FT'" << std::endl;
		F();
		Tp();
	}
	if (tokens[vptr].name == "/") {
		outputStream << "Operator" << std::setw(20) << "/" << std::endl;
		++vptr;
		outputStream << "T' -> /FT'" << std::endl;
		F();
		Tp();
	}
	else if (!Follows("Tp")) {
		outputStream << "Error: Token is not in Follows of (T')" << std::endl;
		return;
	}

}


void Lex::F() {
	if (First("F")) {
		if (tokens[vptr].name == "(") {
			outputStream << "Separator" << std::setw(20) << "(" << std::endl;
			++vptr;
			outputStream << "F -> (E)" << std::endl;
			E();
			if (tokens[vptr].name == ")") {
				outputStream << "Separator" << std::setw(20) << ")" << std::endl;
				++vptr;
				outputStream << "F -> (E)" << std::endl;
			}
		}
		if (tokens[vptr].type == "Identifier") {
			outputStream << "Identifier" << std::setw(20) << tokens[vptr].name << std::endl;
			++vptr;
			outputStream << "F -> id" << std::endl;
		}
	}
	else {
		outputStream << "Error: Token is not in First of (F)" << std::endl;
		return;
	}


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
		sendtoGrammar("Operator");
		break;
	case(5):
		outputStream << "Separator " << std::setw(20) << arr << std::endl;
		sendtoGrammar("Separator");
		break;
	case(8):
		arr[index] = '\0';
		outputStream << "Identifier" << std::setw(20) << arr << std::endl;
		sendtoGrammar("Identifier");
		break;
	case(9):
		arr[index] = '\0';
		if (searchKeyword(arr)) {
			outputStream << "Keyword   " << std::setw(20) << arr << std::endl;
			sendtoGrammar("Keyword");
		}
		else {
			outputStream << "Identifier" << std::setw(20) << arr << std::endl;
			sendtoGrammar("Identifier");
		}
		break;
	case(10):
		arr[index] = '\0';
		outputStream << "Integer   " << std::setw(20) << arr << std::endl;
		sendtoGrammar("Integer");
		break;
	case (13):
		arr[index] = '\0';
		outputStream << "Float   " << std::setw(20) << arr << std::endl;
		sendtoGrammar("Float");
		break;
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
		do {
			x = getChar();
			col = char_to_col(x);

		} while (col == -1);

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

bool Lex::CheckSingleT(std::string input) {
	if (tokens[vptr].name == input) {
		vptr++;
		return true;
	}
	else {
		outputStream << "Error: Expected: " << input << std::endl;
		return false;
	}




}

bool Lex::STATE() {
	if (EXP() || WL()) {
		return true;
	}
	else
		return false;
		

}

bool Lex::COND() {
	if (EXP()) {
		if (tokens[vptr].name == ">" || tokens[vptr].name == "<") {
			vptr++;
			if (!EXP()) {
				outputStream << "Expression Statement Failed" << std::endl;
				exit(-1);
			}

		}
		else {
			outputStream << "Error: Relational Operator Expected" << std::endl;
			exit(-1);
		}

	}
	else {
		outputStream << "Conditional Statement Failed" << std::endl;
		return (-1);
	}

}
bool Lex::KEY() {
	if (tokens[vptr].name == "int" || tokens[vptr].name == "bool") {
		++vptr;
		if (tokens[vptr].type == "Identifier") {
			++vptr;
			outputStream << "Keyword->Identifier" << std::endl;
			return true;
		}
		else {
			outputStream << "Error: Identifer Expected" << std::endl;
			exit(-1);
		}

	}
	else {
		outputStream << "Error: expected keyword" << std::endl;
		return false;
	}
}


bool Lex::EXP() {
	if (tokens[vptr].type == "Identifier") {
		++vptr;
		return true;
	}
	if (COND())
		return true;
	else
		return false;


}


bool Lex::WL() {
	if (CheckSingleT("while")) {
		if (CheckSingleT("(")) {
			if (COND()) {
				if (CheckSingleT(")")) {
					if (CheckSingleT("{")) {
						if (STATE()) {
							CheckSingleT("}");
							return true;
						}
						else {
							std::cout << "STATEMENT FAILED" << std::endl;
							exit(-1);
						}
					}
				}
			}
			else {
				std::cout << "Condition Failed" << std::endl;
				exit(-1);
			}

		}
	}
	else
		return false;
}




int main()
{
	Lex open("inputfile.txt", "outputfile.txt");

	open.DFSM();
	open.flushArray();
	open.sendtoGrammar("$");
	do {
		if (open.tokens[open.vptr].name == "while") {
			open.WL();
		}
		if (open.tokens[open.vptr].name == "if") {
			open.if_else();
		}
		if (open.tokens[open.vptr].type == "Identifier")
			open.S();
		if (open.tokens[open.vptr].name == "int" || open.tokens[open.vptr].name == "bool")
			open.KEY();
		else {
			if (!(open.tokens[open.vptr].type == "$"))
				open.vptr++;
		}


	} while (!(open.tokens[open.vptr].type == "$"));
	open.outputStream << "Grammar Complete" << std::endl;



	return 0;
}


void Lex::if_else() {

	std::cout << "if else: \n";
	std::cout << "<keyword> <seperator> <condition> <seperator> <seperator><statement> <seperator>\n";
		if (tokens[vptr].name == "if")
		{
			vptr++;
			if (tokens[vptr].name == "(")
			{
				vptr++;
				COND();
				if (tokens[vptr].name == ")")
				{
					vptr++;
					if (tokens[vptr].name == "{")
					{
						vptr++;
						S();
						if (tokens[vptr].name == "}")
						{
							outputStream << "End of if else statement";

						}
						else
						{
							outputStream << "Error: Expected right bracket, exiting program.";
							exit(-1);
						}
					}
					else
					{
						outputStream << "Error: Expected left bracket, exiting program.";
						exit(-1);
					}

				}
				else
				{
					outputStream << "Error: Expected right paranthese, exiting program.";
					exit(-1);
				}
			}
			else
			{
				outputStream << "Error: Expected left prathese, exiting a program.";
				exit(-1);
			}
		}
		else
		{
			outputStream << "keyword if expected, exiting program.";
			exit(-1);
		}

}
