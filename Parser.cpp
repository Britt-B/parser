// CS4303 Programming Language Concepts
// Lab exercise - Parser
//
// Name ___Brittany Bergeron____ ID ____redacted____
//
// A simple parser for C/C++-style variable declarations.
// THe grammar is as follows:
//
// <declaration> 	::= 	<type>  <var> ; | <type> <var> = <number> ;
// <type> 			::= 	int | float
// <var> 			::= 	A | B | C | D | E
// <number> 		::= 	<integer> | <float>
// <integer> 		::= 	<integer> <digit> | <digit>
// <digit> 			::= 	0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
// <float> 			::= 	<integer> . <integer>
// 
// Input is entered at the keyboard.
// If the input is correct, the program should print
// "no error found", otherwise, it should print the type
// of error and terminate its execution. There are four
// possible errors:
// 
// "unrecognizable type"
// "illegal variable name"
// "unexpected number"
// "; expected"
//
// Error message is printed out by calling function 
// "error". An error code ranging from 0 to 4 can be
// passed as an argument to the function indicating what
// message is to be printed. The mapping from the error
// code to the message can be found by looking at the
// definition of function "error".

#include <iostream>
#include <string>

using namespace std;

string GetToken();
void error(int);
void command();
int type();
int var();
int number();

//string needs to be global to be accessed by the methods
string global_token;

int main() {
	

	cout << "Please enter a declaration in format " 
		<< "<type> <variable> [= number] ;" << endl;

	global_token = GetToken();

	// Write the code here
	command();
		
	return 0;
}

string GetToken() {

	string token;
	char ch;
	
	//next character input
	cin.get(ch);
	//ignore if leading space
	if(ch == ' '){
		cin.get(ch);
	}
	  
	//must be type or variable if alphabet
	if(isalpha(ch)){
		//valid var names
		if(ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D' || ch == 'E'){
			token = ch;
		}
		//otherwise, must be type or incorrect form
		else{
			while(isalpha(ch)){
				token.push_back(ch);
				cin.get(ch);
			}
		}
	}
	
	//check if var, '=', or ';'
	else if(ch == '=' || ch == ';'){
		//if any of these okay, add to token
		token.push_back(ch);
	}

	//when number comes in
	else if(isdigit(ch)){
		//take rest of declaration
		while(ch != '\n'){
		    token.push_back(ch);
			cin.get(ch);
		}
	}
	
	//if new line, finished
	else if(ch == '\n'){
		token = "";
	}
		
	return token;
}

void error(int code) {
	switch (code) {
		case 0: cout << "no errors found" << endl; break;
		case 1: cout << "unrecognizable type" << endl; break;
		case 2: cout << "illegal variable name" << endl; break;
		case 3: cout << "unexpected number" << endl; break;
		case 4: cout << "; expected" << endl;
	}
	return;
}

void command(){
	//call recursive stack starting with type
	int error_code = type();
	error(error_code);
	return;
}

int type(){	
	//check if type is valid
	if(global_token == "int" || global_token == "float"){
		//get next token
		global_token = GetToken();
		//next token is var, check that and store error code feedback
		int result = var();
		//return result (error code)
		return result;
	}
	//type was incorrect, return error
	else{
		return 1;
	}
}

int var(){
	//if appropriate variable [A|B|C|D|E]
	if(!global_token.compare("A") || !global_token.compare("B") || !global_token.compare("C") || !global_token.compare("D") || !global_token.compare("E")){
		//get next token
		global_token = GetToken();
		//if '=', have to find number
		if(!global_token.compare("=")){
			global_token = GetToken();
			return number();
		}
		//if ';', have to return to main
		else if(!global_token.compare(";")){
			return 0;
		}
		//else is error, declaration expected
		else{
			return 4;
		}
	}
	//illegal var name
	else
		return 2;
}

int number(){
	//make sure number was acutually passed in
	bool num_check = false;
	//hold current character in string
	char temp;
	//traverse through token string
	for(int i=0; i<global_token.length(); i++){
	    //current ppart of token to analyze
	    temp = global_token[i];
	    //if newline, finished input
	    if(temp == '\n'){
	        //get last char to check semicolon
	        temp = global_token[i-1];
	        break;
	    }
		//mark that number has been recorded
		if (isdigit(temp)){
			num_check = true;
		}
		//semicolon after number or dot
		else if (temp == '.' || (temp == ';' && num_check)){
		    //fine, do nothing but don't return error
		}
		//number was recorded, but new character detected
		else if (num_check && temp != ';'){
		   //bad character
			return 4; 
		}
		else if(!num_check){
		    //bad number entry
		    return 3;
		}
		else{
		    return 0;
		}
	}
	//if semicolon after number ret 0
	if(num_check && temp == ';'){
		return 0;
	}
	//if no smeicolon after number, ret 4
	else{
	    return 4;
	}
}