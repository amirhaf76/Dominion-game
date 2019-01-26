#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Dominion.h"

#define DEBUG 0
#define PLAY -1


int main(){
#if 1
    system("color 3e");
    // variable for for loop.
    int counter;
    int pass_main_loop = 0; /**< zero doesn't pass loop, one pass loop */
    int exit_game = 0;


    // prevent error string and int
    char delete_str[20];
    int temp;

    // variable for show_panel and first assignment.
    char *buff_panel= "Welcome to dominion. :)";
    char *buff_commands_panel[10]={ "New game", "Load game", "Save game", "Exit"};
    int num_commands = 4;

    // prepare and preform command
    int digit_command=1;
    char picked_command[50];

    // these are for storing previous panel.
    char *previous_commands_panel[10];




    // it's all commands that can be used.
    char main_commands[][50]={ "New game", "Load game", "Save game", "Menu", "Exit", "continue", "Delete save"};

    // it's for switch case. these are depends on main_commands.
    enum main_num_commands { Ng, Lg, Sg, Mu, Et, Ct, Dg};
    int digit_find=1;

    //variable for player
    struct gamer zero_player ={"Unknown",'w',{-1},50,50,50};
    for ( counter =0; 100 > counter; ++counter){
        zero_player.remain_probability[counter] = -1;
    }
    struct gamer player = zero_player;



    //link list
    struct problem_node *link_list;
    int size_list = number_of_problem();
    struct problem zero_problem = {"zero problem",{"D1",0,0,0},{"D2",0,0,0},-1};
    struct problem last_problem;





    while (1) {

        system("cls");
        printf("================================================================================\n"
               "%20s  ||%10s  ||%10s  ||%10s  ||%6s\n", "USERNAME", "PEOPLE", "COURT", "TREASURY", "STATE");
        printf("%20s  ||%10d  ||%10d  ||%10d  ||%6c\n", player.username, player.people, player.court,
               player.treasury, player.state);

        if ( 0 == pass_main_loop ){
            digit_command = show_panel( buff_panel, num_commands, buff_commands_panel, picked_command);
            digit_find = find_command( picked_command, 7,main_commands);
        } else {
            pass_main_loop = 0;
        }

#if DEBUG
        printf("\n\nDEBUGING GAME @@@@====================================================================================== START\n");
        printf("digit_command = %d\n"
               "digit_find = %d\n",digit_command, digit_find);
#endif

        switch ( digit_find ){
            case Ng:
                system("cls");

                //prepare new player
                player = zero_player;
                size_list = number_of_problem();
                printf("enter a name for making username : ");
                scanf("%s",player.username);

#if DEBUG
                printf("New game:\n");
                prt_gamer(player);
                printf( "LINE = %d , func = %s\n%s\n", __LINE__, __func__, __FILE__);
#endif

                //prepare problem and first problem
                last_problem = zero_problem;
                prepare_problem("problems\\CHOICES.txt",size_list,&link_list,player);
                play_one_step(&player,&link_list,&size_list,-1,&last_problem);

                //panel
                buff_panel = last_problem.problem_description;
                buff_commands_panel[0]=last_problem.one.approach;
                buff_commands_panel[1]=last_problem.two.approach;
                buff_commands_panel[2] = "Menu";
                num_commands = 3;

                //end new game
                break;

            case Lg:
                system("cls");

                // show saves and pick save which is chosen
                // load player and player's elements
                temp = show_saved_gamer();
                temp = load_game_num( temp, &player);
                size_list = number_of_problem();

                //cancel load game
                if ( 0 == temp ){
                    break;
                }
                if ( 'L' == player.state ) {
                    for ( counter=0; counter<size_list; counter++) {
                        player.remain_probability[counter] = 3;
                    }
                    player.court = 50;
                    player.people = 50;
                    player.treasury = 50;
                    player.state = 'w';
                }

                // prepare problem and first problem
                prepare_problem("problems\\CHOICES.txt", size_list, &link_list, player);
                play_one_step( &player, &link_list, &size_list, -1, &last_problem);

                //panel
                buff_panel = last_problem.problem_description;
                buff_commands_panel[0] = last_problem.one.approach;
                buff_commands_panel[1] = last_problem.two.approach;
                buff_commands_panel[2] = "Menu";
                num_commands = 3;

                // end load game
                break;



            case Sg:
                system("cls");
                //store commands of previous panel
                previous_commands_panel[0] = buff_commands_panel[0];
                previous_commands_panel[1] = buff_commands_panel[1];

                // set new commands of new panel
                buff_commands_panel[0]="Yes";
                buff_commands_panel[1]="No";

                // show and get command
                if ( 'L' == player.state ) {
                    digit_command = show_panel( "You lose!!!!!!!!\n"
                                                "Do you want to save ?", 2, buff_commands_panel,
                                                delete_str);
                } else {
                    digit_command = show_panel( "Do you want to save ?", 2, buff_commands_panel,
                                                delete_str);
                }

                // if it was yes , digit_command become 1 and save game
                if ( 1 == digit_command ){
                    temp = save_game(player);
                }

                // checking saving
                if ( 1 == temp ){
                    printf("saving was successful...\n");
                }
                //return back panel
                buff_commands_panel[0] = previous_commands_panel[0];
                buff_commands_panel[1] = previous_commands_panel[1];



                // it's for EXIT !!!!!!!!!!!!!.
                // in Exit ,digit_command change to -9
                if ( 1 == exit_game ){
                    //free
                    system("cls");
                    printf("   Goodbye   \n");
                    return 0;
                }



                //end saving game
                break;

            case Et:
                system("cls");

                //store commands of previous panel
                previous_commands_panel[0] = buff_commands_panel[0];
                previous_commands_panel[1] = buff_commands_panel[1];

                // set new commands of new panel
                buff_commands_panel[0]="Yes";
                buff_commands_panel[1]="No";

                // show and get command
                digit_command = show_panel( "Do you want to exit ? :(", 2,
                                            buff_commands_panel, delete_str);
                if ( 1 == digit_command ) {
                    digit_find = Sg;
                    exit_game = 1;
                    pass_main_loop = 1;
                    break;
                }

                //return back panel
                buff_commands_panel[0] = previous_commands_panel[0];
                buff_commands_panel[1] = previous_commands_panel[1];

                // cancel exit
                break;

            case PLAY:
                // play game
                temp = play_one_step( &player, &link_list, &size_list, digit_command, &last_problem);

                // reload problems with 3 probability
                if ( 0 == temp ) {
                    size_list = number_of_problem();
                    for ( counter=0; counter<size_list; counter++) {
                        player.remain_probability[counter] = 3;
                    }
                    prepare_problem( "problems\\CHOICES.txt", size_list, &link_list, player);
                }

                if ( 'L' == player.state ) {
                    buff_panel = "__________________________MENU__________________________";
                    buff_commands_panel[0] = "New game";
                    buff_commands_panel[1] = "Load game";
                    buff_commands_panel[2] = "Save game";
                    buff_commands_panel[3] = "Exit";
                    num_commands = 4;
                    digit_find = Sg;
                    pass_main_loop = 1;
                    break;

                }

                // change panel
                buff_panel = last_problem.problem_description;
                buff_commands_panel[0] = last_problem.one.approach;
                buff_commands_panel[1] = last_problem.two.approach;
                buff_commands_panel[2] = "Menu";
                num_commands = 3;

                // end play one step
                break;

            case Mu:

                buff_panel = "__________________________MENU__________________________";
                buff_commands_panel[0] = "New game";
                buff_commands_panel[1] = "Load game";
                buff_commands_panel[2] = "Save game";
                buff_commands_panel[3] = "continue";
                buff_commands_panel[4] = "Exit";
                num_commands = 5;

                break;

            case Ct:

                buff_panel = last_problem.problem_description;
                buff_commands_panel[0] = last_problem.one.approach;
                buff_commands_panel[1] = last_problem.two.approach;
                buff_commands_panel[2] = "Menu";
                num_commands = 3;

                break;

            default:
                ;
        }



    }
#endif

#if 0
    printf("%d\n",number_of_problem());
#endif // DEBUG

    return 0;
}
