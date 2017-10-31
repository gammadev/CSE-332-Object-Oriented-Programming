// Declares the magicsquaregame class
// Name: Oscar Arias
// Email: oarias@wustl.edu

#pragma once
#ifndef magicsquare_h
#define magicsquare_h

#include "game.h"

class MagicSquareGame : public GameBase {
private:
	vector<game_piece> pieces;

public:
	MagicSquareGame();
	friend ostream & operator<<(ostream & os, const MagicSquareGame & game);
	virtual void print();
	virtual bool done();
	virtual bool stalemate();
	virtual void prompt(unsigned int & piece_val);
	virtual int turn();
};
ostream & operator<<(ostream & os, const MagicSquareGame & game);
#endif
