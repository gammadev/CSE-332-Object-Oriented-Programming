//ninealmonds.h: Specifies the NineAlmond game struct and the various methods used to create it. Valid_move is a helper method that determines if a move is valid
//Name: Oscar Arias
//Email: oarias@wustl.edu

#pragma once
#ifndef ninealmonds_h
#define ninealmonds_h

#include "program.h"
#include "piece.h"

enum actions {input_coordinate, quit_game, invalid_input, end_turn};
enum game_actions {no_valid_moves};

class NineAlmonds {
	private:
		int width;
		int height;
		vector<vector<game_piece>> board;

	public:
		NineAlmonds();
		friend ostream & operator<< (ostream & os, const NineAlmonds & game);
		bool done();
		bool stalemate();
		int prompt(unsigned int & x, unsigned int & y);
		int turn();
		int play();
};

bool valid_move(vector<vector<game_piece>> board, unsigned int x, unsigned int y, unsigned int end_x, unsigned int end_y);
ostream & operator<< (ostream & os, const NineAlmonds & game);

#endif