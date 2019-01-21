#include "Dominion.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 1
void prt_decision(struct decision temp){
    printf("Approach : %s\n"
           "People : %d\n"
           "Court : %d\n"
           "Treasury : %d\n",temp.approach,temp.aff_people,temp.aff_court,temp.aff_treasury);
}
void prt_problem(struct problem temp){
    printf("Problem_description : %s\n",temp.problem_description);
    prt_decision(temp.one);
    prt_decision(temp.two);
    printf("Probability : %d\n",temp.probability);

}

/** \brief show_panel make panel with question and commands which is gave.
 *
 * \param problem description char* the address of problem
 * \param commands[][50] char address of array that have command
 * \param size int the number of commands , each command have to be 50 character
 * \param take_command char* the command that user commands
 * \return void
 *
 */
void show_panel(char *description,char commands[][50],int size, char *take_command){
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

    while ( 'T' ) {      /**< work until a suitable number.this number is between 0 and size> */
        scanf("%d",&num); /**< give number of command>*/
        if ( size >= num && 0 < num){ /**< if number is suitable ,accept and copy command in tackecmd> */
            strcpy(take_command,commands[num-1]);
            break;
        }
        printf("It's wrong command\n"); /**< if number is not suitable ,print a message> */
    }

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
 * \param struct problem_node is address for pointing to link_list.link_list produce by this function.
 * \return void.
 *
 */
void prepare_problem( char *addr_choice_file, int siz, struct problem_node *prepared_problem, struct gamer player ){
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


        if (0 != player.remain_probability[counter] ){ /**< if player has probability of this problem (non zero,-1 is acceptable for new player) , it add to link list */

        #if DEBUG

        printf("enter to %d ,%s, %s, %d\n",counter,__FILE__,__func__,__LINE__);
        #endif // DEBUG

        fgets(buff_addr,50,fhin); /**< gets the address of problem */
        char main_addr[100]="problems\\"; /**< the address which has to add address of problem address */

        #if DEBUG
        printf("\n1.buff_addr, %s, %s, %d\n",__FILE__,__func__,__LINE__);
         printf("%s\n",buff_addr);
        #endif // DEBUG

        strcat(main_addr,buff_addr); /**< add main address to problem address */

        #if DEBUG
        printf("2.main_addr, %s, %s, %d\n",__FILE__,__func__,__LINE__);
        printf("%s\n",main_addr);
        #endif // DEBUG

        fhproblem=fopen(main_addr,"r"); /**< don't forget closing file and test it */
        if ( NULL == fhproblem ){ /**< testing for opening file */
            printf("error in opening , %s, %s, %d\n",__FILE__,__func__,__LINE__);
            exit(-1);
        }



        if (0 == first) { /**< make link_list if "first" is zero */
            prepared_problem = (struct problem_node *)malloc(sizeof(struct problem_node)); /**< gets storage in heap and produce address */
            gets_problem_from_file( fhproblem, prepared_problem, player.remain_probability[counter]); /**< copy problem in the storage */
            prepared_problem->next_problem_node = NULL; /**< point next_problem_node to NULL */
            temp_addr = prepared_problem; /**< copy address in temp_addr for adding to link_list */
            first = 1; /**< change 0 to 1 for ending make link_list */

            #if DEBUG
            prt_problem(temp_addr->current_problem);
            printf("%s, %s, %d\n",__FILE__,__func__,__LINE__);
            #endif // DEBUG

        } else { /**< add node to link_list if "first" is non_zero */
            temp_addr->next_problem_node = (struct problem_node *)malloc(sizeof(struct problem_node)); /**< gets storage in heap and copy address in
                                                                                                        * next_problem_node */
            temp_addr = temp_addr->next_problem_node; /**< get address of empty storage in temp_addr */
            temp_addr->next_problem_node = NULL; /**< point next_problem_node to NULL */
            gets_problem_from_file( fhproblem, temp_addr, player.remain_probability[counter]); /**< copy problem in temp_addr */

            #if DEBUG
            prt_problem(temp_addr->current_problem);
            printf("%s, %s, %d\n",__FILE__,__func__,__LINE__);
            #endif // DEBUG
        }

        fclose(fhproblem);
        }

    }

    fclose(fhin);
}





