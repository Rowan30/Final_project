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
int ai[4];
void menu();
void lines();
void game();
void computerEasy();
void computermed();
void game_end(char choice);
void show_scores();
void sort_top();
void add_score();
int check_number(char move[20]);
int scores_sum(int x,int y,char board[x][y],int row,int move);
int Hcheck(int x,int y,char board[x][y],int row,int move);
int Vcheck(int x,int y,char board[x][y],int row,int move);
int D1check(int x,int y,char board[x][y],int row,int move);
int D2check(int x,int y,char board[x][y],int row,int move);

int main(){
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
    int row=0;
    player player1,player2;
    player1.score=0;
    player2.score=0;
    char choice;
    clock_t t1,t2;
    double t3=0;
    int undo[25]={0};
    int undo1[25]={0};
    int v=0;
    int f=0;
    //double t2=0;
    //read from xml
    int x=5,y=5;
    int k=0;
    char board[x][y];
    for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                board[i][j]=' ';
            }
    }
    print(x,y,board);
    for(int i=1;i<=(x*y);i++){
        t1=clock();
        if(turn%2==0){
            printf("\nPlayer %d's turn\nNumber of moves made: %d\n",turn%2+1,turn/2);
            printf("score1=%d\n",player1.score);
            printf("score2=%d\n",player2.score);
            printf("Press 'u' for undo\n");
            printf("Press 'r' for redo\n");
            printf("time from starting the game=%d:%d\n",(int)t3/60,(int)t3%60);
            printf("%s",COLOR_RED);
        }
        else{
            printf("\nPlayer %d's turn\nNumber of moves made: %d\n",turn%2+1,turn/2);
            printf("score1=%d\n",player1.score);
            printf("score2=%d\n",player2.score);
            printf("Press 'u' for undo\n");
            printf("Press 'r' for redo\n");
            printf("time from starting the game=%d:%d\n",(int)t3/60,(int)t3%60);
            printf("%s",COLOR_YELLOW);
        }
        scanf("%s",move);
        //undo
       if(move[0]=='u'&&turn>0&&f>0){
            system("cls");
            board[row][correct_move-1]=' ';
            correct_move=undo[--f];
            row=undo1[f];
            i=i-2;
            turn--;
            v++;
            k=f-1;
            if(board[row][correct_move-1]=='X'){
                player1.score= scores_sum(x,y,board,row,correct_move-1);
            }else if(board[row][correct_move-1]=='O'){
                player2.score= scores_sum(x,y,board,row,correct_move-1);
            }
        }//redo
        else if(move[0]=='r'&&v>0){
            system("cls");
            correct_move=undo[++f];
            row=undo1[f];
            board[row][correct_move-1]=(turn%2==0? 'X':'O');
            turn++;
            v--;
            k=f+1;
            if(board[row][correct_move-1]=='X'){
                player1.score= scores_sum(x,y,board,row,correct_move-1);
            }else if(board[row][correct_move-1]=='O'){
                player2.score= scores_sum(x,y,board,row,correct_move-1);
            }
        }
        else{
                correct_move=check_number(move);
                while(correct_move<1 || correct_move>y ){
                    printf("WRONG INPUT, TRY AGAIN\n");
                    scanf("%s",move);
                    correct_move=check_number(move);
                }
                row=0;
                int t=x;
                for(int j=x-1;j>=0;j--){
                        if(board[j][correct_move-1]==' '){
                             row=j;
                             break;
                        }
                        else t--;
                }
                if(t>0){
                    board[row][correct_move-1]=(turn%2==0? 'X':'O');
                    undo[k]=correct_move;
                    undo1[k]=row;
                    if(board[row][correct_move-1]=='X'){
                        player1.score= scores_sum(x,y,board,row,correct_move-1);
                    }else if(board[row][correct_move-1]=='O'){
                        undo[k]=correct_move;
                        player2.score= scores_sum(x,y,board,row,correct_move-1);
                    }
                    turn++;
                    k++;
                    f=k-1;
                    v=0;
                    system("cls");
                }
                else{
                    printf("PLACE OCCUPIED, TRY AGAIN\n");
                    i--;
                    v=0;
                    continue;
                }
            }
            print(x,y,board);
            t2=clock();
            t3=t3+((t2-t1)/(double)CLOCKS_PER_SEC);
    }
    if(player1.score>player2.score){
            printf("\nplayer1, please enter your name:\n");
            Beep(467,1500);
            Beep(526,1500);
            Beep(624,1500);
            fflush(stdin);
            gets(player1.name);
            fflush(stdin);
            system("cls");
            printf("a)Main Menu\n");
            lines();
            printf("b)Exit\n");
            scanf("%c",&choice);
            fflush(stdin);
            game_end(choice);
            for(int s=0;s<strlen(player1.name);s++){
                    player1.name[s]=tolower(player1.name[s]);
            }
            sort_top(player1.name,player1.score);
    }else if(player2.score>player1.score){
            printf("\nplayer2, please enter your name:\n");
            Beep(467,1500);
            Beep(526,1500);
            Beep(624,1500);
            fflush(stdin);
            gets(player2.name);
            fflush(stdin);
            system("cls");
            printf("a)Main Menu\n");
            lines();
            printf("b)Exit\n");
            scanf("%c",&choice);
            fflush(stdin);
            game_end(choice);
            sort_top(player2.name,player2.score);
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
    char move[20];
    int correct_move=0;
    char choice;
    player player1;
    clock_t t1,t2;
    double t3=0;
    int undo[25]={0};
    int undo1[25]={0};
    int turn=0,v=0,f=0,k=0,row=0,compScore=0;
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
    //print(x,y,board);
    for(int i=1;i<=(x*y);i++){
            system("cls");
            t1=clock();
            print(x,y,board);
            if(turn%2==0){
                printf("\nPlayer %d's turn\nNumber of moves made: %d\n",turn%2+1,turn/2);
                printf("Player's Score=%d\n",player1.score);
                printf("Computer's Score=%d\n",compScore);
                printf("Press 'u' for undo\n");
                printf("Press 'r' for redo\n");
                printf("time from starting the game=%d:%d\n",(int)t3/60,(int)t3%60);
                printf("%s",COLOR_RED);
                scanf("%s",move);
                if(move[0]=='u'&&turn>0&&f>0){
                    system("cls");
                    board[row][correct_move-1]=' ';
                    turn--;
                    correct_move=undo[--f];
                    row=undo1[f];
                    board[row][correct_move-1]=' ';
                    correct_move=undo[--f];
                    row=undo1[f];
                    i=i-4;
                    turn--;
                    v++;
                    k=f-1;
                    if(board[row][correct_move-1]=='X'){
                        player1.score= scores_sum(x,y,board,row,correct_move-1);
                    }
                    else if(board[row][correct_move-1]=='O'){
                        compScore= scores_sum(x,y,board,row,correct_move-1);
                    }
                    t2=clock();
                    t3=t3+((t2-t1)/(double)CLOCKS_PER_SEC);
                    continue;
                }else if(move[0]=='r'&&v>0){
                    system("cls");
                    correct_move=undo[++f];
                    row=undo1[f];
                    board[row][correct_move-1]=(turn%2==0? 'X':'O');
                    turn++;
                    correct_move=undo[++f];
                    row=undo1[f];
                    board[row][correct_move-1]=(turn%2==0? 'X':'O');
                    turn++;
                    v--;
                    k=f+1;
                    if(board[row][correct_move-1]=='X'){
                        player1.score= scores_sum(x,y,board,row,correct_move-1);
                    }else if(board[row][correct_move-1]=='O'){
                        compScore= scores_sum(x,y,board,row,correct_move-1);
                    }
                    i=i+2;
                    t2=clock();
                    t3=t3+((t2-t1)/(double)CLOCKS_PER_SEC);
                    continue;
                    }else{
                        correct_move=check_number(move);
                        while(correct_move<1 || correct_move>y ){
                            printf("WRONG INPUT, TRY AGAIN\n");
                            scanf("%s",move);
                            correct_move=check_number(move);
                        }
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
            row=0;
            int t=x;
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
                undo[k]=correct_move;
                undo1[k]=row;
                if(board[row][correct_move-1]=='X'){
                    player1.score=scores_sum(x,y,board,row,correct_move-1);
                }else if(board[row][correct_move-1]=='O'){
                    compScore=scores_sum(x,y,board,row,correct_move-1);
                }
                turn++;
                k++;
                f=k-1;
                v=0;
            }
            else{
                printf("PLACE OCCUPIED, TRY AGAIN\n");
                i--;
                sleep(1);
                continue;
            }
            t2=clock();
            t3=t3+((t2-t1)/(double)CLOCKS_PER_SEC);
    }
    system("cls");
    print(x,y,board);
    if(player1.score>compScore){
        printf("\nplayer1, please enter your name:\n");
        Beep(467,1500);
        Beep(526,1500);
        Beep(624,1500);
        fflush(stdin);
        gets(player1.name);
        fflush(stdin);
        system("cls");
        printf("a)Main Menu\n");
        lines();
        printf("b)Exit\n");
        scanf("%c",&choice);
        fflush(stdin);
        game_end(choice);
        for(int s=0;s<strlen(player1.name);s++){
            player1.name[s]=tolower(player1.name[s]);
        }
        sort_top(player1.name,player1.score);
    }else if(compScore>player1.score){
        fflush(stdin);
        printf("\nComputer won\n");
        sleep(1);
        system("cls");
        printf("a)Main Menu\n");
        lines();
        printf("b)Exit\n");
        scanf("%c",&choice);
        fflush(stdin);
        game_end(choice);
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
void computermed(){
    for(int i=0;i<4;i++){
        ai[i]=-1;
    }
    char move[20];
    int correct_move=0;
    char choice;
    player player1;
    clock_t t1,t2;
    double t3=0;
    int undo[25]={0};
    int undo1[25]={0};
    int turn=0,v=0,f=0,k=0,row=0,compScore=0;
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
    //print(x,y,board);
    for(int i=1;i<=(x*y);i++){
            system("cls");
            t1=clock();
            print(x,y,board);
            if(turn%2==0){
                printf("\nPlayer %d's turn\nNumber of moves made: %d\n",turn%2+1,turn/2);
                printf("Player's Score=%d\n",player1.score);
                printf("Computer's Score=%d\n",compScore);
                printf("Press 'u' for undo\n");
                printf("Press 'r' for redo\n");
                printf("time from starting the game=%d:%d\n",(int)t3/60,(int)t3%60);
                printf("%s",COLOR_RED);
                scanf("%s",move);
                if(move[0]=='u'&&turn>0&&f>0){
                    system("cls");
                    board[row][correct_move-1]=' ';
                    turn--;
                    correct_move=undo[--f];
                    row=undo1[f];
                    board[row][correct_move-1]=' ';
                    correct_move=undo[--f];
                    row=undo1[f];
                    i=i-4;
                    turn--;
                    v++;
                    k=f-1;
                    if(board[row][correct_move-1]=='X'){
                        player1.score= scores_sum(x,y,board,row,correct_move-1);
                    }
                    else if(board[row][correct_move-1]=='O'){
                        compScore= scores_sum(x,y,board,row,correct_move-1);
                    }
                    t2=clock();
                    t3=t3+((t2-t1)/(double)CLOCKS_PER_SEC);
                    continue;
                }else if(move[0]=='r'&&v>0){
                    system("cls");
                    correct_move=undo[++f];
                    row=undo1[f];
                    board[row][correct_move-1]=(turn%2==0? 'X':'O');
                    turn++;
                    correct_move=undo[++f];
                    row=undo1[f];
                    board[row][correct_move-1]=(turn%2==0? 'X':'O');
                    turn++;
                    v--;
                    k=f+1;
                    if(board[row][correct_move-1]=='X'){
                        player1.score= scores_sum(x,y,board,row,correct_move-1);
                    }else if(board[row][correct_move-1]=='O'){
                        compScore= scores_sum(x,y,board,row,correct_move-1);
                        for(int z=0;z<4;z++){
                            ai[i]=-1;
                        }
                    }
                    i=i+2;
                    t2=clock();
                    t3=t3+((t2-t1)/(double)CLOCKS_PER_SEC);
                    continue;
                    }else{
                        correct_move=check_number(move);
                        while(correct_move<1 || correct_move>y ){
                            printf("WRONG INPUT, TRY AGAIN\n");
                            scanf("%s",move);
                            correct_move=check_number(move);
                        }
                    }
            }
            else{
                    correct_move=atoi(move);
                    int c=0;
                    for(int i=0;i<4;i++){
                        if(ai[i]>=0){
                            correct_move=ai[i]+1;
                            ai[i]=-1;
                            c=1;
                            break;
                        }
                    }
                    if(c==0){
                            srand(time(NULL));
                            correct_move=1+rand()%(y-2);
                            if(vacant[correct_move-1]==x){
                                    for(int r=0;r<y;r++){
                                        if(vacant[r]<x){
                                            correct_move=r+1;
                                        }
                                    }
                            }
                    }
                    sleep(1);
                    printf("%s",COLOR_YELLOW);
            }
            row=0;
            int t=x;
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
                undo[k]=correct_move;
                undo1[k]=row;
                if(board[row][correct_move-1]=='X'){
                    player1.score=scores_sum(x,y,board,row,correct_move-1);
                }else if(board[row][correct_move-1]=='O'){
                    compScore=scores_sum(x,y,board,row,correct_move-1);
                }
                turn++;
                k++;
                f=k-1;
                v=0;
            }
            else{
                printf("PLACE OCCUPIED, TRY AGAIN\n");
                i--;
                sleep(1);
                continue;
            }
            t2=clock();
            t3=t3+((t2-t1)/(double)CLOCKS_PER_SEC);
    }
    system("cls");
    print(x,y,board);
    if(player1.score>compScore){
        printf("\nplayer1, please enter your name:\n");
        Beep(467,1500);
        Beep(526,1500);
        Beep(624,1500);
        fflush(stdin);
        gets(player1.name);
        fflush(stdin);
        system("cls");
        printf("a)Main Menu\n");
        lines();
        printf("b)Exit\n");
        scanf("%c",&choice);
        fflush(stdin);
        game_end(choice);
        for(int s=0;s<strlen(player1.name);s++){
            player1.name[s]=tolower(player1.name[s]);
        }
        sort_top(player1.name,player1.score);
    }else if(compScore>player1.score){
        fflush(stdin);
        printf("\nComputer won\n");
        sleep(1);
        system("cls");
        printf("a)Main Menu\n");
        lines();
        printf("b)Exit\n");
        scanf("%c",&choice);
        fflush(stdin);
        game_end(choice);
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
    Beep(467,500);
    lines();
    printf("b)Load a game\n");
    Beep(526,500);
    lines();
    printf("c) Top players\n");
    Beep(624,500);
    lines();
    printf("d)Quit \n");
    Beep(314,500);
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
                            computermed();
                            break;
                        default:
                            system("cls");
                            menu();
                    }
                    break;
                default:
                    system("cls");
                    menu();
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
            show_scores();
            break;
        case'd':
            system("cls");
            printf("GOOD BYE\n");
            sleep(1);
            break;
        case'e':
            system("cls");
            printf("the goal of the game is to connect four discs horizontally,vertically OR diagonally,the game ends when the board is full\n");
            printf("we check the score of each player,\n");
            printf("and the player with the higher score is considered as the winner\n");
            sleep(1);
            menu();
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
//int piv1=0,ind=-1; //global for medium computer

//function to check if we connected four horizontally
int Hcheck(int x,int y,char board[x][y],int row,int move){
    int count=0;
    int score=0;
    for(int i=0;i<x;i++){
        for(int j=0;j<(y-3);j++){
            if(board[i][j]==board[i][j+1]&&board[i][j]==board[row][move]){
                for(int k=j;k<j+3;k++){
                        if(board[i][k]==board[i][k+1]){
                            count++;
                            if(k+2!=y-1 && board[i][k+2]==' '&&board[i+1][k+2]!=' '&& count<3) ai[0]=k+2;
                            else ai[4]=k-2;
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
    int count=0;
    int score=0;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(board[i][j]==board[i+1][j]&&board[i][j]==board[row][move]){
                for(int k=i;k<i+3;k++){
                        if(board[k][j]==board[k+1][j]){
                            count++;
                              if(board[j-1][i]==' '&& count==2){
                            if(ai[1]==-1){
                                ai[1]=i;
                            }else ai[2]=i;
                              }
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
            int scores_sum(int x,int y,char board[x][y],int row,int move){
            int score;
            score=Hcheck(x,y,board,row,move)+Vcheck(x,y,board,row,move)+D1check(x,y,board,row,move)+D2check(x,y,board,row,move);
            return score;
            }
           /* void save(char choice){
                switch(choice):
                    case 'a':
                        FILE *f1;
                f1=fopen("f1.txt","w");
                break;
                    case 'b':
                        FILE *f2;
                        f2=fopen("f2.txt","w");
                        break;
                    case'c':
                        FILE *f3;
                        f3=fopen("f3.txt","w");
                        break;

            }*/
            player top[10];
    //        playertop.score[10]={0};
            void add_score(){
                  FILE *top1;
                  top1=fopen("Top_players.txt","rb");
                  for(int i=0;i<10;i++){
                    fread(&top[i],sizeof(top[i]),1,top1);

                  }
                  fclose(top1);
            }
        void sort_top(char name[100],int score){
            add_score();
            FILE *top1;
           top1=fopen("Top_players.txt","wb");
            int temp_sc;
        char temp_name[100];
        for(int i=0;i<10;i++){
            if((strcmp(top[i].name,name)==0)){
                    if(score>top[i].score){
            top[i].score=score;
            break;
                    }else{
                    break;
                    }
            }
            else if(score>top[i].score&&i==9){
               temp_sc=top[i].score;
            top[i].score=score;
            score=temp_sc;
            strcpy(temp_name,top[i].name);
            strcpy(top[i].name,name);
            strcpy(name,temp_name);

        }
        }
        for(int i=0;i<10;i++){
                for(int j=i+1;j<10;j++){
              if(top[i].score<top[j].score){
               temp_sc=top[i].score;
            top[i].score=top[j].score;
            top[j].score=temp_sc;
            strcpy(temp_name,top[i].name);
            strcpy(top[i].name,top[j].name);
            strcpy(top[j].name,temp_name);
              }
              }

        }
        for(int i=0;i<10;i++){
            fwrite(&top[i],sizeof(top[i]),1,top1);
        }
        fclose(top1);
        }

        void show_scores(){
         FILE *top1;
                  top1=fopen("Top_players.txt","rb");
                  for(int i=0;i<10;i++){
                        fread(&top[i],sizeof(top[i]),1,top1);
                        printf("[%d] %s\t%d",i+1,top[i].name,top[i].score);
                        printf("\n");

        }
        fclose(top1);
        }

