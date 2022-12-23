#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define COLOR_RED     "\x1b[31m"
#define COLOR_YELLOW  "\x1b[33m"
//structure for players
typedef struct{
  char name[30];
  int score;


}player;
void menu();
void lines();
void game();
void computerEasy();
void game_end(char choice);
//void add_score();
int check_number(char move[20]);
int Hcheck(int x,int y,char board[x][y],int row,int move);
int Vcheck(int x,int y,char board[x][y],int row,int move);
int D1check(int x,int y,char board[x][y],int row,int move);
int D2check(int x,int y,char board[x][y],int row,int move);

int main()
{

    menu();

    return 0;
}

void print(int x,int y,char board[x][y]){
     for(int k=0;k<x;k++){
        //printf("\n---------\n");
        printf("\n");
        for(int u=0;u<(y*2.1);u++){
            printf("-");
        }
        printf("\n");
        for(int m=0;m<y;m++){
            if(m==y-1){
                printf("|");
                printf("%c",board[k][m]);
                printf("|");
            }
            else{
                printf("|");
                printf("%c",board[k][m]);
            }


        }

    }
    printf("\n");
    for(int m=0;m<y;m++){
        printf(" %d",m+1);
    }
}

void game(){
    int turn=0;
    char move[20];
    int correct_move=0;
    player player1,player2;
    player1.score=0;
    player2.score=0;
    char choice;
    //read from xml
    int x=5,y=5;
    char board[x][y];
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            board[i][j]=' ';
        }
    }
    print(x,y,board);
    for(int i=1;i<=(x*y);i++){
        if(turn%2==0){
            printf("\nPlayer %d's turn\nNumber of moves made: %d\n",turn%2+1,turn/2);
            printf("score1=%d\n",player1.score);
            printf("score2=%d\n",player2.score);
            printf("%s",COLOR_RED);

        }
        else{
            printf("\nPlayer %d's turn\nNumber of moves made: %d\n",turn%2+1,turn/2);
            printf("score1=%d\n",player1.score);
            printf("score2=%d\n",player2.score);
            printf("%s",COLOR_YELLOW);
        }

        scanf("%s",move);
        correct_move=check_number(move);
            while(correct_move<1 || correct_move>y ){
                printf("WRONG INPUT, TRY AGAIN\n");
                scanf("%s",move);
                correct_move=check_number(move);
            }

        int row=0,t=x;
        for(int j=x-1;j>=0;j--){
            if(board[j][correct_move-1]==' '){
                 row=j;
                 break;
            }
            else t--;
        }
        if(t>0){
            board[row][correct_move-1]=(turn%2==0? 'X':'O');
             if(board[row][correct_move-1]=='X'){
               player1.score= Vcheck(x,y,board,row,correct_move-1)+Hcheck(x,y,board,row,correct_move-1)+D1check(x,y,board,row,correct_move-1)+D2check(x,y,board,row,correct_move-1);
            }else if(board[row][correct_move-1]=='O'){
            player2.score= Vcheck(x,y,board,row,correct_move-1)+Hcheck(x,y,board,row,correct_move-1)+D1check(x,y,board,row,correct_move-1)+D2check(x,y,board,row,correct_move-1);
            }
            turn++;
            system("cls");
        }
        else{
            printf("PLACE OCCUPIED, TRY AGAIN\n");
            i--;
            continue;
        }
        print(x,y,board);


    }
    if(player1.score>player2.score){
        printf("\nplayer1, please enter your name:\n");
        scanf("%s",player1.name);
        fflush(stdin);
        system("cls");
        printf("a)Main Menu\n");
        lines();
        printf("b)Exit\n");
        scanf("%c",&choice);
        fflush(stdin);
        game_end(choice);
        //add_score(player1.name,player1.score);
    }else if(player2.score>player1.score){
        printf("\nplayer2, please enter your name:\n");
        scanf("%s",player2.name);
        fflush(stdin);
         system("cls");
        printf("a)Main Menu\n");
        lines();
        printf("b)Exit\n");
        scanf("%c",&choice);
        fflush(stdin);
      game_end(choice);
        //add_score(player2.name,player2.score);
    }
    else{
            system("cls");
        printf("There's no winner\n");
        fflush(stdin);
      printf("a)Main Menu\n");
        lines();
        printf("b)Exit\n");
        scanf("%c",&choice);
        fflush(stdin);
        game_end(choice);
    }
}
void computerEasy(){
    int turn=0;
    char move[20];
    int correct_move=0;
    char choice;
    player player1;
    int compScore=0;
    //read from xml
    int x=5,y=5;
    int vacant[y];
    char board[x][y];
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            board[i][j]=' ';
            vacant[i]=0;
        }
    }
    print(x,y,board);
    for(int i=1;i<=(x*y);i++){
        if(turn%2==0){
            printf("\nPlayer %d's turn\nNumber of moves made: %d\n",turn%2+1,turn/2);
            printf("Player's Score=%d\n",player1.score);
            printf("Computer's Score=%d\n",compScore);
            printf("%s",COLOR_RED);
            scanf("%s",move);
        correct_move=check_number(move);
            while(correct_move<1 || correct_move>y ){
                printf("WRONG INPUT, TRY AGAIN\n");
                scanf("%s",move);
                correct_move=check_number(move);
            }
        }
        else{
                correct_move=atoi(move);
            srand(time(NULL));
            correct_move=1+rand()%(y-2);
            if(vacant[correct_move-1]==x){
                for(int r=0;r<y;r++){
                    if(vacant[r]<x){
                        correct_move=r+1;

                    }
                }
            }
            sleep(1);
            printf("%s",COLOR_YELLOW);
        }
        int row=0,t=x;
        for(int j=x-1;j>=0;j--){
            if(board[j][correct_move-1]==' '){
                 row=j;
                 break;
            }
            else t--;
        }
        if(t>0){
            board[row][correct_move-1]=(turn%2==0? 'X':'O');
            vacant[correct_move-1]++;
             if(board[row][correct_move-1]=='X'){
               player1.score=Vcheck(x,y,board,row,correct_move-1)+Hcheck(x,y,board,row,correct_move-1)+D1check(x,y,board,row,correct_move-1)+D2check(x,y,board,row,correct_move-1);
            }else if(board[row][correct_move-1]=='O'){
            compScore=Vcheck(x,y,board,row,correct_move-1)+Hcheck(x,y,board,row,correct_move-1)+D1check(x,y,board,row,correct_move-1)+D2check(x,y,board,row,correct_move-1);
            }
            turn++;
            system("cls");
        }
        else{
            printf("PLACE OCCUPIED, TRY AGAIN\n");
            i--;
            continue;
        }
        print(x,y,board);
    }
    if(player1.score>compScore){
        printf("\nplayer1, please enter your name:\n");
        scanf("%s",player1.name);
        fflush(stdin);
        system("cls");
        printf("a)Main Menu\n");
        lines();
        printf("b)Exit\n");
        scanf("%c",&choice);
        fflush(stdin);
        game_end(choice);
        //add_score(player1.name,player1.score);
    }else if(compScore>player1.score){
        printf("\nComputer won\n");
        sleep(1);
        system("cls");
        printf("a)Main Menu\n");
        lines();
        printf("b)Exit\n");
        scanf("%c",&choice);
        fflush(stdin);
        game_end(choice);
        //add_score(player2.name,player2.score);
    }
    else{
            fflush(stdin);
            system("cls");
        printf("There's no winner\n");
        fflush(stdin);
      printf("a)Main Menu\n");
        lines();
        printf("b)Exit\n");
        scanf("%c",&choice);
        fflush(stdin);
        game_end(choice);
    }
}

