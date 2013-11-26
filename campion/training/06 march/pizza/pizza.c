#include <stdio.h>
#include <math.h>

#define INPUT_FILE  "pizza.in"
#define OUTPUT_FILE "pizza.out"

#define MaxRest 21
#define MAXN 101

int NrRest;
int R, M;
int N;
struct locatie {  int x,y; } loc[MaxRest];
struct camin {int x,y,s; } stud[MAXN];
int sol[MaxRest];

int in[MaxRest][MAXN];
// in[i][j]=1 daca caminul j se afla in raza de actiune a pizzeriei din locatia i

long int rez;


void citire(void)
{ int i;
  FILE *file;
  file = fopen(INPUT_FILE,"r");
  fscanf(file,"%d%d", &NrRest, &R);
  fscanf(file,"%d", &M);
  for (i=1; i<= M; i++)
      fscanf(file,"%d%d",&loc[i].x, &loc[i].y);
  fscanf(file, "%d", &N);
  for (i=1; i<= N; i++)
      fscanf(file,"%d%d%d",&stud[i].x, &stud[i].y, &stud[i].s);
  fclose(file);
}

int inraza(int locatie,int camin)
//functia returneaza 1 daca camin se afla in raza de actiune a pizzeriei
//din locatia locatie
{
  return
     ((long)(loc[locatie].x - stud[camin].x) *
      (loc[locatie].x - stud[camin].x) +
      (long)(loc[locatie].y - stud[camin].y) *
      (loc[locatie].y - stud[camin].y) <= (long)R * R);
}


void rezolva(void)
{
  int i,j;
  long int total;

  for (i=1; i<=M; i++)
      for (j=1; j<=N; j++)
          if (inraza(i,j)) in[i][j] = 1;
             else in[i][j] = 0;
  rez = 0;
  /* generam combinarile de M luate cate K, calculam totalul clientilor siguri
  pentru fiecare combinare si retinem maximul */

  for (i=1; i<= NrRest; i++) sol[i]=i;
  while (1)
        {
         total=0;
         for (j=1; j<=N; j++)
              for (i=1; i<= NrRest; i++)
                 if (in[sol[i]][j])
                    {total += stud[j].s;
                     break;}
         if (total>rez)
            rez=total;
         //generate the next solution
         for (i=NrRest; i>=1 && sol[i]==M-NrRest+i; i--);
         if (!i) return;
            else
            {
            sol[i]++;
            for (j=i+1; j <= NrRest; j++)
                sol[j]=sol[j-1]+1;
            }
        }
}

void afisare(void)
{
  FILE * file = fopen(OUTPUT_FILE,"w");
  fprintf(file,"%d\n",rez);
  fclose(file);
}

int main(void)
{
  citire();
  rezolva();
  afisare();
  return 0;
}
