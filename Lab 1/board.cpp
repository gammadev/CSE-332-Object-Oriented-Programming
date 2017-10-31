//board.cpp: Parses the dimensions and pieces of the board as well as prints it out
//Name: Oscar Arias
//Email: oarias@wustl.edu

#include "stdafx.h"
#include "board.h"

int dimensions(ifstream & ifs, unsigned int & width, unsigned int & height)
{
	string line;
	if (getline(ifs, line)) {
		istringstream iss(line);
		if (iss >> width) {
			if (iss >> height) {
				return success;
			}
			else {
				return extract_dimensions_error;
			}
		}
		else {
			return extract_dimensions_error;
		}
	}
	else {
		return line_not_read;
	}
}

int pieces(ifstream & ifs, vector<game_piece>& positions, unsigned int width, unsigned int height)
{
	string line;
	cases piece_parse = piece_parse_failure;

	while (getline(ifs, line)) {
		istringstream iss(line);
		string color;
		string name;
		string display;
		unsigned int x;
		unsigned int y;

		if (iss >> color && iss >> name && iss >> display && iss >> x && iss >> y) {
			piece_color new_color = color_enum(color);
			if (new_color != invalid_color) {
				if (x < width && y < height) {
					int index = width * y + x;
					positions[index].color = new_color;
					positions[index].name = name;
					positions[index].display = display;

					piece_parse = success;
				}
			}

		}
	}
	return piece_parse;
}

int print_board(const vector<game_piece>& pieces, unsigned int width, unsigned int height)
{
	if (pieces.size() == width*height) {
		for (int i = height - 1; i >= 0; --i) {
			for (unsigned int j = 0; j < width; j++) {
				cout << pieces[width * i + j].display;
			}
			cout << endl;
		}
		return success;
	} 
	else {
		return vector_board_mismatch;
	}
}