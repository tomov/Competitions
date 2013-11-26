#include <stdio.h>
#include <string.h>

int main()
{
   char response[10];
   int  width, height;

   do {
      printf("left\n");
      fflush(stdout);
      scanf("%s", response);
   } while (strcmp(response, "fail") != 0);

   width = 0;
   do {
      ++width;
      printf("right\n");
      fflush(stdout);
      scanf("%s", response);
   } while (strcmp(response, "fail") != 0);

   do {
      printf("up\n");
      fflush(stdout);
      scanf("%s", response);
   } while (strcmp(response, "fail") != 0);

   height = 0;
   do {
      ++height;
      printf("down\n");
      fflush(stdout);
      scanf("%s", response);
   } while (strcmp(response, "fail") != 0);

   printf("%d\n", width*height);
   fflush(stdout);
   
   return 0;
}
