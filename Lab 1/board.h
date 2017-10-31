//board.h: Declares the dimensions and game pieces parsing functions. Declares the print board function
//Name: Oscar Arias
//Email: oarias@wustl.edu

#pragma once

#ifndef board_h
#define board_h

#include "program.h"
#include "piece.h"

int dimensions(ifstream & ifs, unsigned int & width, unsigned int & height);
int pieces(ifstream & ifs, vector<game_piece> & positions, unsigned int width, unsigned int height);
int print_board(const vector<game_piece> & pieces, unsigned int width, unsigned int height);

#endif