void menu(){
    //function to start a game
    //system("color 3c");
    printf("                         WELCOME TO CONNECT FOUR\n");
    char choice1,choice2,choice3;
    FILE *fp_in; //pointer to top player's file
    printf("a)Start a new game\n");
    lines();
    printf("b)Load a game\n");
    lines();
    printf("c) Top players\n");
    lines();
    printf("d)Quit \n");
    lines();
    printf("e)Help!\n");

    scanf("%c",&choice1);
    fflush(stdin);
    switch(choice1){
        case'a':
            system("cls");
            printf("Choose game mode\n");
            lines();
            printf("a)human vs human OR b)human vs computer\n");
            scanf("%c",&choice2);
            fflush(stdin);
            switch(choice2){
                case'a':
                    system("cls");
                    //with human
                    game();
                    break;
                case'b':
                    system("cls");
                    printf("choose the mode of computer [a)easy OR b)medium]\n");
                    scanf("%c",&choice3);
                    fflush(stdin);
                    switch(choice3){
                        case 'a':
                            system("cls");
                            //easy computer
                            computerEasy();
                            break;
                        case'b':
                            system("cls");
                            //med computer
                            break;
                    }
                    break;
            }
            break;
        case'b':
            system("cls");
            printf("choose the saved game to load\n");
            //function for saved games
            break;
        case'c':
            system("cls");
            //function for top players
            fp_in=fopen("Top_players.txt","rb");
            fclose(fp_in);
            break;
        case'd':
            system("cls");
            printf("GOOD BYE\n");
            break;
        case'e':
            system("cls");
            printf("the goal of the game is to connect four discs horizontally,vertically OR diagonally,the game ends when the board is full\n");
            printf("we check the score of each player,\n");
            printf("and the player with the higher score is considered as the winner\n");
            break;
        default:
            system("cls");
            printf("not available choice,TRY AGAIN");
            menu();
    }
}
void lines(){
    printf("===================\n");
}

