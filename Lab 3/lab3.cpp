// lab3.cpp : Defines the entry point for the console application, checks if the proper argument is added after the program name and checks for any errors thrown
// Name: Oscar Arias
// Email: oarias@wustl.edu

#include "stdafx.h"
#include "game.h"


int main(int argc, char * argv[])
{
	try {
		shared_ptr<GameBase> p (GameBase::game_ptr(argc, argv));
		
		if (p == 0) {
			return usage(argv[program_name], "- Game not created");
		}
		return p->play();

	}
	catch (cases & ba) {
		return ba;
	}
}

