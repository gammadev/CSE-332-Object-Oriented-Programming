// reversi.cpp: Source file that creates the reversi game with its own game functions (print, stalemate, turn, capture for opponent peices, done)
// Name: Oscar Arias
// Email: oarias@wustl.edu

#include "stdafx.h"
#include "reversi.h"

Reversi::Reversi(string black_name, string white_name) : black_player(black_name), white_player(white_name), GameBase(8, 8, 0, 0)
{
	ifstream ifs;
	ifs.open("Reversi.txt");
	if (!ifs.is_open()) {
		cout << "Save File could not be opened" << endl;
		throw file_not_open;
	}

	string line;
	getline(ifs, line);
	if (line == "Reversi") {
		getline(ifs, line);
		turns = stoi(line);

		while (getline(ifs, line)) {
			istringstream iss(line);
			string word;
			int x, y;

			while (iss >> word) {
				int coordinate = 3;
				if (word.size() == coordinate && word[1] == ',') {
					x = word[0] - '0';
					y = word[2] - '0';
				}
				else {
					board[x][y].display = word;

					if (word == "X") {
						board[x][y].color = color_enum("black");
					}
					else {
						board[x][y].color = color_enum("white");
					}

					if (word.size() > longest) {
						longest = word.size();
					}
				}
			}
		}
		ifs.close();
		if (ifs.is_open()) {
			cout << "Save File not closed" << endl;
			throw file_not_closed;
		}
	}
	else {
		board[3][3].color = piece_color::black;
		board[4][4].color = piece_color::black;
		board[3][3].display = "X";
		board[4][4].display = "X";
		board[3][4].color = piece_color::white;
		board[4][3].color = piece_color::white;
		board[3][4].display = "O";
		board[4][3].display = "O";
	}
}

void Reversi::print()
{
	cout << *this << endl;
}

bool Reversi::done()
{
	int black_count = 0;
	int white_count = 0;
	
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (board[i][j].display == "X") {
				black_count++;
			}
			if (board[i][j].display == "O") {
				white_count++;
			}
		}
	}

	if (black_count != white_count) {
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				if (valid_move(board, i, j, "X", "O") || valid_move(board, i, j, "O", "X")) {
					return false;
				}
			}
		}

		if (black_count > white_count) {
			cout << black_player << " wins!" << endl;
		}
		else {
			cout << white_player << " wins!" << endl;
		}
		return true;
	}
	return false;
}

bool Reversi::stalemate()
{
	int black_count = 0;
	int white_count = 0;

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (board[i][j].display == "X") {
				black_count++;
			}
			if (board[i][j].display == "O") {
				white_count++;
			}
		}
	}

	if (black_count == white_count) {
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				if (valid_move(board, i, j, "X", "O") || valid_move(board, i, j, "O", "X")) {
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

int Reversi::turn()
{
	string player_piece = "";
	string opponent_piece = "";

	if (turns % 2 == 0) { // If the number of turns is even, then it is the black player's turn
		player_piece = "X";
		opponent_piece = "O";
		cout << black_player << "'s turn" << endl;
	}
	else {    // Else the white player goes this turn
		player_piece = "O";
		opponent_piece = "X";
		cout << white_player << "'s turn" << endl;
	}

	bool continue_turn = false;
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (valid_move(board, i, j, player_piece, opponent_piece)) { // Check if the current player has any valid moves
				continue_turn = true;
			}
		}
	}

	if (continue_turn) { // If so, then proceed with turn
		unsigned int x, y;
		
		while (true) {
			switch (GameBase::prompt(x, y)) {
				case quit_game: return quit_game;
				case end_turn: return end_turn;
				default: break;
			}

			if (!valid_move(board, x, y, player_piece, opponent_piece)) { //If player is making an invalid move then prompt again
				cout << "\n" << "Board space not valid" << endl;
				continue;
			}
			else {
				board[x][y].color = color_enum(player_piece); //Place your piece
				board[x][y].display = player_piece;

				capture(board, x, y, player_piece, opponent_piece); //Flip all contiguous pieces to your color
				print();
				return input_coordinate;
			}
		}
	}
	else { // If no valid moves then end turn
		cout << "No valid moves available for this player!" << endl;
		return no_valid_moves;
	}
}

bool valid_move(vector<vector<game_piece>> board, unsigned int start_x, unsigned int start_y, string player, string opponent)
{
	if (board[start_x][start_y].color == no_color) { //If chosen square is empty
		for (int i = -1; i < 2; i++) {  //Check all the squares around the chosen square by add/subtracting 0 or 1
			for (int j = -1; j < 2; j++) {
				if (start_x + i >= 0 && start_y + j >= 0 && start_x + i < board.size() && start_y + j < board[0].size()) { // If new square lies in range of the board, proceed
					if (board[start_x + i][start_y + j].display == opponent) { // If new square contains an opponent's piece, proceed
						unsigned int endx = start_x + i;
						unsigned int endy = start_y + j;

						while (endx > 0 && endy > 0 && endx < board.size() && endy < board[0].size()) { //Check contiguous squares until you reach the end of the board
							if (board[endx][endy].display == opponent) {								//If the current contiguous square contains an opponents piece, check the next one
								endx += i;
								endy += j;
							}
							else if (board[endx][endy].display == player) {								//If the contiguous square contains your piece, then valid move is found
								return true;
							}
							else {																		//If the contiguous square is empty, then stop checking, move not valid
								break;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

void capture(vector<vector<game_piece>> & board, unsigned int start_x, unsigned int start_y, string player, string opponent)
{
	for (int i = -1; i < 2; i++) {  //Check all the squares around the chosen square by add/subtracting 0 or 1
		for (int j = -1; j < 2; j++) {
			if (start_x + i >= 0 && start_y + j >= 0 && start_x + i < board.size() && start_y + j < board[0].size()) { // If new square lies in range of the board, proceed
				if (board[start_x + i][start_y + j].display == opponent) { // If new square contains an opponent's piece, proceed
					unsigned int endx = start_x + i;
					unsigned int endy = start_y + j;

					while (endx > 0 && endy > 0 && endx < board.size() && endy < board[0].size()) { //Check contiguous squares until you reach the end of the board
						if (board[endx][endy].display == opponent) {								//If the current contiguous square contains an opponents piece, check the next one
								
							endx += i;
							endy += j;
						}
						else if (board[endx][endy].display == player) {								//If the contiguous square contains your piece, then valid move is found
							endx -= i;
							endy -= j;

							while (board[endx][endy].display != player) {							//Retrace path from current square to original square with your piece, flip all opponent pieces to your color
								board[endx][endy].color = color_enum(player);
								board[endx][endy].display = player;
								endx -= i;
								endy -= j;
							}
							break;
						}
						else {																		//If the contiguous square is empty, then stop checking, move not valid
							break;
						}
					}
				}
			}
		}
	}
}


ostream & operator<<(ostream & os, const Reversi & game)
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
		<< " " << setw(game.longest) << "2"
		<< " " << setw(game.longest) << "3"
		<< " " << setw(game.longest) << "4" 
		<< " " << setw(game.longest) << "5" 
		<< " " << setw(game.longest) << "6" 
		<< " " << setw(game.longest) << "7" << endl;

	return os;
}
