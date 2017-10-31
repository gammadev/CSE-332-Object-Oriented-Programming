//program.cpp: Handles essential program functions like converting to lowercase and sending usage messages
//Name: Oscar Arias
//Email: oarias@wustl.edu

#include "stdafx.h"
#include "program.h"

int usage(const string & program, const string & message)
{
	cout << "Usage: " << program << " " << message << endl;
	if (message == "<input_file>") {
		return wrong_cmd_args;
	}
	else if (message == "Input file cannot be opened") {
		return file_not_open;
	}
	else {
		return success;
	}
}

string lowercase(string & input_string)
{
	for (unsigned int i = 0; i < input_string.size(); i++) {
		if (input_string[i] >= 'A' && input_string[i] <= 'Z') {
			input_string[i] += 32;
		}
	}
	return input_string;
}
