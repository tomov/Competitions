/*
 ************************************************************************
 *           Allocate players in a Swiss system chess tournament
 *
 * Environment and requirements
 *	1. In one round of the tournament, two parties are played. Thus 
 *         a player can score 4/2, 3/2, 2/2, 1/2, and 0/2 points
 *         (that is, from 2 victories to 2 defeats)
 *      2. Any two players may have at most _one_ meeting at a chess
 *         board through the entire tournament
 *	3. The problem is to schedule the next round of the tournament,
 *	   given the results of the previous rounds.
 *	   That is, the program should tell who is to play with who,
 *	   matching partners with as close accumulated scores as possible
 *	   (while satisfying requirement 2)
 *
 * The code can save the following data
 *      N_players, Has_played matrix, Scores array
 * into a temporary file, thus allowing restart of the program
 * from a saved history.
 *
 * Call the program
 *      tour                    - "cold" start
 *      tour work_file_name     - resuming the interrupted work
 *
 * $Id$
 *
 ************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

/*
 *=======================================================================
 *        Some screen control routines for a VT-100-type terminal
 */

static void clear_screen(void)
{
  fprintf(stderr,"\033[H\033[J");
}

static void cursor(const int row, const int col)
{
  fprintf(stderr,"\033[%0d;%0dH",row,col);
}

static void message(const char * mess)
{
  cursor(18,20);
  fprintf(stderr,"%s\n\n\tPress CR to continue...",mess);
  getchar();
  cursor(18,0); fprintf(stderr,"\033[J");  /* Clear to end-of-screen       */
}


/*
 *=======================================================================
 *                          Global parameters
 */

#define Max_players 26
int     N_players;              /* No of players, should be an even no  */
char Has_played[Max_players+1][Max_players+1];
                                /* Has_played[i,j]=1 when i,j have had a*/
                                /* game                                 */
int Scores[Max_players+1];      /* Scores[i] is the i-th player score   */
                                /* times two                            */
                                /* Note, indexing begins at 1 rather    */
                                /* than 0 !!!                           */
int Sorted_indices[Max_players+1];
                                /* After 'sort()' was called, the follo-*/
                                /* ing assertion holds:			*/
                                /* for all i>j within 1..N_players      */
                                /* Scores[Sorted_indices[i]] >=         */
                                /* Scores[Sorted_indices[j]]            */
char Work_file_name[50];


/*
 *=======================================================================
 *                  Entering scores for a finished round
 */
static void input(void)
{
  register int i;
  int met[Max_players+1];        /* met[i] is a player participant #i   */
                                 /* has met in this round		*/

  clear_screen();
  fprintf(stderr,"\n\n\n\t\t\t\033[4mEnter Scores for a round\033[m");
  cursor(16,0);
  fprintf(stderr,"\tEnter the number of points gained by the player #1\n");
  fprintf(stderr,"\t   i.e. one of the following: 2, 15, 1, 05, 0");

  cursor(7,0);
  fprintf(stderr,"Player#1");
  for(i=1; i<=N_players; ++i)
     fprintf(stderr,"%3d",i);
  fprintf(stderr,"\nPlayer#2\nScore");
  memset(met,0,sizeof(met));

  for(i=1; i<=N_players; i++)
     {
       int j;                           /* another player's index      */

       if((j=met[i]) == 0)              /* Player #i met with nobody yet*/
       {
         for(;;)                        /* Enter a player the i-th	*/
         {                              /* player has just had a game with*/
           cursor(8,3*i+8);
           scanf("%d",&j); getchar();
           if( j <= N_players && met[j] == 0 && !Has_played[i][j] )
             break;
           message("These players already had a game with each other!");
         }
         for(;;)                        /* Enter the no. of points gained*/
         {                              /* by the i-th in the game i-j  */
           char res[4];
           static const struct ScoreDistrib {
           	const char * symbol;
           	int player_1_score, player_2_score; }
            score_distribution [] =
           { {"2\n",4,0},		/* Player #1 has won both games */
             {"15\n",3,1},		/* One victory and one tie	*/
             {"1\n",2,2}, {"05\n",1,3}, {"0\n",0,4}, {0,0,0}};
           register const struct ScoreDistrib *sp;
           cursor(9,3*i+7); fprintf(stderr,"   \b\b\b");
           fgets(res,sizeof(res),stdin);
           for(sp=score_distribution; sp->symbol != (char *)0; sp++)
             if( strcmp(sp->symbol,res) == 0 )
             {
               Scores[i] += sp->player_1_score;
               Scores[j] += sp->player_2_score;
               break;
             }
           if( sp->symbol != (char *)0 )
             break;
           message("Illegal specification, use '2','15','1','05','0'");
         }
         Has_played[i][j] = 1; Has_played[j][i] = 1;
         met[i] = j;  met[j] = i;
       }
       cursor(8,3*i+8);
       fprintf(stderr,"%-2d",j);
  }
  message("");
}

