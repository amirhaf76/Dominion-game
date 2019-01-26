#include "Dominion.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DEBUG 0



/** \brief prt_decision function print struct decision
 *
 * \param temp : gets struct decision
 * \return void
 *
 */
void prt_decision(struct decision temp){
    printf("Approach : %s\n"
           "Effect on Court : %d\n"
           "Effect on People : %d\n"
           "Effect on Treasury : %d\n",temp.approach,temp.aff_court,temp.aff_people,temp.aff_treasury);
}






/** \brief prt_problem function print struct problem.
 *
 * \param temp : gets struct problem
 * \return void
 *
 */
void prt_problem(struct problem temp){
    printf("Problem_description : %s\n",temp.problem_description);
    prt_decision(temp.one);
    prt_decision(temp.two);
    printf("Probability : %d\n",temp.probability);

}






/** \brief prt_link_list get link list and print it.
 *
 * \param link : gets address of link_list. note : link_list has to be struct problem.
 * \return void
 */
void prt_link_list(struct problem_node *link){
    int counter=1;
    printf("link list :\n");
    while ( NULL != link ){
        printf("--------------------------------------- : %2d\n",counter);
        prt_problem(link->current_problem);
        link = link->next_problem_node;
        counter++;
        printf("_______________________________________ : END\n");
    }
}





/** \brief prt_gamer function get struct gamer and print it.
 *
 * \param player
 * \return void
 *
 */

void prt_gamer(struct gamer player){
    int counter;
    printf("Username : %s ------------------------------------------------------\n",player.username);
    printf("State : %c\n"
           "Court : %d\n"
           "People : %d\n"
           "Treasury : %d\n", player.state, player.court, player.people, player.treasury);
    printf("Probability : ");
    for ( counter = 0 ; counter < 100 ; counter++){
        printf("[%d] = %d ,",counter,player.remain_probability[counter]);
    }
    printf("\b\b  \n___________________________________________________ END\n");
}





/** \brief print all of elements of string array.also show the '\0' and '\n'
 *
 * \param arr is address of string array for print elements of it.
 * \param size is size of string array.
 * \param name is name of string array for showing in console
 * \return void
 *
 */
void print_all_string_array( char *arry, int size,char *name){
    int counter;
    printf("-----------------------------------------------------------\n%s:\n",name);
    for(counter=0; counter<size ; counter++){
        char character;
        character =arry[counter];
        if ('\0' == character ){ /**< if character is '\0' , show the it as |\0| */
            printf("|\\0|-");
        } else if ( '\r' == character){
            printf("|\\r|-");
        } else if ( '\n' == character ) { /**< if character is '\0' , show the it as |\0| */
            printf("|\\n|-");
        } else {
            printf("|%c|-",arry[counter]);
        }
    }
    printf("\b \n----------------------------------------------------------\n");
}










int delete_problem_node_from_list( struct problem_node *delete_problem, struct problem_node **link_list){
    struct problem_node start; /**< a struct problem_node is in stack for checking for first node of link list. */
    struct problem_node *temp_addr; /**< store address of next delete_problem to link previous it. */
    struct problem_node *after_delete_problem;
#if DEBUG
    printf("Debug delete_problem_node_from_list =============================================================================\n");
    printf("%d , %s\n%s\n\n",__LINE__,__func__,__FILE__);
    int number_delete_problem = 1;
#endif // DEBUG

    start.next_problem_node = *link_list; /**< add the first node of link list to next_problem of start. */
    temp_addr = &start;

#if DEBUG
    printf("link_list at first :-------------------------------------------------------------------\n");
    prt_link_list(temp_addr->next_problem_node);
    printf("%d , %s\n%s\n\n",__LINE__,__func__,__FILE__);
#endif // DEBUG

    while ( NULL != temp_addr ) { /**< work until end of link list. */

        if ( temp_addr->next_problem_node == delete_problem ) { /**< find the delete_problem. */

            if ( temp_addr->next_problem_node == *link_list ){ /**< if delete_problem was first node , copy new address
                for link list. */

#if DEBUG
                printf("delete_problem was first problem node in list.!!!!!!!!!!!!!!!!!!!!!\n");
                printf("%d , %s\n%s\n\n",__LINE__,__func__,__FILE__);
#endif // DEBUG

                *link_list = temp_addr->next_problem_node->next_problem_node; /**< copy new address for link list. */
            }
            after_delete_problem = temp_addr->next_problem_node->next_problem_node; /**< keep next address of delete_problem. */
            free(temp_addr->next_problem_node); /**< free the delete_problem. */
            temp_addr->next_problem_node = after_delete_problem; /**< stick previous and next of delete_problem. */

#if DEBUG
            printf("link_list at The END :---------------------------------------------------------------\n");
            prt_link_list(temp_addr->next_problem_node);
            printf("%d , %s\n%s\n",__LINE__,__func__,__FILE__);
            printf("____________________________________________________________________________ END DEBUGING\n"
                   "number of delete_problem = %d\n\n",number_delete_problem);
#endif // DEBUG

            return 1; /**< this operation was successful. */
        }

#if DEBUG
        number_delete_problem++;
#endif // DEBUG

        temp_addr = temp_addr->next_problem_node; /**< go to next address */
    }
#if DEBUG
    printf("link_list at The END :---------------------------------------------------------\n");
    prt_link_list(temp_addr);
    printf("%d , %s\n%s\n",__LINE__,__func__,__FILE__);
    printf("____________________________________________________________________________ END DEBUGING\n\n");
#endif // DEBUG
    return 0; /**< it was not successful.!!!!! */
}










