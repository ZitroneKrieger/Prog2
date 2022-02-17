#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "rawio/rawio.h"

#define ISNUMMER 5
#define DIMENSION 8
#define OBSTACLES (8*8) * 0.15
#define FREI '.'
#define BESETZT '#'
#define ROBOTER 'O'
#define START_POINT 8
#define MAX_EARNED_POINTS 4
#define MOVEMENT_COST 1

struct Robot {
    int x;
    int y;
    char richtung;
    char punkte;
    int obstacleCount;
};

int KAM_CreateObstacles(char KAM_GameField [] [DIMENSION], int amount);
void KAM_MoveOneStep(char KAM_GameField [] [DIMENSION], struct Robot *); 
int KAM_StepByStep(char KAM_GameField [] [DIMENSION], struct Robot *, int); 
int KAM_PrintGame(char KAM_GameField [] [DIMENSION], struct Robot *);
int KAM_N_Steps(char KAM_GameField [] [DIMENSION], struct Robot *);

int main() {
    struct Robot roboter;
    // init gamefield set values
    char KAM_GameField [DIMENSION] [DIMENSION] = {{FREI,FREI,FREI,FREI,FREI,FREI,FREI,FREI},
                                                {FREI,FREI,FREI,FREI,FREI,FREI,FREI,FREI},
                                                {FREI,FREI,FREI,FREI,FREI,FREI,FREI,FREI},
                                                {FREI,FREI,FREI,FREI,FREI,FREI,FREI,FREI},
                                                {FREI,FREI,FREI,FREI,FREI,FREI,FREI,FREI},
                                                {FREI,FREI,FREI,FREI,FREI,FREI,FREI,FREI},
                                                {FREI,FREI,FREI,FREI,FREI,FREI,FREI,FREI},
                                                {FREI,FREI,FREI,FREI,FREI,FREI,FREI,FREI}};

    //set robot in die richtung nach angabe
    int anzahl = 0;
    roboter.x = 'M'%8;
	roboter.y = 'K'%8;
	roboter.richtung = 'l';
    roboter.punkte = START_POINT;

    anzahl = KAM_CreateObstacles(KAM_GameField, OBSTACLES);
    roboter.obstacleCount = anzahl;

    KAM_PrintGame(KAM_GameField, &roboter);

    printf("Welcome to the PAC man like game \n Use W-A-S-D to move \n");
    
    
    KAM_StepByStep(KAM_GameField, &roboter, anzahl);
    

    return 0;
}

int KAM_CreateObstacles(char KAM_GameField [] [DIMENSION], int amount){
    int i = 0;
    int anzahl = 0;
    int randomx, randomy;
    srand(time(NULL));
    for (; i < amount; ++i) {
        randomx = (rand() % (8 - 0) - 0 + 1) - 1;
        randomy = (rand() % (8 - 0) - 0 + 1) - 1;
        if(KAM_GameField[randomx][randomy] != FREI || (randomx == 'M'%8 && randomy == 'K'%8))
		{
			i--;
			continue;
		}
        anzahl += 1;
        KAM_GameField[randomx][randomy] = BESETZT;
    }
    return anzahl;
}

void KAM_MoveOneStep(char KAM_GameField [] [DIMENSION], struct Robot *roboter) {
    switch(roboter->richtung)
	{
        
		case 'a':
            if(roboter->x - 1 < 0) {
                return;
            }
            else {
                if(KAM_GameField [roboter->x - 1] [roboter->y] == BESETZT) {
                    KAM_GameField [roboter->x - 1] [roboter->y] = FREI;
                    roboter->obstacleCount--;
                    roboter->punkte += (rand() % MAX_EARNED_POINTS) + 1;
                }
                roboter->punkte -= 1;
                roboter->x -= 1;
            }
            break;
        case 'd': 
            if(roboter->x + 1 > 7) {
                return;
            }
            else {
                if(KAM_GameField [roboter->x + 1] [roboter->y] == BESETZT) {
                    KAM_GameField [roboter->x + 1] [roboter->y] = FREI;
                    roboter->obstacleCount--;
                    roboter->punkte += (rand() % MAX_EARNED_POINTS) + 1;
                }
                roboter->punkte -= 1;
                roboter->x += 1;
            }
            break;
        case 'w':
            if(roboter->y - 1 < 0) {
                return;
            }
            else {
                if(KAM_GameField [roboter->x] [roboter->y-1] == BESETZT) {
                    KAM_GameField [roboter->x] [roboter->y-1] = FREI;
                    roboter->obstacleCount--;
                    roboter->punkte += (rand() % MAX_EARNED_POINTS) + 1;
                }
                roboter->punkte -= 1;
                roboter->y -= 1;
            }
            break;
        case 's':
            if(roboter->y + 1 > 7 ) {
                return;
            }
            else {
                if(KAM_GameField [roboter->x] [roboter->y + 1] == BESETZT) {
                    KAM_GameField [roboter->x] [roboter->y + 1] = FREI;
                    roboter->obstacleCount--;
                    roboter->punkte += (rand() % MAX_EARNED_POINTS) + 1;
                }
                roboter->punkte -= 1;
                roboter->y += 1;
            }
            break;
        default:
            return;
    }
}

int KAM_PrintGame(char KAM_GameField [] [DIMENSION], struct Robot *roboter) {
    raw_clearscr();
    // gamefield wird ausgegeben
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            if(roboter->x == j && roboter->y == i){
                printf("%c ", ROBOTER);
                continue;
            }
            printf("%c ", KAM_GameField[j][i]);
        }
        printf("\n");
    }
    return 0;
}

int KAM_StepByStep(char KAM_GameField [] [DIMENSION], struct Robot * roboter, int anzahl) {
    char direction = ' ';
    printf("Bitte wählen sie eine richtung in die der  Roboter gehen soll: Oben (w), Unten (s), Rechts (d), Links (a)");
    
    while(direction != 'q'){

        direction = raw_fetchchar(0, 11);
        if(!(direction == 'w' || direction == 'a' || direction == 's' || direction == 'd')) {
            continue;
        }
        roboter->richtung = direction;
        KAM_MoveOneStep(KAM_GameField, roboter);
        if (roboter->punkte == 0) {
            raw_clearscr();
            printf("You lost, your points ran out!");
            return 0;
        }
        if(roboter->obstacleCount == 0) {
            raw_clearscr();
            KAM_PrintGame(KAM_GameField, roboter);
            printf("You Won WOW!!!");
            return 0;
        }
        KAM_PrintGame(KAM_GameField, roboter);
        printf("Your Points: %d\n", roboter->punkte);
    }
    
    return 0;
}



