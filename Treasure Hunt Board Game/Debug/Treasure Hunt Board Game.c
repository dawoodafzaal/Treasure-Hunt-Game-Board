
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


float randomNum(int n, int m, bool neg){

	int integer = rand() & (m - 1); //generates an integer random number
	float decimal = rand() & (n+ 99); //generates an integer decimal value
	float rand = integer + (decimal / 100); //add them both together to get a float number

	if(rand == 0.0){ //if random is zero, add 0.01 to make it non zero
		rand = rand + 1.00;
	}

	if(neg == true){ //checks to see if neg is true then generates a negative
		rand = rand*(-1); //multiplies rand by -1 to get a neagtive rand
	return rand;
	}

	return rand; //else returns a pos random num

}



void initializeGame(float (*board)[100], int input){
	int i, j;
	int counter = 0;

	for(i = 0; i < input; i++){ //for loop to fill each spot with a random number from -15 to 15
		for(j = 0; j < input; j++){
			if(counter < ((input*input)*0.2)){ //using the counter to check 20% of the board is negative values
				board[i][j] = randomNum(-15, 15, true);
				counter++;
			}
			else{
				board[i][j] = randomNum(-15, 15, false); //otherwise it only generates positive nums
			}
		}
	}

}

void displayGame(float (*board)[100], int input, int timer, float score){
	int i, j;

	//loop through each line and print the numbers
	for(i = 0; i < input; i++){
		for(j = 0; j < input; j++){
			//prints numbers
			if(board[i][j] == 23){
				printf("%c",'$');
			}
			else if(board[i][j] == 24){ //checks if the spot taken was a bad surprise
				printf("%c",'!');
			}
			else if(board[i][j] == 25){ //checks if spot was a time bonus
				printf("%c",'@');
			}
			else if(board[i][j] == 20){ //puts plus sign
				printf("%c",'+');
			}
			else if(board[i][j] == -20){ //puts negative sign
				printf("%c",'-');
			}
			else{
				printf("%c",'X'); //puts the 'X' over the numbers
			}
		}
		//prints a new line for the table
		printf("\n");
	}
	//prints score and timer
	printf("Score: %.2f", score);
	printf("\nTimer: %d\n", timer);
}


float calculateScore(float score, float numberchosen){ //calculate score
	return score + numberchosen; //calculates the score
}


void logScore(char *message){
	//creating file
	FILE *logfile;

	//creating a logfile an allows to append
	logfile = fopen("GameLog.log", "a");

	//checking to see if file is valid
	if(logfile == NULL){
		printf("Error!");
		exit(1);
	}
	//used for logging information in the main
	fprintf(logfile, "%s", message);
	fclose(logfile);
	}


void exitGame(){
	exit(0); //exits game
}

void displayTopScores(int n){


	//pointer to file
	 FILE *fp1;

	  fp1 = fopen("GameLog.log", "r"); //opening game log in read mode

	    char line[128];
	    int i = 0;

	    while (fgets(line, sizeof(line), fp1)) {
	    	if (i == n*3) { //check if we have read the first n*3 lines
	    		break;
	    	}
	        printf("%s", line); //prints the line
	        i++;
	     }
	     fclose(fp1); //closes file
	     return;
	 }



bool checkboardfull(float (*board)[100], int input){ //checks if the board is full
	for(int i = 0; i < input; i++){
		for(int j = 0; j < input; j++){
			if (board[i][j] != 21 && board[i][j] != -21 && board[i][j] != 23 && board[i][j] != 24 && board[i][j] != 25){ //loops through the board and if it finds one piece thats not 21 or -21
															//it returns false because that means the board isnt full
				return false;
			}
		}
	}
	printf("Congrats! You win."); //win condition
	return true;
}


