#include<bits/stdc++.h>
#include<stdio.h>

using namespace std;

//For setting X or O or _ in the grid
char gridChar(int i);
//For executing a move 
void draw_a_move(int b[9]);
//This determines if a player has won, returns 0 otherwise.
//All the possible wining position is already stored in an array
int win(const int board[9]);
//This is the recursive algorithm
//Which perform full tree search and find the optimal fitted position
//Returns a score based on minimax tree at a given node.
int minimax(int boad[9], int rating);
//Opponent => Computer which basically calls the minimax function
void opponent(int board[9]);
//User's turn
void your(int board[9]);

int main()
{
	printf("\n\n\t\t\t\t\t\t   PROGRAMMING FOR PROBLEM SOLVING \n");
	printf("\t\t\t\t\t\t ______________________________________ \n\n\n");
    printf("\t\t\t\t\t   TIC-TAC-TOE GAME USING MINIMAX ALGORITHM : GAME THEORY \n");
	printf("\t\t\t\t\t ___________________________________________________________ \n\n\n");
    printf("\t\t\t\t\t\t\t ( YOU CAN'T BEAT IT ) \n");
	
	printf("Computer: O , You: X\n");
	int choice = 0;
	printf("Please select your choice : 1 => 1st Draw or 2 => 2nd Draw\n");
	scanf("%d",&choice);
	
	int board[9] = {0,0,0,0,0,0,0,0,0};
	int turn;
	for (turn = 0; turn < 9 && win(board) == 0; turn++){
		
			if ((turn+choice)%2 == 0){
				opponent(board);
			}else{
				draw_a_move(board);
				your(board);
			}
		}
	
	switch(win(board)) {
        case 0:
            printf("Match draw\n");
            break;
        case 1:
            draw_a_move(board);
            printf("You lose.\n");
            break;
        case -1:
            printf("You win. \n");
            break;
    }
	
	return 0;
}

// -------------------------------Defining all the functions-------------------------------------------------

char gridChar(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

void draw_a_move(int b[9]) {
    printf("\t\t\t (0)  %c | (1)  %c | (2)  %c\n",gridChar(b[0]),gridChar(b[1]),gridChar(b[2]));
    printf("\t\t\t---------+---------+--------\n");
    printf("\t\t\t (3)  %c | (4)  %c | (5)  %c\n",gridChar(b[3]),gridChar(b[4]),gridChar(b[5]));
    printf("\t\t\t---------+---------+--------\n");
    printf("\t\t\t (6)  %c | (7)  %c | (8)  %c\n",gridChar(b[6]),gridChar(b[7]),gridChar(b[8]));
}

int win(const int board[9]) {
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}


int minimax(int board[9], int rating){
	int winner = win(board);
	
	if (winner != 0) {
        return winner*rating;
    }
	int move = -1;
	int score = -2;
	int i;
	for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = rating;
            int thisScore = -minimax(board, rating*-1);
            if(thisScore > score) {
                score = thisScore;
               
                move = i;
            }
            board[i] = 0;
        }
    }
    
    if(move == -1) return 0;
    return score;
}

void opponent(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
				move = i;
            }
        }
    }
    board[move] = 1;
}

void your(int board[9]) 
{
	int move = 0;
	do {
		start:
		printf("\nInput move ([0..8]): ");
		scanf("%d", &move);
		
		if(board[move] != 0) {
			printf("Its Already Occupied !");
			goto start;
		}
		printf("\n");
	} while (move >= 9 || move < 0 && board[move] == 0);
	board[move] = -1;
}
