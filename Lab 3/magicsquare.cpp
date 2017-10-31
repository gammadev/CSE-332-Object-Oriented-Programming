// magicsquare.cpp: Source file that creates the magic square game with its own game functions (print, stalemate, turn, prompt for the piece, done)
// Name: Oscar Arias
// Email: oarias@wustl.edu

#include "stdafx.h"
#include "magicsquare.h"

MagicSquareGame::MagicSquareGame() : GameBase(3, 3, 0) //Load pieces into available piece array, check for longest piece display
{
	for (int i = 1; i <= width*height; ++i) {
		pieces.push_back(* new game_piece(no_color, to_string(i), to_string(i)));

		if (to_string(i).size() > longest) {
			longest = to_string(i).size();
		}
	}
}

void MagicSquareGame::print()
{
	cout << "\n" << *this << endl;
}

bool MagicSquareGame::done() // Add rows and columns sums to a set, if the size of the set is 1 then all values are the same and thus game is won
{
	int row = 0;
	int col = 0;
	int diag1 = 0;
	int diag2 = 0;
	set<int> vals;

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; j++) {
			if (value(board[j][i]) == 0 || value(board[i][j]) == 0) { return false; } // Checks if any board space is empty, then return false
			row += value(board[j][i]); //Sum rows
			col += value(board[i][j]); //Sum columns
		}
		vals.insert(row);
		vals.insert(col);

		row = 0;
		col = 0;
	}

	for (int i = 0; i < width; ++i) {
		diag1 += value(board[i][i]); //Sum diagonal, bottom left to top right
		diag2 += value(board[i][width - 1 - i]); // Sum diagonal, top left to bottom right
	}
	vals.insert(diag1);
	vals.insert(diag2);

	return (vals.size() == 1);
}

bool MagicSquareGame::stalemate() // Same as done() except if set size is not 1 and all spaces are full, then return true
{
	int row = 0;
	int col = 0;
	int diag1 = 0;
	int diag2 = 0;
	set<int> vals;

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; j++) {
			if (value(board[j][i]) == 0 || value(board[i][j]) == 0) { return false; }
			row += value(board[j][i]);
			col += value(board[i][j]);
		}
		vals.insert(row);
		vals.insert(col);

		row = 0;
		col = 0;
	}

	for (int i = 0; i < width; ++i) {
		diag1 += value(board[i][i]);
		diag2 += value(board[i][width - 1 - i]);
	}
	vals.insert(diag1);
	vals.insert(diag2);

	return (vals.size() != 1);
}

void MagicSquareGame::prompt(unsigned int & piece_val)
{
	while(true) {
		cout << "Enter a piece value, 'end' to end turn, or 'quit' to quit the game" << endl;
		string input;
		cin >> input;

		if (input == "quit") {
			throw quit_game;
		}
		else if (input == "end") {
			throw end_turn;
		}
		else if (input == "1" || input == "2" || input == "3" || input == "4" || input == "5" || input == "6" || input == "7" || input == "8" || input == "9") {
			for (game_piece p : pieces) {
				if (value(p) == stoi(input)) {
					piece_val = value(p);
					throw input_coordinate;
				}
			}

			cout << "\n" << "Piece not available" << endl;
		}
		else {
			cout << "\n" << "Invalid piece value: Please enter any number 1-9" << endl;
		}
	}
}

int MagicSquareGame::turn()
{
	unsigned int x, y, piece;

	while (true) {
		switch (GameBase::prompt(x, y)) {
			case quit_game : return quit_game;
			case end_turn: return end_turn;
			default: break;
		}

		if (board[x][y].display != " ") {
			cout << "\n" << "Board space not empty" << endl;
			continue;
		}

		try { prompt(piece); }
		catch (actions & a) {
			switch (a) {
				case quit_game : return quit_game;
				case end_turn: return end_turn;
				default: break;
			}
		}

		if (value(pieces[piece - 1]) != piece) {
			cout << "Piece not available" << endl;
		}
		else {
			board[x][y] = pieces[piece - 1];
			pieces[piece - 1].name = "0";
			pieces[piece - 1].display = "";
			
			print();

			return success;
		}
	}
}

ostream & operator<<(ostream & os, const MagicSquareGame & game)
{
	for (int j = game.height - 1; j >= 0; --j) {
		os << j;
		for (int i = 0; i < game.width; ++i) {
			os << " " << setw(game.longest) << game.board[i][j].display;
		}
		os << endl;
	}
	os << "X"
		<< " " << setw(game.longest) << "0"
		<< " " << setw(game.longest) << "1"
		<< " " << setw(game.longest) << "2" << endl;

	os << "Available Pieces:";
	for (game_piece p : game.pieces) {
		os << " " << setw(game.longest) << p.display;
	}
	os << endl;

	return os;
}
