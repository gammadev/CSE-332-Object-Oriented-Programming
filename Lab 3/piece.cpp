//piece.cpp: Allows colors for a piece to be set as either an enumeration or a lowercase C++ string
//Name: Oscar Arias
//ID: 438241
//Emai: oarias@wustl.edu

#include "stdafx.h"
#include "piece.h"

string color_string(piece_color input_color)
{
	switch (input_color)
	{
	case red:
		return "red";
	case black:
		return "black";
	case white:
		return "white";
	case brown:
		return "brown";
	case no_color:
		return "no color";
	default:
		return "invalid color";

	}
}

piece_color color_enum(string input_color)
{
	if (input_color == "red") {
		return red;
	}
	else if (input_color == "black") {
		return black;
	}
	else if (input_color == "white") {
		return white;
	}
	else if (input_color == "brown") {
		return brown;
	}
	else if (input_color == " ") {
		return no_color;
	}
	else {
		return invalid_color;
	}
}

int value(game_piece p) // Converts a piece name to a value (for use with MagicSquare game)
{
	if (p.name == "") {
		return 0;
	}
	else {
		return stoi(p.name);
	}
}