/** \brief show_panel make panel with question and commands which is gave.
 *
 * \param problem description char* the address of description of problem
 * \param
 * \param size int the number of commands , each command have to be 50 character
 * \param take_command char* the command that user commands
 * \return number of command.
 *
 */
int show_panel(char *description,int size,char *commands[size], char *take_command){
    // prevent error because of characters
    char delete_str[20];

    int num;
    int cnt;  /**< counter >*/

    printf("================================================================================\n"); /**< it's for bar section> */

    printf("\n");  /**< continue make panel >*/
    printf("%s\n\n\n",description); /**< print problem description */

    for (cnt=0;cnt<size;cnt++){  /**< it's for print commands>*/
        printf("[%d].%s\n",cnt+1,commands[cnt]); /**< print one more than the number of commands due to starting one> */
    }

    printf("Enter number of command :\n");

    while ( 1 ) {      /**< work until a suitable number.this number is between 0 and size> */
        scanf("%d",&num); /**< give number of command>*/

        if ( size >= num && 0 < num){ /**< if number is suitable ,accept and copy command in tackecmd> */
            strcpy(take_command,commands[num-1]);
            break;
        }
        gets(delete_str);
        printf("It's wrong command\n"); /**< if number is not suitable ,print a message> */
    }
#if DEBUG
    printf("\n\nDEBUGING show_panel ================================================== START\n"
           "number of command = %d\n"
           "commands = %s\n"
           "DEBUGING show_panel ================================================== END\n",num,take_command);
#endif // DEBUG
    return num;
}









/** \brief gets_problem_from_file copy a problem in a struct problem_node.
 *
 * \param gets a handler to get file.
 * \param gets address of struct problem_node to save information form file to struct problem_node.
 * \param player_probability is for checking condition.
 * \return void
 *
 */

void gets_problem_from_file( FILE *handler, struct problem_node *host,int player_probability){
    char str[200]; /**< it's for passing extra character for reaching the description */
    fgets(host->current_problem.problem_description, 200, handler); /**< gets description from file handler */
    fgets(host->current_problem.one.approach, 200, handler); /**< gets approach of first decision from file handler */
    fscanf(handler, "%d%d%d", &host->current_problem.one.aff_people, /**< these three line ,gets people, court and treasury of first decision. */
           &host->current_problem.one.aff_court,
           &host->current_problem.one.aff_treasury);
    fgets(str,200,handler);
    fgets(host->current_problem.two.approach, 200, handler); /**< gets approach of second decision from file handler */
    fscanf(handler, "%d%d%d", &host->current_problem.two.aff_people, /**< these three line ,gets people, court and treasury of second decision. */
           &host->current_problem.two.aff_court,
           &host->current_problem.two.aff_treasury);
    if ( -1 == player_probability ){ /**< -1 is for new player.new player has 3 probability */
        host->current_problem.probability = 3;
    } else { /**< other amounts is just 0 , 1 , 2 and 3 */
        host->current_problem.probability = player_probability;
    }
}







