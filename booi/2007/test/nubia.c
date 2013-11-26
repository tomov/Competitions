/*
TASK:nubia
LANG:C
*/
#include <stdio.h>
#define inf 1000000000000000

 long long n,pom,heap[262144],sum,c,tmp,m;

 void add (long long z)
  {
   long long i;
   heap[++c]=z;
   i=c;
   while (i!=1)
    if (heap[i]<heap[i/2])
     {
      tmp=heap[i];
      heap[i]=heap[i/2];
      heap[i/2]=tmp;
      i/=2;
     }
      else
       break;
  }

 void del ()
  {
   long long i,v;
   heap[1]=heap[c];
   heap[c]=inf;
   c--;
   i=1;
   while (i*2<=c)
    {
     v=i*2;
     if (heap[v]>heap[v+1])
      v++;
     if (heap[i]>heap[v])
      {
       tmp=heap[i];
       heap[i]=heap[v];
       heap[v]=tmp;
       i=v;
      }
       else
        break;
    }
  }

 int main ()
  {
   long long i,cur;
   scanf("%Ld",&m);
   sum=0;
   c=0;
   for (i=1;i<=m;i++)
    {
     scanf("%Ld",&pom);
     sum+=pom;
     add(pom);
    }
   scanf("%Ld",&n);
   for (i=1;i<=n;i++)
    {
     scanf("%Ld",&pom);
     add(pom);
    }
//?
   cur=0;
   while (1)
    {
     if (heap[1]-1<=cur)
      cur+=heap[1];
       else
        break;
     del();
     if (c==0 || cur>=sum)
      break;
    }
   if (cur<sum)
    printf("%Ld\n",sum-cur-1);
     else
      printf("0\n");
   return 0;
  }


