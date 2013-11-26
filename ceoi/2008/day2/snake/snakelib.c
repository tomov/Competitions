#include <stdio.h>
#include <stdlib.h>

#include "snakelib.h"

#define INPUT_FILE_NAME "snake.in"
#define LOG_FILE_NAME "snake.log"

static int initialised = 0;
static int Len, Tail, K, turn = 0;
static FILE *log = NULL;

static void die(char const* Message) {
   printf("An error occured: %s. Please check snake.log!\n", Message);
   if (log != NULL) {
      fprintf(log, "Error: %s!\n", Message);
      fclose(log);
   } else {
      log = fopen(LOG_FILE_NAME, "w");
      if (log == NULL) {
	 printf("error opening snake.log for writing");
	 exit(1);
      }
      fprintf(log, "Error: %s!\n", Message);
      fclose(log);
   }
   exit(1);
}

void initialise()
{
   FILE *in;
   char tmp[256];
  
   log = fopen(LOG_FILE_NAME, "w");
   if (log == NULL) {
      printf("error opening snake.log for writing");
      exit(1);
   }
  
   in = fopen(INPUT_FILE_NAME, "r");
   if (in == NULL)
      die("could not open snake.in");
  
   if (fscanf(in, "%d %d %d", &Len, &Tail, &K) != 3) 
      die("Wrong format in snake.in");
   if (Len > MAXLEN) {
      sprintf(tmp, "the snake length must be at most %d", MAXLEN);
      die(tmp);
   }
   if (Len < 1) die("the snake must have a positive length");
   if (Tail + Len - 1 > MAXN) {
      sprintf(tmp, "all parts of the snake must initially be within the hearing distance %d", MAXN);
      die(tmp);
   }
   if (Tail < 0) die("the initial distance between you and the snake cannot be negative");
   if (K < 0) die("the snake speed cannot be a negative number");
   if (K > MAXSPEED) {
      sprintf(tmp, "the snake speed cannot exceed %d", MAXSPEED);
      die(tmp);
   }

   initialised = 1;
}

int get_speed()
{
   if (initialised) die("do not call get_speed more than once");
   if (!initialised) initialise();
   fprintf(log, "get_speed. reply: %d\n", K);
   return K;
}

char eval(int p)
{
   char a;
   char tmp[256];
  
 
   if (p < 0) {
      die("the position cannot have a negative value");
   }
   if (p > MAXN) {
      sprintf(tmp, "the position cannot exceed %d", MAXN);
      die(tmp);
   }
   if (p < Tail) {
      a = 'b';
   } else if (p >= Tail + Len) {
      a = 'f';
   } else {
      a = 's';
   }
   return a;
}

void ask_snake(int U1, int U2, char *A1, char *A2)
{
   if (!initialised)
      die("you need to call get_speed first");
  
   turn++;
   char tmp[256];
   fprintf(log, "%2d: ask_snake(%d, %d). reply: ", turn, U1, U2);
   if (turn >= MAXCALL2) { sprintf(tmp, "you cannot ask the snake more than %d times", MAXCALL2 - 1); die(tmp); }
   if ((turn % 2 == 0) && Tail + K + Len <= MAXN) Tail += K;
   *A1 = eval(U1);
   *A2 = eval(U2);
   fprintf(log, "%c %c\n", *A1, *A2);
   fprintf(log, "    (the snake currently covers units %d - %d)\n", Tail, Tail + Len - 1);
}

void tell_length(int L) {
   if (!initialised) die("you need to call get_speed first");
   fprintf(log, "tell_length(%d)\n", L);
   if (L < 1) die("the snake length is always a positive number");
   if (abs(L - Len) > K) {
      fprintf(log, "Wrong! Your estimate is not good enough");
   } else {
      fprintf(log, "Your estimate is within the allowed range! You needed to ask the snake %d times\n", turn);
      fprintf(log, "You would get %s score for this test\n", turn <= MAXCALL1 ? "full" : "half");
   }
   fclose(log);
   exit(0);
}
