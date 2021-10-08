# Parser
***
## Task
Write a program to parse input from command line and determine if input is valid for C/C++ declaration or initialization numerical types (int, float)
***
## Criteria
* Use C++
* follow declaration rules (see functionality below)
* report if any errors found, and what type of error was encountered
***
## Summary
The program accepts input from the user via command line or file input and returns with a message of acceptance or information about what went wrong.
### Errors:
* "no errors found"		-all went as expected
* "unrecognizable type"		-"int" or "float" not specified
* "illegal variable name"	-options are A|B|C|D|E
* "unexpected number"		-user did not properly initialize with int or float number
* "; expected"			-statement not ended properly
***
## Functionality
### Acceptable Grammer:
* <declaration> ::= 	<type>  <var> ; | <type> <var> = <number> ;
* <type> 	::= 	int | float
* <var> 	::= 	A | B | C | D | E
* <number> 	::= 	<integer> | <float>
* <integer> 	::= 	<integer> <digit> | <digit>
* <digit> 	::= 	0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
* <float> 	::= 	<integer> . <integer>
***
## Design
Functions are called in a recursive manner to determine if each portion was written correctly by the user. This allows the program to stop once it reaches an issue.
***
## Run Locally
using gcc compiler:
* navigate to file location
* g++ -o parser parser.cpp
* ./parser

