#include "Dominion.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DEBUG 1
void prt_decision(struct decision temp){
    printf("Approach : %s"
           "Effect on People : %d\n"
           "Effect on Court : %d\n"
           "Effect on Treasury : %d\n",temp.approach,temp.aff_people,temp.aff_court,temp.aff_treasury);
}
void prt_problem(struct problem temp){
    printf("Problem_description : %s",temp.problem_description);
    prt_decision(temp.one);
    prt_decision(temp.two);
    printf("Probability : %d\n",temp.probability);

}
void prt_link_list(struct problem_node *link){
    int counter=1;
    while ( NULL != link ){
        printf("--------------------------------------- : %2d\n",counter);
        prt_problem(link->current_problem);
        link = link->next_problem_node;
        counter++;
        printf("_______________________________________ : END\n");
    }
}
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

/** \brief 
 *
 * \param 
 * \param 
 * \return 
 *
 */     
int delete_problem_node_from_list( struct problem_node *delete_problem, struct problem_node **link_list){
    struct problem_node *start; /**< a struct problem_node in stack for checking for first node of link list. */
    struct problem_node *temp_addr; /**< store address of next delete_problem to link previous it. */
    
    start->next_problem_node = *link_list; /**< add the first node of link list to next_problem of start. */
    
    while ( NULL == previous_problem ) { /**< work until end of link list. */
        if ( start->next_problem_node == delete_problem ) { /**< find the delete_problem. */
            
            if ( start->next_problem_node == *link_list ){ /**< if delete_problem was first node , copy new address
                for link list. */
                *link_list = start->next_problem_node->next_problem_node; /**< copy new address for link list. */
            }
            temp_addr = start->next_problem_node->next_problem_node; /**< keep next address of delete_problem. */
            free(start->next_problem_node); /**< free the delete_problem. */
            start->next_problem_node = temp_addr; /**< stick previous and next of delete_problem. */
            return 1; /**< this operation was successful. */
        }
        start = start->next_problem_node; /**< go to next address */
    }
  return 0; /**< it was not successful.!!!!! */
}

/** \brief show_panel make panel with question and commands which is gave.
 *
 * \param problem description char* the address of description of problem
 * \param commands[][50] char address of array that have command
 * \param size int the number of commands , each command have to be 50 character
 * \param take_command char* the command that user commands
 * \return number of command.
 *
 */
