// game.cpp: Source file for gamebase class. Initializes an empty board, contains the play function, game ptr and board coordinate prompt class
// Name: Oscar Arias
// Email: oarias@wustl.edu

#include "stdafx.h"
#include "game.h"
#include "ninealmonds.h"
#include "magicsquare.h"
#include "reversi.h"

shared_ptr<GameBase> GameBase::game = nullptr;
string GameBase::name = "";

GameBase::GameBase(int width, int height, unsigned int longest, int turns) : width(width), height(height), longest(longest), turns(turns)  // Creates an empty 2-D vector board with blank pieces on each space
{
	for (int i = 0; i < width; i++) {
		vector<game_piece> col;
		board.push_back(col);
		for (int j = 0; j < height; j++) {
			game_piece blank = *new game_piece(no_color, "", " ");
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
	while (true) {
		if (turn() == quit_game) {
			cout << "\n" << turns << " turns have been played" << endl;
			cout << "User has quit the game" << endl;
			
			string save = "";
			while (save != "y" && save != "n") {
				cout << "\n" << "Save game? (y,n)" << endl;
				cin >> save;
			}

			ofstream ofs;
			ofs.open(name + ".txt"); //Should throw error if doesnt exist?

			if (save == "y") {
				if (ofs.is_open()) {
					ofs << name << endl; // Check if all this writing is proceeding correctly, else throw error
					ofs << turns << endl;
					for (int i = 0; i < width; ++i) {
						for (int j = 0; j < height; ++j) {
							ofs << i << "," << j << " " << board[i][j].display << endl;
						}
					}
				}
				else {
					cout << "Save File could not be opened" << endl;
					throw file_not_open;
				}
			}
			else {
				if (ofs.is_open()) {
					ofs << "" << endl;
				}
				else {
					cout << "Save File could not be opened" << endl;
					throw file_not_open;
				}
			}
			ofs.close();
			if (ofs.is_open()) {
				cout << "Save File not closed" << endl;
				throw file_not_closed;
			}

			return quit_game;
		}
		else if (done()) {
			++turns;
			cout << "Game!" << endl;
			cout << "\n" << "Game completed in " << turns << " turns" << endl;

			ofstream ofs;
			ofs.open(name + ".txt"); //Should throw error if doesnt exist?
			if (ofs.is_open()) {
				ofs << "" << endl;
			}
			else {
				cout << "Save File could not be opened" << endl;
				throw file_not_open;
			}

			ofs.close();
			if (ofs.is_open()) {
				cout << "Save File not closed" << endl;
				throw file_not_closed;
			}

			return success;
		}
		else if (stalemate()) {
			++turns;
			cout << "Stalemate" << endl;
			cout << "\n" << turns << " turns have been played" << endl;
			cout << "No valid moves remain in the game" << endl;

			ofstream ofs;
			ofs.open(name + ".txt"); //Should throw error if doesnt exist?
			if (ofs.is_open()) {
				ofs << "" << endl;
			}
			else {
				cout << "Save File could not be opened" << endl;
				throw file_not_closed;
			}

			ofs.close();
			if (ofs.is_open()) {
				cout << "Save File not closed" << endl;
				throw file_not_closed;
			}

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

void GameBase::game_ptr(int argsnum, char * args[])
{
	if (game != nullptr) {
		cout << "Exception: Game currently exists" << endl;
		throw game_currently_exists;
	}
	else {
		if (argsnum == 2 && args[input_file] == string("NineAlmonds")) {
			try {
				shared_ptr<GameBase> new_game_ptr(new NineAlmonds());
				game = new_game_ptr;
				name = "NineAlmonds";
			}
			catch (bad_alloc & ba) {
				cout << "Exception Error: " << ba.what() << endl;
				throw bad_allocation;
			}
			catch (cases c) {
				throw c;
			}
		}
		else if (argsnum == 2 && args[input_file] == string("MagicSquare")) {
			try {
				shared_ptr<GameBase> new_game_ptr(new MagicSquareGame());
				game = new_game_ptr;
				name = "MagicSquare";
			}
			catch (bad_alloc & ba) {
				cout << "Exception Error: " << ba.what() << endl;
				throw bad_allocation;
			}
			catch (cases c) {
				throw c;
			}
		}
		else if ((argsnum == 2 || argsnum == 3 || argsnum == 4) && args[input_file] == string("Reversi")) {
			if (argsnum == 4) {
				try {
					shared_ptr<GameBase> new_game_ptr(new Reversi(args[2], args[3]));
					game = new_game_ptr;
					name = "Reversi";
				}
				catch (bad_alloc & ba) {
					cout << "Exception Error: " << ba.what() << endl;
					throw bad_allocation;
				}
				catch (cases c) {
					throw c;
				}
			}
			else {
				cout << "Enter two player names after 'Reversi', Ex ('Reversi' 'Player1' 'Player2')" << endl;
				throw wrong_cmd_args;
			}
		}
		else {
			if (argsnum != 2) {
				throw wrong_cmd_args;
			}
			else {
				throw game_not_given;
			}
		}
		
	}
}

shared_ptr<GameBase> GameBase::instance()
{
	if (game != nullptr) {
		return game;
	}
	else {
		cout << "Exception: No game currently exists" << endl;
		throw game_does_not_exist;
	}
}

