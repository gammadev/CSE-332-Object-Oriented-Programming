//ninealmonds.cpp: Serves as the file that creates the ninealmonds game. Runs through all cases for the game and decides how moves will be made
//End case ends a turn if the user has accidentally continued the turn and wants to escape it without messing up their game
//Name: Oscar Arias
//Email: oarias@wustl.edu

#include "stdafx.h"
#include "ninealmonds.h"

NineAlmonds::NineAlmonds() : GameBase(5, 5, 0)
{
	for (int i = 1; i < width - 1; i++) {
		for (int j = 1; j < height - 1; j++) {
			board[i][j].color = brown;
			board[i][j].display = "A";

			if (board[i][j].display.size() > longest) {
				longest = board[i][j].display.size();
			}
		}
	}
}

void NineAlmonds::print()
{
	cout << *this << endl;
}

bool NineAlmonds::done()
{
	game_piece center = board[2][2];

	if (center.display == "A") {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (board[i][j].display == "A" && i != 2 && j != 2) {
					return false;
				}
			}
		}
		return true;
	}
	else {
		return false;
	}
}

bool NineAlmonds::stalemate()
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (board[i][j].display == "A") {
				for (int k = 0; k < width; k++) {
					for (int l = 0; l < height; l++) {
						if (valid_move(board, i, j, k, l)) {
							return false;
						}
					}
				}
			}
		}
	}
	return !done();
}

int NineAlmonds::turn()
{
	while (true)
	{
		cout << "Enter beginning square coordinate" << endl;
		unsigned int start_x;
		unsigned int start_y;
		unsigned int end_x;
		unsigned int end_y;

		string moves = "Moves this turn: ";
		bool first_move = true;

		switch (prompt(start_x, start_y)) {
		case quit_game: return quit_game;
		case end_turn: return end_turn;
		case input_coordinate: break;
		default: break;
		}

		if (board[start_x][start_y].display == " ") { 
			cout << "\n" << "Board space is empty" << endl;
			continue;
		}

		while (true) {
			cout << "Enter ending square coordinate" << endl;

			switch (prompt(end_x, end_y)) {
			case quit_game: return quit_game;
			case end_turn: return end_turn;
			case input_coordinate: break;
			default: break;
			}

			if (board[end_x][end_y].display == "A") {
				cout << "\n" << "Board space not empty" << endl;
			}
			else if (valid_move(board, start_x, start_y, end_x, end_y)) {

				board[end_x][end_y].display = "A";
				board[start_x][start_y].display = " ";

				int midpointx = (start_x + end_x) / 2;
				int midpointy = (start_y + end_y) / 2;

				board[midpointx][midpointy].display = " ";

				cout << "\n" << *this << "\n";

				if (first_move) {
					moves += to_string(start_x) + "," + to_string(start_y);
					first_move = false;
				}

				moves += " to ";
				moves += to_string(end_x) + "," + to_string(end_y);

				cout << moves << "\n" << endl;

				cout << "Contiune this turn? (y, n)" << endl;

				string input = "";
				while (input != "y" && input != "n") {
					cin >> input;
				}

				if (input == "n") {
					return success;
				}
				else {
					start_x = end_x;
					start_y = end_y;
				}
			}
			else {
				cout << "Invalid move, re-enter start and end coordinates" << endl;
				break;
			}
		}
	}
}

bool valid_move(vector<vector<game_piece>> board, unsigned int start_x, unsigned int start_y, unsigned int end_x, unsigned int end_y)
{
	if (board[start_x][start_y].display == "A") {
		//Distance formula for 2 spaces
		int distancex = (end_x - start_x) * (end_x - start_x);
		int distancey = (end_y - start_y) * (end_y - start_y);
		int distance = (int)sqrt(distancex + distancey);

		if (distance == 2 && board[end_x][end_y].display == " ") {
			//Midpoint formula for 1 space
			int midpointx = (start_x + end_x) / 2;
			int midpointy = (start_y + end_y) / 2;

			if (board[midpointx][midpointy].display == "A") {
				return true;
			}
		}
	}
	return false;
}

ostream & operator<<(ostream & os, const NineAlmonds & game)
{
	for (int j = game.height - 1; j >= 0; --j) {
		os << j;
		for (int i = 0; i < game.width; ++i) {
			os << " "<< setw(game.longest) << game.board[i][j].display;
		}
		os << endl;
	}
	os << "X"
	   << " "<< setw(game.longest) << "0"
	   << " "<< setw(game.longest) << "1"
	   << " "<< setw(game.longest) << "2"
	   << " "<< setw(game.longest) << "3"
	   << " "<< setw(game.longest) << "4" << endl;
	   
	return os;
}