/** \brief  this function prepare problems for showing.it depends on new game and load game.
 *
 * \param addr_file_choice is address of choice file for getting address of problem.
 * \param siz size number of problems which are exist.for new gamer is different form prior gamer.
 * \param struct problem_node is address for store address which keep address of pointer to link_list.link_list produce by this function.
 * \param player give probability of problem for adding to link list.
 * \return void.
 *
 */
void prepare_problem( char *addr_choice_file, int siz, struct problem_node **prepared_problem, struct gamer player ){
    struct problem_node *temp_addr=NULL; /**< temp_addr is just for keep address of prepared_problem for short time */

#if DEBUG
    printf("\n\nDEBUGING prepare_problem =======================================================================\n\n");
#endif // DEBUG

    FILE *fhin; /**< file handler of input */
    fhin=fopen(addr_choice_file,"r"); /**< don't forget closing file and test it */
    if ( NULL == fhin ){ /**< testing for opening file */
        printf("error in opening , %s, %s, %d\n",__FILE__,__func__,__LINE__);
        exit(-1);
    }

    char buff_addr[50]; /**< keep address in this buffer for short time */
    FILE *fhproblem; /**< don't forget closing file and test it */

    int first=0; /**< it's for making link_list.after that add node to list */
    int counter=0; /**< it's for counting of problem */

    for (counter = 0; counter < siz; counter++) {


        if (0 != player.remain_probability[counter] ){ /**< if player has probability of this problem
                                                       (non zero,-1 is acceptable for new player) , it add to link list */

#if DEBUG
            printf("-------------------------------------------- : %2d\n",counter+1);
            printf("enter to %d\n",counter);
            printf("%d , %s\n%s\n\n",__LINE__,__func__,__FILE__);
#endif // DEBUG

            fscanf(fhin,"%s",buff_addr); /**< gets the address of problem */
            char main_addr[100]="problems\\"; /**< the address which has to add address of problem address */

#if DEBUG
            printf("1.buff_addr : %s\n",buff_addr);
            printf("%d , %s\n%s\n\n",__LINE__,__func__,__FILE__);
#endif // DEBUG


            strcat(main_addr,buff_addr); /**< add main address to problem address */



#if DEBUG
            printf("2.main_addr : %s\n",main_addr);
            printf("%d , %s\n%s\n\n",__LINE__,__func__,__FILE__);
#endif // DEBUG

            fhproblem=fopen(main_addr,"r"); /**< don't forget closing file and test it */
            if ( NULL == fhproblem ){ /**< testing for opening file */
                printf("error in opening , %s, %s, %d\n",__FILE__,__func__,__LINE__);
                exit(-1);
            }



            if (0 == first) { /**< make link_list if "first" is zero */
                *prepared_problem = (struct problem_node *)malloc(sizeof(struct problem_node)); /**< gets store in heap and produce address */
                gets_problem_from_file( fhproblem, *prepared_problem, player.remain_probability[counter]); /**< copy problem in the store */
                (*prepared_problem)->next_problem_node = NULL; /**< point next_problem_node to NULL */
                temp_addr = *prepared_problem; /**< copy address in temp_addr for adding to link_list */
                first = 1; /**< change 0 to 1 for ending make link_list */

#if DEBUG
                prt_problem(temp_addr->current_problem);
                printf("%d , %s\n%s\n\n",__LINE__,__func__,__FILE__);
                printf("____________________________________________ : END\n\n");
#endif // DEBUG

            } else { /**< add node to link_list if "first" is non_zero */
                temp_addr->next_problem_node = (struct problem_node *)malloc(sizeof(struct problem_node)); /**< gets store in heap and copy address in
                                                                                                        * next_problem_node */
                temp_addr = temp_addr->next_problem_node; /**< get address of empty store in temp_addr */
                temp_addr->next_problem_node = NULL; /**< point next_problem_node to NULL */
                gets_problem_from_file( fhproblem, temp_addr, player.remain_probability[counter]); /**< copy problem in temp_addr */

#if DEBUG
                prt_problem(temp_addr->current_problem);
                printf("%d , %s\n%s\n\n",__LINE__,__func__,__FILE__);
                printf("____________________________________________ : END\n\n");
#endif // DEBUG
            }

            fclose(fhproblem);
        }

    }

    fclose(fhin);
}







