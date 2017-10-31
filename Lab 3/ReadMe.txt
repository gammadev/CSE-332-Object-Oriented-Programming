Lab 3
Name: Oscar Arias
Email: oarias@wustl.edu

Errors: vector subscript out of range

Cases:

Win:
	input: applied the following moves
		Done:

		0,0: 6
		0,1: 7
		0,2: 2
		1,0: 1
		1,1: 5
		1,2: 9
		2,0: 8
		2,1: 3
		2,2: 4

	output: Game! 
			Game completed in 9 turns

Stalemate:
	input: applied the following moves
		Stalemate:

		0,0: 1
		0,1: 2
		0,2: 3
		1,0: 4
		1,1: 5
		1,2: 6
		2,0: 7
		2,1: 8
		2,2: 9

	output: Stalemate
			9 moves have been played
			No valid moves remain in the game

quit: after 4 moves - Output: 4 moves have been played
								User has quit the game

Input: lab3.exe
Output: Usage: lab3.exe - Game not created
			   Enter 'NineAlmonds' or 'MagicSquare' after the program name

Input: entering a board coordinate that already has a piece
Output: 'Board coordinate not empty' then reprompts for coordinate

Input: Entering a piece that has already been used
Output: 'Piece not available', then reprompts for piece

Input: '0' (or any non-valid value or string)
Output: Invalid piece value: Please Enter any number 1-9			   
 
'end' ends the turn and adds 1 to the turn count
Applied the same tests from the previous lab for nine almonds, works fine.

Almond moves to win and stalemate: 
Stalemate: 
	1,2 to 1,4
	2,2 to 4,0 
	3,3 to 3,1
	4,0 to 2,2
	1,1 to 3,3 to 1,3
	1,4 to 1,2
	2,1 to 0,3

Done:
	2,2 to 2,0 to 4,2 to 2,4 to 0,2
	1,1 to 1,3 
	3,2 to 1,4 to 1,2
	0,2 to 2,2
