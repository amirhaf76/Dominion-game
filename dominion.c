#include "Dominion.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** \brief show_panel make panel with question and commands which is gave
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
 * \return void
 *
 */
void gets_problem_from_file( FILE *handler, struct problem_node *host){
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
}


/** \brief  this function prepare problems for showing.it depends on new game and load game.
 *
 * \param addr_file_choice is address of choice file for getting address of problem.
 * \param siz size number of problems which are exist.for new gamer is different form prior gamer.
 * \param struct problem_node is address for pointing to link_list.link_list produce by this function.
 * \return void.
 *
 */
void prepare_problem( char *addr_choice_file, int siz, struct problem_node *prepared_problem){
    struct problem_node *temp_addr;

    FILE *fhin;
    fhin=fopen(addr_choice_file,"r");

    char buff_addr[50];
    FILE *fhproblem;

    int first=0;
    int counter;
    for (counter = 0; counter < siz; counter++) {
        fgets(buff_addr,50,fhin);
        char main_addr[50]="problems\\";

        strcat(main_addr,buff_addr);

        fhproblem=fopen(main_addr,"r");

        if (0 == first) {
            prepared_problem = (struct problem_node *)malloc(sizeof(struct problem_node));
            gets_problem_from_file( fhproblem, prepared_problem);
            prepared_problem->next_problem_node = NULL;
            temp_addr = prepared_problem;
            first = 1;
        } else {
            temp_addr->next_problem_node = (struct problem_node *)malloc(sizeof(struct problem_node));
            temp_addr = temp_addr->next_problem_node;
            temp_addr->next_problem_node = NULL;
            gets_problem_from_file( fhproblem, temp_addr);
        }
        fclose(fhproblem);
    }

    fclose(fhin);
}





