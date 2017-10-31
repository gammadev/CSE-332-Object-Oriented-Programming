// lab1.cpp : Runs main program method. Checks command line args and responds accordingly. Reads the dimensions and pieces of an input file for a board.
// Name: Oscar Arias
// Email: oarias@wustl.edu

#include "stdafx.h"
#include "board.h"

int main(int argc, char * argv[])
{
	if (argc != 2) {
		return usage(argv[0], "<input_file>");
	}
	else {
		ifstream ifs(argv[1]);
		if (!ifs.is_open()) {
			return usage(argv[0], "Input file cannot be opened");
		}
		else {
			unsigned int horizontal;
			unsigned int vertical;
			
			int dimension_action = dimensions(ifs, horizontal, vertical);
			while (dimension_action == extract_dimensions_error && !ifs.eof()) {
				dimension_action = dimensions(ifs, horizontal, vertical);
			}

			if (dimension_action == extract_dimensions_error) {
				cout << "Board dimensions could not be extracted" << endl;
				return dimensions_never_extracted;
			}
			else {
				vector<game_piece> new_pieces;
				for (unsigned int i = 0; i < horizontal*vertical; i++) {
					game_piece p;
					p.color = no_color;
					p.display = "-";
					p.name = "";
					new_pieces.push_back(p);
				}
				ifs.seekg(ifs.beg);
				int piece_parse = pieces(ifs, new_pieces, horizontal, vertical);
				if (piece_parse == piece_parse_failure) {
					cout << "Program could not parse the game pieces" << endl;
					return piece_parse;
				}
				else {
					return print_board(new_pieces, horizontal, vertical);
				}
			}
		}
	}
}

