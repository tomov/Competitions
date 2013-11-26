#include <stdio.h>
#include "snakelib.h"

int K;
char a1, a2;

int main()
{
  K = get_speed();
  printf("the snake's speed is %d\n", K);
  
  printf("asking the snake if it covers units 0 and 11\n");
  ask_snake(0, 11, &a1, &a2);
  printf("and the snake says: %c %c\n", a1, a2);
  
  printf("asking the snake if it covers units 2 and 10\n");
  ask_snake(2, 10, &a1, &a2);
  printf("and the snake says: %c %c\n", a1, a2);
  
  printf("asking the snake if it covers units 4 and 9\n");
  ask_snake(4, 9, &a1, &a2);
  printf("and the snake says: %c %c\n", a1, a2);
  
  printf("asking the snake if it covers units 6 and 10\n");
  ask_snake(6, 10, &a1, &a2);
  printf("and the snake says: %c %c\n", a1, a2);
  
  printf("tell the snake that you guess its length to be 6\n");
  tell_length(6);
}
