#include "Dominion.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char approach[200];
    int aff_court;
    int aff_people;
    int aff_treasury;
} decision;

typedef struct {
    decision one;
    int Probability;
    char que[200];
    decision two;
} problem;

typedef struct {
    char username[80];
    char state;
    int remain_probability[100];
    int court;
    int people;
    int treasury;
} saved_information;











/** \brief show_panel make panel with question and commands which is gave
 *
 * \param qus char* the address of question
 * \param cmds[][50] char address of array that have command
 * \param size int the number of commands , each command have to be 50 character
 * \param takecmd char* the command that user commands
 * \return void
 *
 */
void show_panel(char *qus,char cmds[][50],int size, char *takecmd){
    int num;
    int cnt;  /**< counter >*/
    for (cnt=0;cnt<80;++cnt) {   /**< it's for bar section> */
        printf("=");
    }
    printf("\n");  /**< continue make panel >*/
    printf("%s ?\n\n\n",qus); /**< print question */

    for (cnt=0;cnt<size;cnt++){  /**< it's for print commands>*/
        printf("[%d].%s\n",cnt+1,cmds[cnt]); /**< print one more than the number of commands due to starting one> */
    }

    printf("Enter number of command :\n");

    while ( 'T' ) {      /**< work until a suitable number.this number is between 0 and size> */
        scanf("%d",&num); /**< give number of command>*/
        if ( size >= num && 0 < num){ /**< if number is suitable ,it accept and copy command in tackecmd> */
            strcpy(takecmd,cmds[num-1]);
            break;
        }
        printf("It's wrong command\n"); /**< if number is not suitable ,print a message> */
    }

}








