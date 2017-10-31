//game.h: Declares the GameBase class
//Name: Oscar Arias
//Email: oarias@wustl.edu

#pragma once
#ifndef GameBase_h
#define GameBase_h

#include "program.h"
#include "piece.h"

enum actions { input_coordinate, quit_game, no_valid_moves, invalid_input, end_turn };
enum coordinate {x_coord, comma, y_coord};

class GameBase {
protected:
	int width;
	int height;
	unsigned int longest;
	int turns; //Add new member var for turns in a game
	vector<vector<game_piece>> board;
	static shared_ptr<GameBase> game;
	static string name; // New member variable that holds the name of the game created

public:
	GameBase(int width, int height, unsigned int longest, int turns);
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual int turn() = 0;
	int play();
	virtual int prompt(unsigned int & x, unsigned int & y);
	static void game_ptr(int argsnum, char * args[]);
	static shared_ptr<GameBase> instance();
};
#endif