//function to check if we connected four horizontally
int Hcheck(int x,int y,char board[x][y],int row,int move){
    int n;
    int count=0;
    int score=0;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(board[i][j]==board[i][j+1]&&board[i][j]==board[row][move]){
                for(int k=j;k<j+3;k++){
                        if(board[i][k]==board[i][k+1]){
                            count++;
                        }else{
                        count=0;
                        break;
                        }
                }
                if(count==3){
                    score++;
                    count=0;
                }
            }
        }
    }
    return score;
}
//function to check if we connected four vertically
int Vcheck(int x,int y,char board[x][y],int row,int move){
    int n;
    int count=0;
    int score=0;
    for(int i=0;i<y;i++){
        for(int j=0;j<x;j++){
            if(board[j][i]==board[j+1][i]&&board[j][i]==board[row][move]){
                for(int k=j;k<j+3;k++){
                        if(board[k][i]==board[k+1][i]){
                            count++;
                        }else{
                        count=0;
                        break;
                        }
                }
                if(count==3){
                    score++;
                    count=0;
                }
            }
        }
    }
    return score;
}
   //function to check if we connected four diagonally with an obtuse angle
int D1check(int x,int y,char board[x][y],int row,int move){
    int n;
    int count=0;
    int score=0;
    for(int i=0;i<x;i++){
            n=i;
        for(int j=0;j<y;j++){
            if(board[i][j]==board[i+1][j+1]&&board[i][j]==board[row][move]){
                for(int k=j;k<j+3;k++){
                        if(board[n][k]==board[n+1][k+1]){
                            count++;
                            n++;
                        }else{
                        count=0;
                        break;
                        }
                }
                if(count==3){
                    score++;
                    count=0;
                }
            }
        }
    }
    return score;
}
      //function to check if we connected four diagonally with an acute angle
int D2check(int x,int y,char board[x][y],int row,int move){
    int n;
    int count=0;
    int score=0;
    for(int i=0;i<x;i++){
            n=i;
        for(int j=0;j<y;j++){
            if(board[i][j]==board[i+1][j-1]&&board[i][j]==board[row][move]){
                for(int k=j;k>j-3;k--){
                        if(board[n][k]==board[n+1][k-1]){
                            count++;
                            n++;
                        }else{
                        count=0;
                        break;
                        }
                }
                if(count==3){
                    score++;
                    count=0;
                }

            }
        }
    }
    return score;
   }
/*void add_score(int score,char name[30]){
FILE *fp_out;
FILE *fp_in;
char names[10][30];
for(int i=0;i<10;i++){
    strcpy(names[i],' ');
}
int scores[10]={0};
int temp1;
char temp2[30];
fp_out=fopen("Top_players.txt","rb");
for(int i=0;i<10;i++){
    fgets(fp_in,sizeof(names[i]),names[i]);
    fflush(stdin);
    fscanf(fp_in,"%d",scores[i]);
}
if(score>scores[9]){
    scores[9]==score;
    strcpy(name,names[9]);
}
for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
        if(scores[j]<scores[i]){
            temp1=scores[i];
            scores[i]=scores[j];
            scores[j]=temp1;
        strcpy(temp2,names[i]);
          strcpy(names[j],names[i]);
          strcpy(names[j],temp2);
        }
    }

}

for(int i=0;i<10;i++){
    fprintf(fp_out,"%s    %d",names[i],scores[i]);
}
fclose(fp_out);


}*/
void game_end(char choice){
    switch(choice){
    case'a':
         system("cls");
        menu();
        break;
    case'b':
        system("cls");
        printf("Good bye\n");
        break;
        }
}
int check_number(char move[20]){
    int correct_move=0;
        if(isalpha(move[0])!=0){
        correct_move=0;
        }else{
        correct_move=atoi(move);

        }
        return correct_move;


}

