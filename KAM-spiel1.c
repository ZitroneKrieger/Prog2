#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ISNUMMER 5
#define DIMENSION 8
#define OBSTACLES (8*8) * 0.15
#define FREI '.'
#define BESETZT '#'
#define ROBOTER 'O'

struct Robot {
    int x;
    int y;
    char richtung;
};

int KAM_CreateObstacles(char KAM_GameField [] [DIMENSION], int amount);
int KAM_MoveOneStep(char KAM_GameField [] [DIMENSION], struct Robot *); 
int KAM_StepByStep(char KAM_GameField [] [DIMENSION], struct Robot *); 
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
    roboter.x = 'M'%8;
	roboter.y = 'K'%8;
	roboter.richtung = 'l';
    KAM_CreateObstacles(KAM_GameField, OBSTACLES);


    KAM_PrintGame(KAM_GameField, &roboter);

    printf("Einzelschrittmodus (1) oder auf einmal: \n");

    int mode = 1;


    
    // KAM_MoveOneStep(KAM_GameField, &roboter);
    scanf("%d", &mode);
    

    if (mode == 2){
        KAM_N_Steps(KAM_GameField, &roboter);
    } else {
        KAM_StepByStep(KAM_GameField, &roboter);
    }

    return 0;
}

int KAM_CreateObstacles(char KAM_GameField [] [DIMENSION], int amount){
    int i = 0;
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

        KAM_GameField[randomx][randomy] = BESETZT;
    }
    return 0;
}

int KAM_MoveOneStep(char KAM_GameField [] [DIMENSION], struct Robot *roboter) {
    switch(roboter->richtung)
	{
        
		case 'l':
            if(roboter->x - 1 < 0 || KAM_GameField [roboter->x - 1] [roboter->y] == BESETZT) {
                roboter->richtung = 'o';
                KAM_MoveOneStep(KAM_GameField, roboter);
            }
            else {
                roboter->x -= 1;
            }
            break;
        case 'r':
            if(roboter->x + 1 > 7 || KAM_GameField [roboter->x + 1] [roboter->y] == BESETZT) {
                roboter->richtung = 'u';
                KAM_MoveOneStep(KAM_GameField, roboter);
            }
            else {
                roboter->x += 1;
            }
            break;
        case 'o':
            if(roboter->y - 1 < 0 || KAM_GameField [roboter->x] [roboter->y-1] == BESETZT) {
                roboter->richtung = 'r';
                KAM_MoveOneStep(KAM_GameField, roboter);
            }
            else {
                roboter->y -= 1;
            }
            break;
        case 'u':
            if(roboter->y + 1 > 7 || KAM_GameField [roboter->x] [roboter->y + 1] == BESETZT) {
                roboter->richtung = 'l';
                KAM_MoveOneStep(KAM_GameField, roboter);
            }
            else {
                roboter->y += 1;
            }
            break;
    }
    return 0;
}

int KAM_PrintGame(char KAM_GameField [] [DIMENSION], struct Robot *roboter) {

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

int KAM_StepByStep(char KAM_GameField [] [DIMENSION], struct Robot * roboter) {
    char buffer [10] = "";
    getchar();
    

    while(strcmp(buffer, "quit\n") != 0){
        fgets(buffer, sizeof(buffer), stdin);
        KAM_MoveOneStep(KAM_GameField, roboter);

        KAM_PrintGame(KAM_GameField, roboter);
    }
    
    return 0;
}

int KAM_N_Steps(char KAM_GameField [] [DIMENSION], struct Robot * roboter) {
    int amount = 1;
    printf("Wie viele Schritte auf einmal? ");
    scanf("%d", &amount);

    for(int i = 0; i < amount; ++i) {
        KAM_MoveOneStep(KAM_GameField, roboter);
        KAM_PrintGame(KAM_GameField, roboter);
        sleep(5);
    }
    return 0;
}