/*
 *=======================================================================
 *                         Sorting scores
 */
                        /* Comparison function for sorting 'Scores'    */
			/* in descending order                          */
static int compar(const int *i, const int *j)
{
  return Scores[*j] - Scores[*i];
}


static void sort(void)   /* Sorting Scores arranging the indices to	*/
{                        /* sorted scores in 'Sorted_indices'		*/
  register int i;
  for(i=1; i<=N_players; i++)           /* Unsorted set of indices      */
     Sorted_indices[i] = i;
  qsort(&(Sorted_indices[1]),N_players,sizeof(Sorted_indices[1]),compar);
}

/*
 *=======================================================================
 *                Perform an allocation for the next game
 */

			/* Find out how good an allocation allo is	*/
			/* allo[i] is a party for player #i       	*/
static int find_measure(const int allo[])
{
  register int i;               /* The closer scores of the parties,    */
  register int measure =0;      /* the less is the measure, the         */
  for(i=1; i<=N_players; ++i)   /* better is allocation                 */
     measure += abs(Scores[i]-Scores[allo[i]]);
  return measure;
}

			 /* Try some allocation and select the best      */
static void try_allocate(int best_allo[])
{
  int level;                            /* Level of search 1..N_players/2*/
  int si[Max_players/2+1];              /* For stack simulation         */
  int sj[Max_players/2+1];
  int allo[Max_players+1];              /* i-th player will have a game */
                                        /* with the allo[i]-th player   */
  int best_measure = 32767;             /* Measure for the best allo    */

  int i,j;
  int status;                           /* Automaton status             */

#define N_retries 5                     /* No of attempts to find best alloc */
  int retry_no;

  memset(allo,0,sizeof(allo));
                                /* Build a list of N_players/2 pairs	*/
                                /* using several trials if necessary	*/
                                /* level counts the number of games	*/
                                /* arranged so far: level=N_players/2	*/
                                /* means the complete round		*/
                                /* At each level, we pick up 		*/
                                /* players Sorted_indices[i] 		*/
                                /* and Sorted_indices[j] 		*/
                                /* and check to see if they have already*/
                                /* played with each other.		*/
                                /* For backtracking, we save i, and j in*/
                                /* si[level],sj[level]			*/
  for(i=0,level=1,status=0,retry_no=0;retry_no<N_retries;)
  {
    register int ti,tj;
    switch(status)
    {
      case 0:                           /* Find a candidate for level-th game*/
           i++;
           status = ( i>N_players ? 4 :
                       (ti=Sorted_indices[i], allo[ti] == 0 ? 1 : 0) );
           continue;

      case 1:                           /* Begin to search for the      */
           j = i;                       /* party for the ti-th player   */
           status=2;

      case 2:                           /* Find and test the party      */
           if( ++j>N_players )
           {                            /* Search failed for ti-th party*/
             status = 0;                /* Pick another ti              */
             continue;
           }                            /* tj-th player has just been   */
           tj = Sorted_indices[j];
           if( allo[tj] || Has_played[ti][tj] )  /* allocated      */
             continue;                  /* or ti-tj game took place     */
           status = 3;

      case 3:                           /* ti-tj game is arranged       */
           allo[ti]=tj;
           allo[tj]=ti;
           si[level]=i;  sj[level]=j;
           if( ++level>N_players/2 )    /* All games in a tour has been */
           {                            /* allocated                    */
             register int measure = find_measure(allo);
             if( measure < best_measure )
             {                          /* Save the best allocation     */
               best_measure = measure;  /* found beforehand             */
               memcpy(best_allo,allo,sizeof(allo));
             }
             ++retry_no;
             status = 4;                /* Find another alloc if possible */
           }
           else
             status=0;
           continue;

      case 4:                           /* back tracking to the prev.   */
           level--;                     /* level                        */
           if( level<1 )
             break;                     /* no more alternatives         */
           i = si[level];               /* Restore values for the prev  */
           j = sj[level];               /* level                        */
           ti = Sorted_indices[i];
           tj = Sorted_indices[j];
           allo[ti] = allo[tj] = 0;
           status = 2;
           continue;
    }
    break;
  }

  if(retry_no == 0)
    message("Allocation failed!");
}

static void print_allocation(const int allo[])
{
  FILE *pr = fopen("prn","w");
  register int i;

  assert( pr != (FILE *)0 );
  fprintf(pr,"player #1");
  for(i=1; i<=N_players; ++i)
     fprintf(pr,"%3d",i);
  fprintf(pr,"\nplayer #2");
  for(i=1; i<=N_players; ++i)
     fprintf(pr,"%3d",allo[i]);
  fprintf(pr,"\n\f");
  fclose(pr);
}


			/* Root scheduling module		*/
