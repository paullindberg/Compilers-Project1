// ConsoleApplication3.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <string>


class Lex {
private:
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

};

void Lex::flushArray() {
	for (int i = 0; arr[i] != '\0'; i++) {
		if (arr[i] != '\0')
			arr[i] = '\0';

	}
	return;

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
	outputStream << "Lexeme" << '\t' << "Token" << std::endl;

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

	open.readinput();
	open.writeArray();
	open.flushArray();

	return 0;
}

