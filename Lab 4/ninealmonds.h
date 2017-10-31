//ninealmonds.h: Specifies the NineAlmond game struct and the various methods used to create it. Valid_move is a helper method that determines if a move is valid
//Name: Oscar Arias
//Email: oarias@wustl.edu

#pragma once
#ifndef ninealmonds_h
#define ninealmonds_h

#include "game.h"

class NineAlmonds : public GameBase {
public:
	NineAlmonds();
	friend ostream & operator<< (ostream & os, const NineAlmonds & game);
	virtual void print();
	virtual bool done();
	virtual bool stalemate();
	virtual int turn();
};

bool valid_move(vector<vector<game_piece>> board, unsigned int x, unsigned int y, unsigned int end_x, unsigned int end_y);
ostream & operator<< (ostream & os, const NineAlmonds & game);

#endif