/** \brief save_game save information of gamer in file with "saves of game of Dominion.ds" format.
 * if the gamer was in file , new data replace it.
 *
 * \param struct game is input and it save in file.
 * \return if successful in saving , return non zero.
 *
 */
unsigned long save_game( struct gamer player){
    unsigned long check; /**< checking saving operation */
    struct gamer finding_gamer; /**< checking for existence of player in file */

    FILE *fh_saves_file; /**< a file in order to save player*/
    fh_saves_file=fopen("saved_data\\saves of game of Dominion.ds","rb+"); /**< open binary file for reading and writting */

    if ( NULL == fh_saves_file ) { /**< if there isn't any file in "saves of game of Dominion.ds" format , make now one  */

        fh_saves_file=fopen("saved_data\\saves of game of Dominion.ds","wb+");

        if ( NULL == fh_saves_file ) { /**< checking for making and opening file */
            printf("error in opening , %s ,%s , %d",__FILE__,__func__,__LINE__);
            exit(-1);
        }
    }

    while ( 1 ){ /**< this loop is for searching player in file. */
        check = fread(&finding_gamer,sizeof(struct gamer),1,fh_saves_file); /**< read one gamer form file and store in
                                                                                 finding_gamer*/
#if DEBUG
        printf("finding_gamer : %s\n"
               "player : %s\n",finding_gamer.username,player.username);
        printf("check fread : %lu\n""end of file : %d\n"
               "%s , %s , %d\n",check,feof(fh_saves_file),__FILE__,__func__,__LINE__);
#endif // DEBUG

        if ( 0 == strcmp(player.username,finding_gamer.username) ){  /**< if find player in file , new data replace it  */

            fseek(fh_saves_file,-1*sizeof(struct gamer),
                  SEEK_CUR);  /**< come back size of gamer bytes ,because it pass the detected data */
            check = fwrite(&player,sizeof(struct gamer),1,fh_saves_file); /**< new data replace old data */

#if DEBUG
            printf("player found.\n");
            printf("check fwrite : %lu\n"
                   "%s , %s , %d\n",check,__FILE__,__func__,__LINE__);
#endif //DEBUG

            break;
        }
        if ( 0 != feof(fh_saves_file) ){  /**< if is not found , write new data in end of the file. */
            fseek(fh_saves_file,0,SEEK_END);
            check = fwrite(&player,sizeof(struct gamer),1,fh_saves_file);/**< write new data in end of the file */

#if DEBUG
            printf("player not found.\n");
            printf("check fwrite : %lu\n"
                   "%s , %s , %d\n",check,__FILE__,__func__,__LINE__);
#endif // DEBUG

            break;
        }
    }

    fclose(fh_saves_file); /**< close file */
    return check; /**< return numbers of the bytes which write in file */
}