static void allocation(void)
{
  int allo[Max_players+1];              /* i-th player will have a game */
                                        /* with the allo[i]-th player   */
  register int i;

  cursor(18,20);
  fprintf(stderr,"\033[4mT h i n k i n g ...\033[m");
  sort();                               /* Sort 'Scores' in desc. order*/
  try_allocate(allo);

  clear_screen();
  fprintf(stderr,"\n\n\n\t\t\t\033[4mALLOCATION FOR A NEW TOUR\033[m");

  cursor(7,0);
  fprintf(stderr,"Player #1");
  for(i=1; i<=N_players; ++i)
     fprintf(stderr,"%3d",i);
  fprintf(stderr,"\nPlayer #2");
  for(i=1; i<=N_players; ++i)
     fprintf(stderr,"%3d",allo[i]);
  cursor(18,20); fprintf(stderr,"Print the allocation?");
  if( toupper(getchar()) == 'Y' )
    print_allocation(allo);
  getchar();
}

/*
 *=======================================================================
 *                    Output the concluding results
 */
static void concluding_results(void)
{
  register int i;

  sort();                       /* Sort 'Scores' in descending order   */
  clear_screen();
  fprintf(stderr,"\n\n\n\t\t\t\033[4mCONCLUDING RESULTS\033[m");

  cursor(7,0);
  fprintf(stderr,"Player");
  for(i=1; i<=N_players; ++i)
     fprintf(stderr,"%3d",Sorted_indices[i]);
  fprintf(stderr,"\nScore");
  for(i=1; i<=N_players; ++i)
  {
    register int res = Scores[Sorted_indices[i]];
    cursor(8,3*i+4);
    fprintf(stderr,"%3d",res/2);        /* Integral part of result      */
    if( res%2 )                         /* Output a half a point        */
    {                                   /* if any                     	*/
      cursor(9,3*i+5); fprintf(stderr,"/2");
    }
  }
  message("");
}

/*
 *=======================================================================
 *                      Save status for recovery
 */

static void save_status(void)
{
  FILE *fp = fopen(Work_file_name,"wb");
  assert( fp != (FILE *)0 );
  putw(N_players,fp);
  fwrite(Has_played,sizeof(Has_played),1,fp);
  fwrite(Scores,sizeof(Scores),1,fp);
  fclose(fp);
  message("Saved");
}

/*
 *=======================================================================
 *                         Getting started
 */

			/* Start from scratch				 */
static void cold_start(void)
{
  int i;

  fprintf(stderr,"\n\nHow many people will take part in the tournament >");
  scanf("%d",&N_players); getchar();
  if( N_players <= 4 || N_players > Max_players || N_players % 2 )
    fprintf(stderr,"\nBad no '%d'",N_players), exit(4);
  fprintf(stderr,"\nWork file name >");
  fgets(Work_file_name,sizeof(Work_file_name),stdin);
  Work_file_name[sizeof(Work_file_name)-1] = '\n';
  *strchr(Work_file_name,'\n') = '\0';

  for(i=1; i<=N_players; i++)           /* Each guy has played with himself*/
     Has_played[i][i] = 1;
}

			/* Resume the interrupted execution             */
			/* using already accumulated history		*/
static void warm_start(const char *file_name)
{
  FILE *fp;

  strncpy(Work_file_name,file_name,sizeof(Work_file_name)-1);
  fp = fopen(Work_file_name,"rb");
  assert( fp != (FILE *)0 );
  N_players = getw(fp);
  if( N_players <= 4 || N_players > Max_players || N_players % 2 )
    fprintf(stderr,"\nBad no '%d'",N_players), exit(4);
  fread(Has_played,sizeof(Has_played),1,fp);
  fread(Scores,sizeof(Scores),1,fp);
  fclose(fp);
}

			/* The Main module			*/
void main(int argc, const char * argv[])
{
  if( argc>2 )
    fprintf(stderr,"Too many arguments. Only work file name may be specified"),
    exit(4);

  if( argc == 1 )
    cold_start();
  else
    warm_start(argv[1]);

  for(;;)              		/* Main loop    */
  {
    clear_screen(); cursor(3,0);
    fprintf(stderr,"\t\t\t\033[4mM A I N   M E N U\033[m\n\n");
    fprintf(stderr,"\t\t1. Enter scores for a finished round\n");
    fprintf(stderr,"\t\t2. Perform an allocation for the next round\n");
    fprintf(stderr,"\t\t3. Output concluding results\n");
    fprintf(stderr,"\t\t4. Save status to the work file\n");
    for(;;)
    {
        int c;
        cursor(15,20);
        fprintf(stderr,"Enter your choice \033[1m>\033[m");
        switch((c=getchar(),getchar(),c))
        {
           case '1':
                input();
                break;

           case '2':
                allocation();
                break;

           case '3':
                concluding_results();
                break;

           case '4':
                save_status();
                break;

           default:
                continue;
        }
        break;
    }
  }
}

