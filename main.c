#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Dominion.h"
#define DEBUG 1

int main(){
#if 1
    // variable for for loop
    int counter;
    // variable for show_panel
    char *buff_panel= "Welcome to dominion.";
    char *buff_commands_panel[10]={"New game","Load game","no"};
    int num_commands = 3;
    int digit_command;
    char picked_command[50];

    char main_commands[][50]={"New game","Load game"};
    enum main_num_commands {Newgame,Loadgame};

    //variable for player
    struct gamer player;
    struct gamer zero_player ={"zero player",'w',{-1},50,50,50};
    for ( counter =0; 100 > counter; ++counter){
        zero_player.remain_probability[counter] = -1;
    }


    //link list
    struct problem_node *link_list;
    int size_list=7;
    struct problem zero_problem = {"zero problem",{"D1",0,0,0},{"D2",0,0,0},-1};
    struct problem last_problem;

    int digit_find;


    while (1) {
        //system("cls");
        digit_command = show_panel( buff_panel, num_commands, buff_commands_panel, picked_command);
        digit_find = find_command( picked_command, 2,main_commands);

        #if DEBUG
        printf("\n\nDEBUGING GAME @@@@====================================================================================== START\n");
        printf("digit_command = %d\n"
               "digit_find = %d\n",digit_command, digit_find);
        #endif
        switch ( digit_find ){
        case Newgame:
            //prepare new player
            player =zero_player;
            printf("enter a name for making username : ");
            scanf("%s",player.username);

            #if DEBUG
            printf("New game:\n");
            prt_gamer(player);
            #endif
            //prepare problem and first problem
            last_problem = zero_problem;
            prepare_problem("problems\\CHOICES.txt",size_list,&link_list,player);
            play_one_step(&player,&link_list,&size_list,-1,&last_problem);

            prt_problem(last_problem);

            //panel
            buff_panel = last_problem.problem_description;
            buff_commands_panel[0]=last_problem.one.approach;
            buff_commands_panel[1]=last_problem.two.approach;
            num_commands = 2;
        case Loadgame:
            ;
        }



    }
#endif

#if 0
struct gamer player={"mohammd",'w',{1,1,1,1,1,1,1,1,1,1},8,5,3};
    int k = 7;
    struct problem_node *list;
    char str[50]="problems\\CHOICES.txt";

    prepare_problem(str,7,&list,player);

    struct problem test_problem = {"what's problem",{"i don't know",3,-5,0},{"solve it",-6,9,9},2};

    struct problem a=play_one_step( &player, &list, &k, 2,&test_problem);

#endif


    return 0;
}
