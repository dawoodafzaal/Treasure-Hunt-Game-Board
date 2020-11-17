# Treasure Hunt Game Board

This project was created by myself for a school project.

This game was coded in C. The structure of the game is as followed:

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BEFORE YOU PLAY

On start, you are prompted to enter a username of your choice then you are presented with the option to see the top three scores with their respective usernames which are stored in a log file.

Afterwards, you choose the dimensions of a nxn board where n is the user input and n cannot exceed 20 and cannot be less than 5, meaning the largest board size is 20x20. Also, the overall time given to a player is based on the board size, the initial timer is set to 60 when n is equal to 5 and as n increases, so does the timer, this provides the player with a proportionate amount of time.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PLAYING THE GAME

Once the player has entered a name and board size, the game begins.

Each tile of the board is seen as an 'X', the player is asked to enter (x,y) coordinates, then the 'X' on the board at the (x,y) coordinates chosen by the player dissapears and the 'treasure' underneathe is revealed. There are four possibilities: the player found a treasure and their score increases, or they found a bomb and their score decreases, or they found a 'nice surprise' which doubles their current score, or they found a 'bad surprise' which halves their current score or lastly, they found a 'time pack' which increases their time by thirty seconds

The values generated by the 'treasures' and 'bombs' are from (-15 to -1) for the bombs and (1-15) for treasures

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

WIN CONDITION

If the player uncovers all spots on the board and retains a score above zero, they win!

Their name, score and time used will be recorded within a log file

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LOSING CONDITIONS

If a players score is less than zero AFTER their first turn, they lose. Another losing condition is if the timer runs out and they still have 'X's' on the board

Regardless of if the player wins, their name, score, and time used will still be saved in a log file

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

OTHER NOTES

Once a spot has been picked on the board, a symbol associated with the type of reward chosen will overide the 'X' icon on the board. A '+' will appear if the player has chosen a treasure, '-' if the player picked a bomb, '!' if the player picked the bad surpirse, '$' if the player picked the good surpirse and '@' if the player picked the time pack.

The same spot cannot be chosen again, any (x,y) coordinate chosen which does not exist on the board will be rejected and the player will be notified if their move is out if bounds.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Functions:

	RandomNum: returns a random number in a range from -15 to 15, must only return non-zero numbers
	
	Initialize: initializes the pieces of the game, places the numbers on random indices
	
	Display: Displays the board. 
	
	Calculate Score: calculates the player's most current score
	
	Log Score: creates a game log which stores the player's name, score and time for each playthrough
	
	Exit Game: exits the game upon function call
	
	Display Top Scores: displays 'n' number of top scores where n is the users input
	
	Check Board: loops through the entire board to see if all indices have been used, returns false otherwise
  
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	








