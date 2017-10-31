//ninealmonds.cpp: Serves as the file that creates the ninealmonds game. Runs through all cases for the game and decides how moves will be made
//End case ends a turn if the user has accidentally continued the turn and wants to escape it without messing up their game
//Name: Oscar Arias
//Email: oarias@wustl.edu

#include "stdafx.h"
#include "ninealmonds.h"

NineAlmonds::NineAlmonds()
{
	width = 5;
	height = 5;

	for (int i = 0; i < width; i++) {
		vector<game_piece> col;
		board.push_back(col);
		for (int j = 0; j < height; j++) {
			game_piece almond(no_color, "", " ");
			board[i].push_back(almond);
		}
	}
	
	for (int i = 1; i < width - 1; i++) {
		for (int j = 1; j < height - 1; j++) {
			board[i][j].color = brown;
			board[i][j].display = "A";
		}
	}
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

int NineAlmonds::prompt(unsigned int & x, unsigned int & y)
{
	cout << "\n" << "Enter a board coordinate, 'end' to end the turn, or 'quit' to quit the game" << endl;
	string input;
	cin >> input;
	
	if (input.size() < 3) {
		cout << "\n" << "Invalid input: Please enter 'quit' or enter the required coordinate (Ex. 2,3)" << endl;
		prompt(x, y);
	}

	int left_coordinate = input[0] - '0';
	char comma = input[1];
	int right_coordinate = input[2] - '0';

	if (input == "quit") {
		throw quit_game;
	}
	else if (input.length() == 3 && (left_coordinate < width) && comma == ',' && (right_coordinate < width)) {
		x = left_coordinate;
		y = right_coordinate;
		
		throw input_coordinate;
	}
	else if (input == "end") {
		throw end_turn;
	}
	else {
		cout << "\n" << "Invalid input: Please enter 'quit' or re-enter the required coordinate (Ex. 2,3)" << endl;
		prompt(x, y);
	}

	return success;
}

int NineAlmonds::turn()
{
	cout << "\n" << "Enter beginning square coordinate" << endl;
	unsigned int start_x;
	unsigned int start_y;
	unsigned int end_x;
	unsigned int end_y;
	
	string input = "";
	string moves = "Moves this turn: ";
	bool first_move = true;
		
	try { prompt(start_x, start_y); }
	catch (actions coordinate) {};

	while (input != "n") {
		input = "";
		cout << "\n" << "Enter ending square coordinate" << endl;

		try { prompt(end_x, end_y); }
		catch (actions coordinate){}
				
		if (valid_move(board, start_x, start_y, end_x, end_y)) {
				
			board[end_x][end_y].display = "A";
			board[start_x][start_y].display = " ";

			int midpointx = (start_x + end_x) / 2;
			int midpointy = (start_y + end_y) / 2;
				
			board[midpointx][midpointy].display = " ";
				
			cout << "\n" << *this << "\n";
				
			if (first_move) {moves += to_string(start_x) + "," + to_string(start_y);}
			moves += " to ";
			moves += to_string(end_x) + "," + to_string(end_y);
			first_move = false;

			cout << moves << "\n" << endl;

			if (stalemate() || done()) {throw end_turn;}
			cout << "\n" << "Contiune this turn? (y, n)" << endl;
			while (input != "y" && input != "n") {
				cin >> input;
			}

			if (input == "n") { throw end_turn; }

			start_x = end_x;
			start_y = end_y;
		}
		else {
			cout << "\n" << "Invalid move, re-enter start and end coordinates" << "\n" << endl;
			turn();
		}
	}
	return success;
}

int NineAlmonds::play()
{
	cout << "\n" << *this << endl;
	int turns = 0;

	while (true) {
		try {
			turn();
		}
		catch (actions stop) {
			if (stop == quit_game) {
				cout << "\n" << turns << " turns have been played" << endl;
				cout << "User has quit the game" << endl;
				return stop;
			}
		}
		if (done()) {
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

bool valid_move(vector<vector<game_piece>> board, unsigned int start_x, unsigned int start_y, unsigned int end_x, unsigned int end_y)
{
	if (board[start_x][start_y].display == "A") {
		//Distance formula for 2 spaces
		int distancex = (end_x - start_x) * (end_x - start_x);
		int distancey = (end_y - start_y) * (end_y - start_y);
		int distance = (int)sqrt(distancex + distancey);
		
		if (distance == 2 && board[end_x][end_y].display == " ") {
			//Midpoint formula for 1 space
			int midpointx = (start_x + end_x)/2;
			int midpointy = (start_y + end_y)/2;
			
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
		os << j << " ";
		for (int i = 0; i < game.width; ++i) {
			os << game.board[i][j].display << " ";
		}
		os << endl;
	}
	os << "X 0 1 2 3 4" <<  "\n" << endl;
	return os;
}
