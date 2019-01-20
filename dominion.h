#ifndef DOMINION_H_INCLUDED
#define DOMINION_H_INCLUDED
typedef struct {    /**< features of decision */
    char approach[200]; /**< approach is a way to solve problem and it's string.limit of it is 200 */
    int aff_court; /**< how much it affect on court */
    int aff_people; /**< how much it affect on people */
    int aff_treasury; /**< how much it affect on people */
} stc_decision; /**< this structure named as stc_decision */

typedef struct {  /**< features of problem.each problem has two approach,one probability and problem description */
    stc_decision one;
    int Probability; /**< probability is probability of happening this problem. */
    char problem_description[200]; /**< description of problem */
    stc_decision two;
} stc_problem; /**< this structure named as stc_problem  */

typedef struct { /**< it's type for saving information of gamer */
    char username[80]; /**< name of gamer.it's string with 80 character*/
    char state; /**< it show whether gamer won or lose */
    int remain_probability[100]; /**< array of probability of problem */
    int court; /**< how much point for court gamer has */
    int people; /**< how much point for people gamer has  */
    int treasury; /**< how much point for treasury gamer has */
} stc_saved_info; /**< this structure named as stc_saved_info */

typedef struct { /**< structure for making node of problem */
    stc_problem current_problem;
    stc_problem *next_problem;
} problem_node;



void show_panel(char*,char(*)[50],int, char*);

#endif // DOMINION_H_INCLUDED
