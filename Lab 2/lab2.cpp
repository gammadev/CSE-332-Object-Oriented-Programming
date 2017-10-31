// lab2.cpp : Contains the main method which checks for the valid arguments and creates and starts a game if so
// if not, the main calls the usage method which explains how to run the program
// 
// Name: Oscar Arias
// ID: 438241
// Email: oarias@wustl.edu

#include "stdafx.h"
#include "ninealmonds.h"


int main(int argc, char * argv[])
{
	if (argc == expected_arg_length && argv[input_file] == string("NineAlmonds")) {
		NineAlmonds game;
		return game.play();
	}
	else {
		return usage(argv[program_name], "NineAlmonds");
	}
}