int play_one_step( struct gamer *player, struct problem_node **link_list_problem,
                   int *size_list, int choice, struct problem *last_problem){
    double average; /**< test for win or lose. */
    int counter;

    //struct problem picked_problem; /**< it's next problem. */
    struct problem_node *picked_node_problem = *link_list_problem; /**< it's for finding node. */
    struct problem zero_problem = {"zero problem",{"D1",0,0,0},{"D2",0,0,0},-1}; /**< it's for starting game or
      ending of all problems. -1 is for detect zero problem. */

    double rand_num; /**< make random number between zero and size_list. */
    time_t system_time; /**< store time of system.it use in make random number. */

#if DEBUG
    printf("\n\nDEBUGING play_one_step ================================================================\n\n");
    printf("before effect ************************************ START\n");
    printf("last_problem :\n");
    prt_problem(*last_problem);
    printf("\nchoice = %d\n",choice);
    prt_gamer(*player);
    printf("LINE :%d , func : %s\n%s\n"
           "before effect ************************************ END\n\n",__LINE__,__func__,__FILE__);
#endif
    //play game.affect on elements.
    switch (choice){ /**< depends on the choice ,one of two approaches which are for last problem , affects on elements of player. */

        case 1: /**< effect of first approach on elements of player. */
            player->court += last_problem->one.aff_court;
            player->people += last_problem->one.aff_people;
            player->treasury += last_problem->one.aff_treasury;
            break;

        case 2: /**< effect of first approach on elements of player. */
            player->court += last_problem->two.aff_court;
            player->people += last_problem->two.aff_people;
            player->treasury += last_problem->two.aff_treasury;
            break;
        default:
            printf("error in choice.\n");
    }
#if DEBUG
    printf("after effect ************************************ START\n");
    prt_gamer(*player);
    printf("LINE :%d , func : %s\n%s\n\n"
           "after effect ************************************ END\n\n",__LINE__,__func__,__FILE__);
#endif

    //check lose or win
    if ( 0 >= player->court ) { /**< check if player is loser or winner */
        player->state = 'L'; /**< Lose */
    }
    else if ( 0 >= player->people ) {
        player->state = 'L'; /**< lose */
    }
    else if ( 0 >= player->treasury ){
        player->state = 'L'; /**< lose */
    }
    average = player->court + player->people + player->treasury ; /**< calculate average for checking if player is loser or winner */
    average = average / 3;
    if ( 10 > average ){
        player->state = 'L';
    }
    /**< player is winner until he can play */
    /**< if state of player is 'L', he can't continue game. */


    if ( 100 < player->court ) {
        player->court = 100;
    }
    if ( 100 < player->people ) {
        player->people = 100;
    }
    if ( 100 < player->treasury ){
        player->treasury = 100;
    }


#if DEBUG
    printf("after evaluation ************************************ START\n");
    prt_gamer(*player);
    printf("LINE :%d , func : %s\n%s\n\n"
           "after evaluation ************************************ END\n\n",__LINE__,__func__,__FILE__);
#endif



    if ( 0 < size_list ){ /**< if there is any problem , chooses one of them. */

        //make random number
        time(&system_time); /**< time of system */
        rand_num = system_time % (*size_list);

#if DEBUG
        srand( (unsigned)(system_time*3) ); /**< make random number with time of system */
     rand_num = 1.0*rand()/RAND_MAX;

     #if DEBUG
     printf("first rand_num = %lf\n",rand_num);
     #endif
     rand_num = rand_num * (*size_list); /**< make random number between zero and size of list  */
                                         /**< rand_num chooses the problem. */
#endif

#if DEBUG
        printf("CHECKING RANDOM NUMBER ************************************ START\n"
               "time = %lu , rand_num = %lf , size_list = %d\n",
               system_time, rand_num, *size_list);
        printf("LINE :%d , func : %s\n%s\n",__LINE__,__func__,__FILE__);
        printf("CHECKING RANDOM NUMBER ************************************END\n\n");
#endif // DEBUG

        // find random number
        for (counter =0; counter < rand_num; counter++){ /**< it find problem that is chosen. */
            picked_node_problem = picked_node_problem->next_problem_node;
        }
#if DEBUG
        printf("CHECKING ELIMINATION ************************************ START\n");
        prt_problem(picked_node_problem->current_problem);
        printf("LINE :%d , func : %s\n%s\n",__LINE__,__func__,__FILE__);
#endif

        picked_node_problem->current_problem.probability += -1; /**< mines for elimination */
        *last_problem = picked_node_problem->current_problem;

        // eliminate problem if probability == 0
        if ( 0 == picked_node_problem->current_problem.probability ){
            delete_problem_node_from_list(picked_node_problem,link_list_problem);
            (*size_list)--;
#if DEBUG
            printf("the problem is deleted because its probability was zero.\n");
            printf("LINE :%d , func : %s\n%s\n\n",__LINE__,__func__,__FILE__);
#endif
        }

#if DEBUG
        prt_link_list(*link_list_problem);
        printf("LINE :%d , func : %s\n%s\n\n",__LINE__,__func__,__FILE__);
        printf("last_problem :\n");
        prt_problem(*last_problem);
        printf("CHECKING ELIMINATION ************************************ END\n\n");
#endif

        return 1;
    } else {
        *last_problem = zero_problem;
        return 0;
    }

};





