// ConsoleApplication3.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


class Lex {
private:
	int table[12][27] = {


	{2,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,6,1,5,1,1,1},
	{2,7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,7,9,9,9},
	{10,3,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,10,10,10,10,10,10,10,10},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,12,6,6,6,6,12},
	{7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,8,8,8},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{10,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

	};

	std::ofstream outputStream;
	std::ifstream inputStream;
	char c;
	char arr[30];
	std::string test = "while";



public:
	Lex(std::string, std::string);
	void writeArray();
	void readinput();
	char getChar();
	~Lex();
	bool keywordWhile();
	void appendArray();
	void flushArray();
	void DFSM();
	int char_to_col(char x);
	int final_state(int state);
	void parse(int state, int index);
	bool searchKeyword(char keyword[]);

};

void Lex::flushArray() {
	for (int i = 0; arr[i] != '\0'; i++) {
		if (arr[i] != '\0')
			arr[i] = '\0';

	}
	return;

}

bool Lex::searchKeyword(char keyword[]) {
    //Declare string array that contains all keywords.
    std::string key[15] = { "int", "float", "bool", "if", "else", "then", "do",
        "while", "whileend", "do", "doend", "for", "and", "or", "function" };

    std::string word;
    //Check if keyword from keyword() is in the array.
    for (int i = 0; i <= 30; i++) {
        if (keyword[i] != '\0')
            word = word + keyword[i];
    }
    for (int j = 0; j <= 14; j++) {
        if (word == key[j])
            return true;
    }
    return false;

}


void Lex::appendArray() {
	int i;
	bool firstRun = true;

	while (true) {
		if (!firstRun)
			c = getChar();
		if ((c == ' ') || (c == '\n'))
			return;
		for (i = 0; arr[i] != '\0'; i++) {
			//Stuff
		}
		if (arr[i] == '\0') {
			arr[i] = c;
		}
		else
			std::cout << "There was an error with indexing" << std::endl;
		if (firstRun == true)
			firstRun = false;


	}
	return;

}


bool Lex::keywordWhile() {
	int i = 1; //Initial State, w has been printed.

	while (i != 6) {
		c = getChar();
		switch (i)
		{
		case 1: //Sets state to 2
			if (c == 'h') {
				outputStream << c;
				i = 2;
				break;
			}
			else {
				//GO TO IDENTIFIER FUNCTION
			}

		case 2: //Sets state to 3
			if (c == 'i') {
				outputStream << c;
				i = 3;
				break;
			}
			else {
				//GO TO IDENTIFIER FUNCTION
			}

		case 3: //Sets state to 4
			if (c == 'l') {
				outputStream << c;
				i = 4;
				break;
			}
			else {
				//GO TO IDENTIFIER FUNCTION
			}


		case 4: //Sets state to 5
			if (c == 'e') {
				outputStream << c;
				i = 5;
				break;
			}
			else {
				//GO TO IDENTIFIER FUNCTION
			}

		case 5: //Sets state to 6, exit state.
			if (c == ' ' || c == '\n') {
				outputStream << '\t' << "Keyword" << std::endl;
				i = 6;
				break;
			}
			else {
				//GO TO IDENTIFIER FUNCTION
			}
		}
	}
	return true;
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
	outputStream << "Lexeme" << std::setw(20) << "Token" << std::endl;

}

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
	int finals[] = { 4,5,8,9,10,12 };
	for (int i = 0; i < 6; i++) {
		if (state == finals[i]) {
			return state;
		}
	}
	return 0;
}


void Lex::parse(int state, int index) {
	switch (state) {
	case(4):
		outputStream << arr << std::setw(20) << "Operator" << std::endl;
		break;
	case(5):
		outputStream << arr << std::setw(20) << "Separator" << std::endl;
		break;
	case(8):
		arr[index] = '\0';
		outputStream << arr << std::setw(20) << "Identifier" << std::endl;
		break;
	case(9):
		arr[index] = '\0';
		if (searchKeyword(arr))
			outputStream << arr << std::setw(20) << "Keyword" << std::endl;
		else
			outputStream << arr << std::setw(20) << "Identifier" << std::endl;
		break;
	case(10):
		arr[index] = '\0';
		outputStream << arr << std::setw(20) << "Number" << std::endl;
		break;
	case(12):
		break;
	}


}


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
			if (state == 8 || state == 9 || state == 10)
				if ( x != -52)
					inputStream.putback(x);
			parse(state, index);
			state = 1;
			index = 0;
			flushArray();

		}
			

	}



}



void Lex::writeArray() {
	std::cout << arr << std::endl;
	system("pause");
	return;
}

void Lex::readinput() {
	while (!inputStream.eof()) {
		c = getChar();
		switch (c)
		{
		case ('{'):
			outputStream << c << '\t' << "Separator" << std::endl;
			break;
		case ('}'):
			outputStream << c << '\t' << "Separator" << std::endl;
			break;
		case ('('):
			outputStream << c << '\t' << "Separator" << std::endl;
			break;
		case (')'):
			outputStream << c << '\t' << "Separator" << std::endl;
			break;
		case (';'):
			outputStream << c << '\t' << "Punctuation" << std::endl;
			break;
		case ('='):
			outputStream << c << '\t' << "Operator" << std::endl;
			break;
		case ('+'):
			outputStream << c << '\t' << "Operator" << std::endl;
			break;
		case ('-'):
			outputStream << c << '\t' << "Operator" << std::endl;
			break;
		case ('*'):
			outputStream << c << '\t' << "Operator" << std::endl;
			break;
		case ('/'):
			outputStream << c << '\t' << "Operator" << std::endl;
			break;
		case (' '):
			outputStream << "WHITESPACE" << std::endl;
			break;
		case('\n'):
			break;
		default:
			if (c >= 97 && c <= 121) {
				appendArray();
				break;
			}
			else
				break;

		}





		std::cout << c << std::endl;
	}



}


int main()
{
	Lex open("inputfile.txt", "outputfile.txt");



	open.DFSM();
//	open.readinput();
//	open.writeArray();
//	open.flushArray();

	return 0;
}