int show_panel(char *description,char commands[][50],int size, char *take_command){
    int num;
    int cnt;  /**< counter >*/
    for (cnt=0;cnt<80;++cnt) {   /**< it's for bar section> */
        printf("=");
    }
    printf("\n");  /**< continue make panel >*/
    printf("%s ?\n\n\n",description); /**< print problem description */

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
        printf("It's wrong command\n"); /**< if number is not suitable ,print a message> */
    }
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

    FILE *fhin; /**< file handler of input */
    fhin=fopen(addr_choice_file,"r"); /**< don't forget closing file and test it */
    if ( NULL == fhin ){ /**< testing for opening file */
        printf("error in opening , %s, %s, %d\n",__FILE__,__func__,__LINE__);
        exit(-1);
    }

    char buff_addr[50]; /**< keep address in this buffer for short time */
    FILE *fhproblem; /**< don't forget closing file and test it */

    int first=0; /**< it's for making link_list.after that add node to list */
    int counter; /**< it's for counting of problem */

    for (counter = 0; counter < siz; counter++) {


        if (0 != player.remain_probability[counter] ){ /**< if player has probability of this problem
                                                       (non zero,-1 is acceptable for new player) , it add to link list */

#if DEBUG
            printf("-------------------------------------------- : %2d\n",counter+1);
            printf("enter to %d ,%s, %s, %d\n\n",counter,__FILE__,__func__,__LINE__);
#endif // DEBUG

            fscanf(fhin,"%s",buff_addr); /**< gets the address of problem */
            char main_addr[100]="problems\\"; /**< the address which has to add address of problem address */

#if DEBUG
            printf("1.buff_addr : %s , %s, %s, %d\n",main_addr,__FILE__,__func__,__LINE__);
#endif // DEBUG


            strcat(main_addr,buff_addr); /**< add main address to problem address */



#if DEBUG
            printf("2.main_addr : %s , %s, %s, %d\n\n",main_addr,__FILE__,__func__,__LINE__);
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
                printf("%s, %s, %d\n",__FILE__,__func__,__LINE__);
                printf("____________________________________________ : END\n");
#endif // DEBUG

            } else { /**< add node to link_list if "first" is non_zero */
                temp_addr->next_problem_node = (struct problem_node *)malloc(sizeof(struct problem_node)); /**< gets store in heap and copy address in
                                                                                                        * next_problem_node */
                temp_addr = temp_addr->next_problem_node; /**< get address of empty store in temp_addr */
                temp_addr->next_problem_node = NULL; /**< point next_problem_node to NULL */
                gets_problem_from_file( fhproblem, temp_addr, player.remain_probability[counter]); /**< copy problem in temp_addr */

#if DEBUG
                prt_problem(temp_addr->current_problem);
                printf("%s, %s, %d\n",__FILE__,__func__,__LINE__);
                printf("____________________________________________ : END\n");
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
            printf("check fwrite : %d\n"
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

/** \brief load_game read information
 * of players from saved_data\saves of game of Dominion.ds file.
 *
 * \param username is address to string.it's username of player that has to found.
 * \param if there is gamer with this username in file, copy it to where player point it.
 * \return if find information of gamer return 1,other wise return 0.
 *
 */

int load_game(char *username, struct gamer *player){

    unsigned long check; /**< it's for checking fread function */
    struct gamer found_player; /**< for checking player in file */

    FILE * fh_load_file; /**< a file in order to get information of player */
    fh_load_file = fopen("saved_data\\saves of game of Dominion.ds","rb"); /**< just read a binary file */
    if ( NULL == fh_load_file ) {
        printf("!!! There is not any saved file.\n");
        return -1;
    }

    while ( 1 ) {
        check = fread(&found_player, sizeof(struct gamer), 1, fh_load_file);

#if DEBUG
        printf("found_player : %s\n"
               "username : %s\n",found_player.username,username);
        printf("check fread : %lu\n""end of file : %d\n"
               "%s , %s , %d\n",check,feof(fh_load_file),__FILE__,__func__,__LINE__);
#endif // DEBUG

        if ( 0 == strcmp(username,found_player.username) ) {
            *player = found_player;
#if DEBUG
            printf("player found.\n");
            printf("%d , %s\n%s\n",__LINE__,__func__,__FILE__);
#endif // DEBUG
            fclose(fh_load_file);
            return 1;
        }
        if ( 0 != feof(fh_load_file) ) {
            printf("There is not any save with this username : %s\n",username);
            fclose(fh_load_file);
            return 0;
        }

    }
    fclose(fh_load_file);
};

/** \brief play_one_step function choose a problem form link_list randomly and
 * after decision affect on people , court , treasury and probability.
 *
 * \param
 * \param
 * \return struct_problem as next problem
 *
 */

 struct problem play_one_step( struct gamer *player, struct problem_node **link_list_problem,
                               int *size_list, int choice, struct problem *last_problem){
     double average;
     int counter;
     struct problem picked_problem;
     struct problem_node *picked_node_problem = *link_list_problem
     int rand_num;
     time_t system_time; 
     
     switch (choice){
     case 1:
        player->court += last_problem->one.aff_court;
        player->people += last_problem->one.aff_people;
        player->treasury += last_problem->one.aff_treasury;
     case 2:
        player->court += last_problem->two.aff_court;
        player->people += last_problem->two.aff_people;
        player->treasury += last_problem->two.aff_treasury;
     }
    
    
     if (0 == (player->court ){
        player->state = 'L'; /**< Lose */
     } 
     else if ( 0 == player->people ) {
        player->state = 'L'; /**< lose */
     }
     else if ( 0 == player->treasury ){
        player->state = 'L'; /**< lose */
     }
     average = player->court + player->people + player->treasury ;
     average = average / 3;
     if ( 10 > average ){
        player->state = 'L';
     }
     
     
     
     
     
     
     
     
     time(&system_time); /**< time of system */
     srand( (unsigned)(system_time*3) ); /**< make random number with time of system */
     rand_num = (int) 1.0*rand()/RAND_MAX;
     rand_num = rand_num * size_list; /**< make random number between zero and size of list  */
     
     #if DEBUG
     printf("time = %lu , rand_num = %d , size_list = %d\n",
            system_time, rand_num, size_list);
     printf("%d , %s\n%s\n",__LINE__,__func__,__FILE__);
     #endif // DEBUG
     
     for (counter =0; counter < rand_num; counter++){
        picked_node_problem = picked_node_problem->next_problem_node;
     }
     picked_problem = picked_node_problem->current_problem;
     picked_node_problem->current_problem.probability += -1; /**< mines for elimination */
     if ( 0 == picked_node_problem->current_problem.probability ){
        delete_problem_node_from_list(picked_node_problem,link_list_problem);
     }

 };



