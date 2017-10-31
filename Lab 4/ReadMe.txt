Name: Oscar Arias
Lab 4
Email: oarias@wustl.edu

Error: Vector Subscript out of range

- Saving for each game works in the following way: When a game is saved, the name of the game is written in the first line of the text file with its respective name. 
  The second line is the number of turns that have been played in the game before the game was saved. All subsequent lines are all the board coordinates on its own line with the display of the piece on that coordinate listed
  next to it. When a game is to be loaded, the first line is checked to make sure it is the right game, then the turns are read and finally the coordinates and the piece on each one.

- 'end' key word allows for a turn to end and the next turn to begin

- Made the number of turns played in a game a member variable for game base class

- Classes: NineAlmonds, MagicSquare, Reversi, GameBase
  Copy Control Features: copy constructor, move constructor, copy-assignment operator, move-assignment operator, destructor
  Did not implement most of these copy control features.
  - Destructor: generated automatically by the compiler to destroy the game pointer, no more than one game will ever be played at a time when running the program so not included
  - Copy constructor: not needed in any of the games since no new game was based off of an old one that was created. Used simple copy assignment instead for the game pointer
  - Move Constructor: No need to move any existing games to another game variable. Game pointers are copy assigned instead
  - Copy-Assignment Operator: When creating new pointers for games, I used the copy assignment operator to move the value of the new pointer to the existing game member variable pointer, this allowed for quick game variable initialization
  - Move-Assignment Operator: No need to move any existing games to another game variable. Game pointers are copy assigned instead.


- Test Cases:
	
	Tested cases from previous lab, all NineAlmonds and MagicSquare worked accordingly.
	
	Invalid Move: Placed piece at 7,7. Also tried placing a black piece next to two other black pieces and no white pieces.
	Output: Board Space not valid

	Usage Cases: Only entered lab4.exe
	Output: Usage: lab4.exe - Game not created
                       Enter 'NineAlmonds', 'MagicSquare', or 'Reversi' after the program name
                       If entering 'Reversi', enter two player names after 'Reversi'

	Usage Cases: Entered 'Reversi' but did not enter correct number of player names
        Output: Enter two player names after 'Reversi'

	Skip Player Move: Filled board up with all black pieces, except one and allowed white player to play a piece
	Output: "No valid moves available for this player!"

	Done(): Placed black piece at 5,3 then ended turn and placed black piece at 2,4
	Output: "Oscar Wins! Game! Game completed in 3 turns" 

	Save: Entered quit, then enter 'y' for save and all board coordinates, pieces, turns, and game name were saved in its respective text file
	
	Stalemate: Filled save file with these pieces on each coordinates, then placed black at 1,3.      Output: 'Stalemate!'
				Reversi
				0
				0,0 O
				0,1 O
				0,2 O
				0,3 O
				0,4 O
				0,5 O
				0,6 O
				0,7 O
				1,0 O
				1,1 O
				1,2 O
				1,3  
				1,4 X
				1,5 X
				1,6 X
				1,7 X
				2,0 O
				2,1 O
				2,2 X
				2,3 O
				2,4 O
				2,5 O
				2,6 X
				2,7 X
				3,0 O
				3,1 X
				3,2 O
				3,3 X
				3,4 X
				3,5 X
				3,6 X
				3,7 X
				4,0 X
				4,1 X
				4,2 X
				4,3 O
				4,4 X
				4,5 O
				4,6 O
				4,7 X
				5,0 X
				5,1 X
				5,2 O
				5,3 X
				5,4 O
				5,5 X
				5,6 O
				5,7 X
				6,0 X
				6,1 X
				6,2 X
				6,3 O
				6,4 O
				6,5 O
				6,6 X
				6,7 X
				7,0 O
				7,1 O
				7,2 O
				7,3 O
				7,4 O
				7,5 O
				7,6 O
				7,7 X