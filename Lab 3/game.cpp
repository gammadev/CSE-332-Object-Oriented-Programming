// game.cpp: Source file for gamebase class. Initializes an empty board, contains the play function, game ptr and board coordinate prompt class
// Name: Oscar Arias
// Email: oarias@wustl.edu

#include "stdafx.h"
#include "game.h"
#include "ninealmonds.h"
#include "magicsquare.h"

GameBase::GameBase(int width, int height, unsigned int longest) : width(width), height(height), longest(longest)  // Creates an empty 2-D vector board with blank pieces on each space
{
	for (int i = 0; i < width; i++) {
		vector<game_piece> col;
		board.push_back(col);
		for (int j = 0; j < height; j++) {
			game_piece blank = * new game_piece(no_color, "", " ");
			if (blank.display.size() > longest) {
				longest = blank.display.size();
			}
			board[i].push_back(blank);
		}
	}

};
int GameBase::play()
{
	print();
	int turns = 0;

	while (true) {
		if (turn() == quit_game) {
			cout << "\n" << turns << " turns have been played" << endl;
			cout << "User has quit the game" << endl;
			return quit_game;
		}
		else if (done()) {
			++turns;
			cout << "Game!" << endl;
			cout << "\n" << "Game completed in " << turns << " turns" << endl;
			return success;
		}
		else if (stalemate()) {
			++turns;
			cout << "Stalemate" << endl;
			cout << "\n" << turns << " turns have been played" << endl;
			cout << "No valid moves remain in the game" << endl;
			return no_valid_moves;
		}
		else {
			++turns;
		}
	}
}

int GameBase::prompt(unsigned int & x, unsigned int & y)
{
	while (true)
	{
		cout << "Enter a board coordinate, 'end' to end turn, or 'quit' to quit the game" << endl;
		string input;
		cin >> input;

		if (input == "quit") {
			return quit_game;
		}
		else if (input == "end") {
			return end_turn;
		}
		else if (input.length() == 3) {
			int left_coordinate = input[0] - '0';
			char comma = input[1];
			int right_coordinate = input[2] - '0';

			if (left_coordinate < width && comma == ',' && right_coordinate < width) {
				x = left_coordinate;
				y = right_coordinate;

				return input_coordinate;
			}

			continue;
		}
		else {
			cout << "\n" << "Invalid input: Please enter 'quit' or re-enter the required coordinate (Ex. 2,3)" << endl;
			continue;
		}
	}
}

GameBase * GameBase::game_ptr(int argsnum, char * args[])
{
	if (argsnum == 2 && args[input_file] == string("NineAlmonds")) {
		try {
			return new NineAlmonds();
		}
		catch (bad_alloc & ba) {
			cout << "Exception Error: " << ba.what() << endl;
			throw bad_allocation;
		}
	}

	if (argsnum == 2 && args[input_file] == string("MagicSquare")) {
		try {
			return new MagicSquareGame();
		}
		catch (bad_alloc & ba) {
			cout << "Exception Error: " << ba.what() << endl;
			throw bad_allocation;
		}
	}
	return 0;
}

