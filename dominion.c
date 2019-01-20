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
        if ( size >= num && 0 < num){ /**< if number is suitable ,it accept and copy command in tackecmd> */
            strcpy(take_command,commands[num-1]);
            break;
        }
        printf("It's wrong command\n"); /**< if number is not suitable ,print a message> */
    }

}


/*int prepare_question(stc_saved_info data,stc_problem *problem){

}*/





