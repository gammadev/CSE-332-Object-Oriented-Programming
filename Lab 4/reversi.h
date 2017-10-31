// reversi.h: Header file that declares the reversi game with its own game functions (print, stalemate, turn, done). Valid_move checks if a move is valid according to reversi game rules, caputre does same but flips colors of captured pieces
// Name: Oscar Arias
// Email: oarias@wustl.edu

#pragma once
#ifndef reversi_h
#define reversi_h

#include "game.h"

class Reversi : public GameBase {
private :
	string black_player;
	string white_player;

public :
	Reversi(string black_name, string white_name);
	friend ostream & operator<<(ostream & os, const Reversi & game);
	virtual void print();
	virtual bool done();
	virtual bool stalemate();
	virtual int turn();
};
bool valid_move(vector<vector<game_piece>> board, unsigned int start_x, unsigned int start_y, string player, string opponent);
void capture(vector<vector<game_piece>> & board, unsigned int start_x, unsigned int start_y, string player, string opponent);

ostream & operator<<(ostream & os, const Reversi & game);
#endif