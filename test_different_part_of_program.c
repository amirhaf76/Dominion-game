#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Dominion.h"

int main()
{
    /**< test of print_problem */
    #if 0
    struct problem test={"i have pain in my leg",
                        {"use pil",1,8,-99},
                        {"sleep",75,5,4},
                        5};
    #endif

    /**< test prepare_problem and prt_link_list */
    #if 0
    //int k;
    struct problem_node *list;
    char str[50]="problems\\CHOICES.txt";
    struct gamer player={"ali",'w',{-1,-1,-1,-1,-1,-1,-1},80,52,100};
    prepare_problem(str,7,&list,player);

    #endif

    /**< test of opening */
    #if 0
    char main_addr[100]="problems\\c1.txt";

    FILE *fhin;
    fhin=fopen(main_addr,"r");
    system("dir");
    if (NULL == fhin){
        printf("error");
    }
    fclose(fhin);
    #endif

    //it solved/** the current problem is in length of main_addr and buff_addr*/

    /**< test of fscanf and fgets,file of test is named test 1 */
    #if 0
    FILE *fhin1;
    FILE *fhin2;

    int a;
    char *str;
    char str1[50];

     fhin1=fopen("test1.txt","r");
     fhin2=fopen("test1.txt","r");
     char buff1[50];
     char buff2[50];

     a=fscanf(fhin1,"%s %s",buff1,str1);
     str=fgets(buff2,50,fhin2);

     //strcat(buff1,buff2);

     printf("%d , %s , %p\n",a,str1,str1);
     printf("fscanf : %s\nfgets : %s\n",buff1,buff2);
     print_all_string_arry(buff1,50,"buff1");
     print_all_string_arry(buff2,50,"buff2");
     print_all_string_arry(str1,50,"str1");

     printf("%lu\n",strlen(buff2));


     fclose(fhin1);
     fclose(fhin2);
     #endif

    /**< test of prt_gamer */
    #if 0
    struct gamer player={"ali",'w',{-1,-1,-1,5,-1,3,2,90,5,80},80,52,100};
    prt_gamer(player);
    #endif


    /**< test of save_game */
    #if 0
    struct gamer player={"mohammd",'w',{-1,-1,-1,5,-1,3,2,90,5,80},80,52,100};
    int i=save_game(player);
    printf("%d\n",i);
    #endif

    /**< test of load_game . note : this test preform
         with test of save_game  */
    #if 0
    struct gamer player_1;
    char username_player_1[]="ahmad";
    int j = load_game(username_player_1,&player_1);
    prt_gamer(player_1);
    #endif // 1

    /**< test show_panel */
    #if 0
    char command[4][50]={"hello","yes","no","why"};
    char str[]="why do you do that ?";
    char answer[50];
    printf("%d %s\n",show_panel(str,command,4,answer),answer);

    #endif // 1

    #if 0
    struct problem test_problem = {"zero problem",{"D1",0,0,0},{"D2",0,0,0},0};
    prt_problem(test_problem);
    #endif // 1

    /**< test of delete_problem_node_form_list */
    #if 0
    int k;
    struct problem_node *list;
    char str[50]="problems\\CHOICES.txt";
    struct gamer player={"ali",'w',{-1,-1,-1,-1,-1,-1,-1},80,52,100};
    prepare_problem(str,7,&list,player);
    printf("here...\n"
           "list = %p\n",list);
    k=delete_problem_node_from_list (list, &list);
    printf("delete : %d\n",k);

    #endif // 1

    #if 0
    struct gamer player={"mohammd",'w',{1,1,1,1,1,1,1,1,1,1},8,5,3};
    int k = 7;
    struct problem_node *list;
    char str[50]="problems\\CHOICES.txt";

    prepare_problem(str,7,&list,player);

    struct problem test_problem = {"what's problem",{"i don't know",3,-5,0},{"solve it",-6,9,9},2};

    struct problem a=play_one_step( &player, &list, &k, 2,&test_problem);

    #endif // 1

    #if 0
    //make random number
    double rand_num;
    time_t system_time;
    int a=7;
    int *size_list=&a;
    time(&system_time); /**< time of system */
    srand( (unsigned)(system_time*3) ); /**< make random number with time of system */
    rand_num = 1.0*rand()/RAND_MAX;


    printf("first rand_num = %lf\n",rand_num);
    rand_num = rand_num * (*size_list); /**< make random number between zero and size of list  */
    /**< rand_num chooses the problem. */
    printf("first rand_num = %lf\n",rand_num);

#endif

    return 0;
}