int find_command(char *f_command, int size_main, char commands[][50]){
    int counter;
    int digit_cmd;
    for ( counter = 0; counter < size_main; ++counter) {
        digit_cmd = strcmp( f_command, commands[counter]);

#if DEBUG
        printf("\n\nDUBUGING find_command============================ START \n");
        printf("picked command = %s\n"
               "main_command [%d] = %s\n", f_command, counter, commands[counter]);
#endif // DEBUG
        if ( 0 == digit_cmd ){

#if DEBUG
            printf("return = %d\n",counter);
            printf("\n\nDUBUGING find_command============================ END\n\n");
#endif // DEBUG
            return counter;
        }

    }
#if DEBUG
    printf("return = -1\n"
           "there is not any command like picked command.\n");
    printf("\n\nDUBUGING find_command============================ END\n\n");
#endif // DEBUG
    return -1;
}







int show_saved_gamer( void){
    //store for short time
    struct gamer player;

    //check for preform correctly
    unsigned long check;

    //open file
    FILE *fh_saved_file;
    fh_saved_file = fopen("saved_data\\saves of game of Dominion.ds","rb+");
    if ( NULL == fh_saved_file ){
        printf("error in opening. Maybe there is not file with saves of game of Dominion.ds\n"
               "LINE = %d , func = %s\n%s\n",__LINE__,__func__,__FILE__);
    }

    //read saves form file
    int counter = 1;
    printf("%23s |%10s |%10s |%10s |%6s\n","saves", "PEOPLE", "COURT", "TREASURY","STATE");
    while ( 0 == feof(fh_saved_file) ){
        check = fread ( &player, sizeof(struct gamer), 1, fh_saved_file);
#if DEBUG
        printf("check fread = %d\n"
               "LINE = %d , func = %s\n%s\n", check, __LINE__, __func__, __FILE__);
#endif // DEBUG
        if ( 0 != check ){
            printf("%2d.%20s :%10d ,%10d ,%10d ,%6c\n", counter, player.username, player.people,
                   player.court, player.treasury, player.state);
        }
        counter++;
    }

    // close file for safety
    fclose(fh_saved_file);

    //calculate number of saves. counter mines -2.
    // one for EOF and one for adding in loop
    counter += -2;

#if DEBUG
    printf("counter = %d\n"
           "LINE = %d , func = %s\n%s\n", counter,
            __LINE__, __func__, __FILE__);
#endif // 1

    // return number of saves
    printf("[enter 0]--> EXIT\n"
           "Enter number of save :\n");
    return counter;

}












int load_game_num ( int num_save, struct gamer *player){
    // for getting number of save
    // assign -1 for entering to loop
    int num= -1;

    // prevent error because of characters
    char delete_str[20];

    // get number of save
    while ( ( num > num_save) || ( num < 0) ){
        scanf("%d", &num);
        if ( ( num > num_save) || (num < 0) ){
            gets(delete_str);
            printf("it was wrong number.\n");
        }
    }

    //cancel load save
    if ( 0 == num ){
        return 0;
    }

    //check for preform correctly
    unsigned long check;

    //open file
    FILE *fh_saved_file;
    fh_saved_file = fopen("saved_data\\saves of game of Dominion.ds","rb+");
    if ( NULL == fh_saved_file ){
        printf("error in opening. Maybe there is not file with saves of game of Dominion.ds\n"
               "LINE = %d , func = %s\n%s\n",__LINE__,__func__,__FILE__);
    }

    //find gamer
    fseek( fh_saved_file, (num-1)*sizeof(struct gamer), SEEK_SET);
    check = fread ( player, sizeof(struct gamer), 1, fh_saved_file);

#if DEBUG
    prt_gamer(*player);
    printf("check fread = %lu\n"
           "LINE = %d , func = %s\n%s\n", check, __LINE__, __func__, __FILE__);
#endif // DEBUG

    //close the file for safety
    fclose(fh_saved_file);

    //return player
    return 1;
};








int number_of_problem(void){
    // counting number
    int counter=0;



    // for counting line
    char delete_str[10];
    // open file
    FILE *fhin;
    fhin = fopen("problems\\CHOICES.txt","r");
    if ( NULL == fhin ){
        printf("error in opening.\n"
               "LINE = %d , func = %s\n%s\n", __LINE__, __func__, __FILE__);
    }

    while ( 0 == feof(fhin) ) {
        fgets(delete_str, 10, fhin);
#if DEBUG
        print_all_string_array(delete_str,10,"delete_str");
#endif
        counter++;
    }

    fclose(fhin);

    return counter;

}





