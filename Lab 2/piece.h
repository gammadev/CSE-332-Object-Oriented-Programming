//piece.h: Declares the characteristics of a game piece
//Name: Oscar Arias
//ID: 438241
//Email: oarias@wustl.edu

#pragma once

#ifndef piece_h
#define piece_h

#include "program.h"

enum piece_color { red, black, white, brown, no_color, invalid_color };

struct game_piece {

	piece_color color;
	string name;
	string display;
	
	game_piece();
	game_piece(piece_color color, string name, string display);
};

string color_string(piece_color input_color);
piece_color color_enum(string input_color);

#endif