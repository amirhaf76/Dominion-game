#ifndef DOMINION_H_INCLUDED
#define DOMINION_H_INCLUDED
struct decision {    /**< features of decision */
    char approach[200]; /**< approach is a way to solve problem and it's string.limit of it is 200 */
    int aff_court; /**< how much it affect on court */
    int aff_people; /**< how much it affect on people */
    int aff_treasury; /**< how much it affect on people */
};

struct problem{  /**< features of problem.each problem has two approach,one probability and problem description */
    char problem_description[200]; /**< description of problem */
    struct decision one;
    struct decision two;
    int probability; /**< probability is probability of happening this problem. */
};

struct gamer { /**< it's type for saving information of gamer */
    char username[80]; /**< name of gamer.it's string with 80 character*/
    char state; /**< it show whether gamer won or lose */
    int remain_probability[100]; /**< array of probability of problem */
    int court; /**< how much point for court gamer has */
    int people; /**< how much point for people gamer has  */
    int treasury; /**< how much point for treasury gamer has */
};

struct problem_node { /**< structure for making node of problem */
    struct problem current_problem;
    struct problem_node *next_problem_node;
};


void prt_decision( struct decision);
void prt_problem( struct problem);
void prt_link_list( struct problem_node *);
void prt_gamer( struct gamer);
void print_all_string_array(char *, int, char *);
int show_panel( char *,char (*)[50], int, char *);
void prepare_problem( char *, int, struct problem_node **, struct gamer);
unsigned long save_game( struct gamer);
int load_game( char *, struct gamer *);
#endif // DOMINION_H_INCLUDED