int main (int argc, char *argv[]){

	srand(time(0));
	time_t start, end; //clock
	float score = 0.0; //initial score
	float board[100][100];
	float topscore = 0; //setting top score
	int toptime = 0; //setting the top time
	int timeused; //for calculating the time the user played

	if(argc != 3){ //error handling
		printf("Invalid number of arguments\n");
		exit(0);
	}



	int input = atoi(argv[2]); //size is equal to the user input


	char buffer[150]; //buffer to store strings
	sprintf(buffer, "Player's name: %s \n", argv[1]);
	logScore(buffer);

	if(input < 5 || input > 20){ //checking if board size is okay
		printf("Invalid board size");
		exit(1);
	}


	int timer;

	//setting timer based on user input
	if(input >= 5 && input <= 7){
		timer = 60;
	}
	else if(input > 7 && input <= 10){
		timer = 100;
	}
	else if(input > 10 && input <= 13){
		timer = 140;
	}
	else if(input > 13 && input <= 16){
		timer = 180;
	}
	else if(input > 16 && input <= 18){
		timer = 220;
	}
	else{
		timer = 260;
	}

	int origtime = timer; //grabbing the original value of the timer

	//choices for checking if the player want to see the top scores
	int q;
	int choice;

	printf("\nWould you like to see the top scores? 0 for (yes) and 1 for (no):\n");
	scanf("%d", &q); //scanning the character
	if(q == 0){ //if they DO, we call the display top scores function
		printf("How many of the top score's would you like to see?\n");
		scanf("%d", &choice);
		displayTopScores(choice);
	}
	else if(q == 1){
		printf("Valid input, now continuing\n");
	}
	else{
		printf("Invalid input\n");
		exitGame();
	}

	initializeGame(board, input); //initializing the game board
	time(&start); //starting the timer

	while(1){ //entering game

		int x, y; //player move
		int question; //asking them if they want to see top scores before the game closes
		int prompt; //prompts them for topscore

		if(timer <= 0){ //turning timer to 0 if its negative
			timer = 0;
		}



		displayGame(board, input, timer, score); //displaying the game board


		printf("Enter [21 21] to exit\n"); //exit prompt
		printf("Enter your move (x y):");
		scanf("%d %d", &x, &y); //scanning value

		if((x > (input-1) || x < 0 ) && (x != 21) ){ //validating input
			printf("Input is out of bounds\n");
			continue;
		}
		else if((y > (input-1) || y < 0) && (y != 21) ){ //validating input
			printf("Input is out of bounds\n");
			continue;
		}

			//all the conditionals to check if the player landed on the surprises
		if(x == 1 && y == 3){
			printf("You got a nice suprise! (Score is doubled)\n");
			score = (int) score << 1;
			board[1][3] = 23;
			continue;
		}
		else if(x == 6 && y == 8){
			printf("You got a nice suprise! (Score is doubled)\n");
			score = (int) score << 1;
			board[6][8] = 23;
			continue;
		}
		else if(x == 12 && y == 14){
			printf("You got a nice suprise! (Score is doubled)\n");
			score = (int) score << 1;
			board[12][14] = 23;
			continue;
		}
		else if(x == 5 && y == 8){
			printf("You got a nice suprise! (Score is doubled)\n");
			score = (int) score << 1;
			board[5][8] = 23;
			continue;
		}
		else if(x == 2 && y == 4){
			printf("You got the bad surpise! (Score is halved)\n");
			score = (int) score >> 1;
			board[2][4] = 24;
			continue;
		}
		else if(x == 7 && y == 12){
			printf("You got the bad surpise! (Score is halved)\n");
			score = (int) score >> 1;
			board[7][12] = 24;
			continue;
		}
		else if(x == 9 && y == 5){
			printf("You got the bad surpise! (Score is halved)\n");
			score = (int) score >> 1;
			board[9][5] = 24;
			continue;
		}
		else if(x == 1 && y == 1){
			printf("You got the bad surpise! (Score is halved)\n");
			score = (int) score >> 1;
			board[1][1] = 24;
			continue;
		}
		else if(x == 9 && y == 2){
			printf("You got a time bonus! (You've been given extra time)\n");
			timer = timer + 30;
			board[9][2] = 25;
			continue;
		}
		else if(x == 2 && y == 2){
			printf("You got a time bonus! (You've been given extra time)\n");
			timer = timer + 30;
			board[2][2] = 25;
			continue;
		}



		if (x == 21 && y == 21){ //checking to see if move is 21 21 (to exit)
			if(board[9][2] == 25 && board[2][2] == 25){
				origtime = origtime + 60;
				timeused = (origtime - timer);
			}
			else if(board[9][2] == 25 || board[2][2] == 25){ //adding to the timer if the player got the surprises
				origtime = origtime + 30;
				timeused = (origtime - timer);
			}
			else{ //otherwise they did not land on the surprises
				timeused = (origtime - timer);
			}
			sprintf(buffer, "Score: %.2f\n", score); //logging the player's score
			logScore(buffer); //passing the buffer to the array
			sprintf(buffer, "Time used: %d\n", timeused); //logging the players timer
			logScore(buffer); //pass it on
			printf("\nWould you like to see the top scores? 0 for (yes) and 1 for (no):\n");
			scanf("%d", &question); //scanning the character
			if(question == 0){ //if they DO, we call the display top scores function
				if(score > topscore){ //updating the top score
					topscore = score;
					toptime = timer;
				}
				printf("How many of the top score's would you like to see?\n"); //prompt for if they want to see top scores
				scanf("%d", &prompt);
				displayTopScores(prompt);
				exitGame();
			}
			else if(question == 1){ //anything else means they input 'n' for no, so we simply exit the game
				printf("Valid input, now exiting the game");
				exitGame();
			}
			else{
				printf("Invalid input, now exiting game");
				exitGame();
			}
		}
		//similar to above, we're checking if they landed on the time bonuses and adding it to the timer
		else if(timer <= 0){
			if(board[9][2] == 25 && board[2][2] == 25){
				origtime = origtime + 60;
				timeused = (origtime - timer);
			}
			else if(board[9][2] == 25 || board[2][2] == 25){
				origtime = origtime + 30;
				timeused = (origtime - timer);
			}
			else{
				timeused = (origtime - timer);
			}
			sprintf(buffer, "Score: %.2f\n", score); //logging the player's score
			logScore(buffer); //passing the buffer to the array
			sprintf(buffer, "Time used: %d\n", timeused); //logging the players timer
			logScore(buffer); //pass it on
			printf("Times up!\n"); //checking to see if timer is less than or equal to 0
			printf("\nWould you like to see the top scores? 0 for (yes) and 1 for (no):\n");
			scanf("%d", &question); //scanning the character
			if(question == 0){ //if they DO, we call the display top scores function
				if(score > topscore){ //updating the top score
					topscore = score;
					toptime = timer;
			}
				printf("How many of the top score's would you like to see?\n");
				scanf("%d", &prompt);
				displayTopScores(prompt);
				exitGame();
				}
			else if(question == 1){ //anything else means they input 'n' for no, so we simply exit the game
				printf("Valid input, now exiting the game");
				exitGame();
				}
			else{
				printf("Invalid input, now exiting game");
				exitGame();
			}
		}
		//checking if all the pieces on the board have been used and then adding to the timer
		else if(checkboardfull(board, input)){
			if(board[9][2] == 25 && board[2][2] == 25){
				origtime = origtime + 60;
				timeused = (origtime - timer);
			}
			else if(board[9][2] == 25 || board[2][2] == 25){
				origtime = origtime + 30;
				timeused = (origtime - timer);
			}
			else{
				timeused = (origtime - timer);
			}
			sprintf(buffer, "Score: %.2f\n", score); //logging the player's score
			logScore(buffer); //passing the buffer to the array
			sprintf(buffer, "Time used: %d\n", timeused); //logging the players timer
			logScore(buffer); //pass it on
			printf("\nWould you like to see the top scores? 0 for (yes) and 1 for (no):\n");
			scanf("%d", &question); //scanning the character
				if(question == 0){ //if they DO, we call the display top scores function
					if(score > topscore){ //updating the top score
						topscore = score;
						toptime = timer;
					}
					printf("How many of the top score's would you like to see?\n");
					scanf("%d", &prompt);
					displayTopScores(prompt);
					exitGame();
					}
				else if(question == 1){ //anything else means they input 'n' for no, so we simply exit the game
					printf("Valid input, now exiting the game");
					exitGame();
					}
				else{
					printf("Invalid input, now exiting game");
					exitGame();
				}

		}
		else{ //progress the game
			time(&end); //ends time
			int difference = start - end;
			timer = timer + difference;

			//checking if the spot the user picked has already been chosen
			if(board[x][y] == 20 || board[x][y] == -20 || board[x][y] == 23 || board[x][y] == 24 || board[x][y] == 25){
				printf("Spot has already been picked, try again\n");
				continue;
			}
			else{
				float numberchosen = board[x][y]; //the number they picked was valid
				if(numberchosen < 0){
					printf("Bang!! You lost %.2f\n", numberchosen);
					score = calculateScore(score, numberchosen); //numberchosen is the number at board[x][y] and update the score
					board[x][y] = -20; //changing the value to -20
				}
				else if(numberchosen >= 0){
					printf("Uncovered a reward of %.2f\n", numberchosen);
					score = calculateScore(score, numberchosen); //numberchosen is the number at board[x][y] and update the score
					board[x][y] = 20; //change the value at [x][y] to 20
				}
			}

		}


	}







}
