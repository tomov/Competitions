/* This sample library can be used for testing purposes. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cgamelib.h"

#define MAXN 2010

static int initialized = 0;
static int n, list[MAXN];
static int left, right, score;
static FILE *f_in, *f_log;

void initialize() {
  int i;
  if(initialized) {
    fprintf(f_log,"ERROR: Cannot Initialize Twice.\n");
    exit(0);
  }

  f_in = stdin;
  f_log = stdout;
  initialized = 1;
  fscanf(f_in,"%d",&n);
  for(i=0; i<n; i++)
    fscanf(f_in,"%d",&list[i]);
  
  left = 0;
  right = n-1;
  score = 0;
  srand(time(0));
  fprintf(f_log,"Initialization Complete.\n");
}

int getN() {
  if(!initialized) {
    fprintf(f_log,"Error: Cannot call getN() before initialize().\n");
    exit(0);
  }

  fprintf(f_log,"getN() returns %d.\n",n);
  return n;
}

int getValue(int city) {
  if(!initialized) {
    fprintf(f_log,"ERROR: Cannot call getValue() before initialize().\n");
    exit(0);
  }

  if(city<0 || city>=n) {
    fprintf(f_log,"ERROR: City %d is invalid.\n",city);
    exit(0);
  }

  fprintf(f_log,"getValue(%d) returns %d.\n",city,list[city]);
  return list[city];
}

int move(int city) {
  int response, i;
  fprintf(f_log,"Your move is: put the bastions after city %d.\n",city);
  if(!(city>=left && city<right)) {
    fprintf(f_log,"ERROR: Your move is invalid.\n");
    exit(0);
  } 
  
  /***** You may change the response choice to have a better opponent. *****/
  response = rand()%2;
  /*********************************************************************/

  if(response==0) {
    for(i=left; i<=city; i++)
      score += list[i];
    right = city;
  }

  else {
    for(i=city+1; i<=right; i++)
      score += list[i];
    left = city+1;
  }

  fprintf(f_log,"Opponent attacks from: %s.\n",(response)?"Left":"Right");
  fprintf(f_log,"New interval is: [%d,%d].\n",left,right);
  fprintf(f_log,"Total score at this moment is %d.\n",score);
  if(left>=right) {
    printf("Final total score is %d.\n",score);
    exit(0);
  }
  
  return response; 
}
