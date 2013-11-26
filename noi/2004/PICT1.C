//#define DEBUG

#include <stdio.h>

#define IN      "pict.in"
#define MAX     1600
#define INF     0x7fffffff
#define EPS     0.00000001

long n;
double w;
double small[MAX], big[MAX];
double best[MAX];

long the_best;
long bigger[MAX], num;

int check(double max, long start, long end)
{
   long i;
   double sum;

   sum=0;

   for(i=start; i<=end && sum-w<=EPS; i++)
      if(big[i]>max)
        sum+=big[i];
      else
        sum+=small[i];

   if(i>end && sum-w<=EPS) return 1;

   return 0;
}

double calc_it(long start, long end)
{
   double res;
   long i, newnum, tmp;

   if(!num)
     the_best=start;
   else
   {
     if(small[start]>small[the_best])
       the_best=start;
   }

   newnum=0;
   for(i=0; i<num; i++)
      if(big[bigger[i]]>small[the_best])
        bigger[newnum++]=bigger[i];

   if(big[start]>small[the_best])
     bigger[newnum++]=start;

   num=newnum;
   i=num-1;

   while(i>0 && big[bigger[i]]<big[bigger[i-1]])
   {
      tmp=bigger[i];
      bigger[i]=bigger[i-1];
      bigger[i-1]=tmp;
      i--;
   }

   if(check(small[the_best], start, end))
     return small[the_best];

   for(i=0; i<num; i++)
      if(check(big[bigger[i]], start, end))
        return big[bigger[i]];

   return -1;
}

int main()
{
   long i, j;
   double t;

#ifdef DEBUG
   freopen(IN, "r", stdin);
#endif

   scanf("%ld%lf", &n, &w);

   for(i=1; i<=n; i++)
   {
      scanf("%lf%lf", small+i, big+i);

      if(small[i]>big[i])
      {
        t=small[i];
        small[i]=big[i];
        big[i]=t;
      }
   }

#ifdef DEBUG
   fclose(stdin);
#endif

   best[0]=0;

   for(i=1; i<=n; i++)
   {
      num=0;
      best[i]=INF;

      for(j=i; j>0; j--)
      {
         t=calc_it(j, i);

         if(t<0) break;

         if(t+best[j-1]<best[i])
           best[i]=t+best[j-1];
      }
   }

   printf("%lf\n", best[n]);

   return 0;
}

