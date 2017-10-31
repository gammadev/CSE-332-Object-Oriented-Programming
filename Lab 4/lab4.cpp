// lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game.h"

int main(int argc, char * argv[])
{
	try {
		GameBase::game_ptr(argc, argv);
		shared_ptr<GameBase> p(GameBase::instance());

		return p->play();
	}
	catch (cases c) {
		if (c == wrong_cmd_args) {
			return usage(argv[program_name], "Please enter second command argument (with player names if a multiplayer game)");
		}
		else if (c == game_not_given) {
			return usage(argv[program_name], "- Game not created");
		}
		else {
			return c;
		}
	}
}

