//game.h: Declares the GameBase class
//Name: Oscar Arias
//Email: oarias@wustl.edu

#pragma once
#ifndef GameBase_h
#define GameBase_h

#include "program.h"
#include "piece.h"

enum actions { input_coordinate, quit_game, no_valid_moves, invalid_input, end_turn };

class GameBase {
	protected:
		int width;
		int height;
		unsigned int longest;
		vector<vector<game_piece>> board;

	public:
		GameBase(int width, int height, unsigned int longest);
		virtual void print() = 0;
		virtual bool done() = 0;
		virtual bool stalemate() = 0;
		virtual int turn() = 0;
		int play();
		virtual int prompt(unsigned int & x, unsigned int & y);
		static GameBase * game_ptr(int argsnum, char * args[]);
};
#endif