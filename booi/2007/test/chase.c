/*
TASK:chase
LANG:C
*/
#include <stdio.h>
#define inf 2000000000

 struct T
  {
   long s,i1,i2;
  }heap[16384],tmp;

 long n,m,k,Gx,Gy,X,Y,z[128][128],d[128][128],c,pos[128][128];
 char a[128][128];

 void add (long A,long B,long C)
  {
   long i;
   c++;
   heap[c].s=A;
   heap[c].i1=B;
   heap[c].i2=C;
   pos[B][C]=c;
   i=c;
   while (i!=1)
    if (heap[i].s<heap[i/2].s)
     {
      pos[heap[i/2].i1][heap[i/2].i2]=i;
      pos[heap[i].i1][heap[i].i2]=i/2;
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
   long i,v;
   heap[1]=heap[c];
   heap[c].s=inf;
   pos[heap[1].i1][heap[1].i2]=1;
   c--;
   i=1;
   while (i*2<=c)
    {
     v=i*2;
     if (heap[v].s>heap[v+1].s)
      v++;
     if (heap[i].s>heap[v].s)
      {
       pos[heap[v].i1][heap[v].i2]=i;
       pos[heap[i].i1][heap[i].i2]=v;
       tmp=heap[i];
       heap[i]=heap[v];
       heap[v]=tmp;
       i=v;
      }
       else
        break;
    }
  }

 void update (long h,long x,long y)
  {
   long i;
   i=pos[x][y];
   if (i==-1)
    return;
   if (h==0)
    heap[i].s=z[x][y];
     else
      heap[i].s=d[x][y];
   while (i!=1)
    if (heap[i].s<heap[i/2].s)
     {
      pos[heap[i/2].i1][heap[i/2].i2]=i;
      pos[heap[i].i1][heap[i].i2]=i/2;
      tmp=heap[i];
      heap[i]=heap[i/2];
      heap[i/2]=tmp;
      i/=2;
     }
      else
       break;
  }

 int main ()
  {
   long i,j,j1,j2,pom,res;
   scanf("%ld%ld%ld",&n,&m,&k);
   for (i=1;i<=n;i++)
    {
     scanf("%s",&a[i]);
     for (j=m;j>=1;j--)
      a[i][j]=a[i][j-1];
    }
   scanf("%ld%ld",&Gx,&Gy);
//
   for (i=1;i<=n;i++)
    for (j=1;j<=m;j++)
     z[i][j]=inf;
   for (i=1;i<=k;i++)
    {
     scanf("%ld%ld",&X,&Y);
     z[X][Y]=0;
    }
   c=0;
   for (j1=1;j1<=n;j1++)
    for (j2=1;j2<=m;j2++)
     add(z[j1][j2],j1,j2);
   while (c!=0)
    {
     if (heap[1].s==inf)
      break;
     j1=heap[1].i1;
     j2=heap[1].i2;
     pom=z[j1][j2]+(long)a[j1][j2]-48;
     if (j1-2>0 && a[j1-2][j2]!='X' && z[j1-2][j2]>pom)
      {
       z[j1-2][j2]=pom;
       update(0,j1-2,j2);
      }
     if (j1+2<=n && a[j1+2][j2]!='X' && z[j1+2][j2]>pom)
      {
       z[j1+2][j2]=pom;
       update(0,j1+2,j2);
      }
     if (j1-1>0 && a[j1-1][j2]!='X' && z[j1-1][j2]>pom)
      {
       z[j1-1][j2]=pom;
       update(0,j1-1,j2);
      }
     if (j1+1<=n && a[j1+1][j2]!='X' && z[j1+1][j2]>pom)
      {
       z[j1+1][j2]=pom;
       update(0,j1+1,j2);
      }
     if (j1%2==0)
      {
       if (j2+1<=m && j1-1>0 && a[j1-1][j2+1]!='X' && z[j1-1][j2+1]>pom)
        {
         z[j1-1][j2+1]=pom;
         update(0,j1-1,j2+1);
        }
       if (j2+1<=m && j1+1<=n && a[j1+1][j2+1]!='X' && z[j1+1][j2+1]>pom)
        {
         z[j1+1][j2+1]=pom;
         update(0,j1+1,j2+1);
        }
      }
       else
        {
         if (j2-1>0 && j1-1>0 && a[j1-1][j2-1]!='X' && z[j1-1][j2-1]>pom)
          {
           z[j1-1][j2-1]=pom;
           update(0,j1-1,j2-1);
          }
         if (j2-1>0 && j1+1<=n && a[j1+1][j2-1]!='X' && z[j1+1][j2-1]>pom)
          {
           z[j1+1][j2-1]=pom;
           update(0,j1+1,j2-1);
          }
        }
     del();
     pos[j1][j2]=-1;
    }
//
   for (i=1;i<=n;i++)
    for (j=1;j<=m;j++)
     d[i][j]=inf;
   d[Gx][Gy]=0;
   c=0;
   for (j1=1;j1<=n;j1++)
    for (j2=1;j2<=m;j2++)
     add(d[j1][j2],j1,j2);
   while (c!=0)
    {
     if (heap[1].s==inf)
      break;
     j1=heap[1].i1;
     j2=heap[1].i2;
     if (d[j1][j2]+(long)a[j1][j2]-48<=z[j1][j2])
      {
       pom=d[j1][j2]+(long)a[j1][j2]-48;
       if (j1-2>0 && a[j1-2][j2]!='X' && d[j1-2][j2]>pom)
        {
         d[j1-2][j2]=pom;
         update(1,j1-2,j2);
        }
       if (j1+2<=n && a[j1+2][j2]!='X' && d[j1+2][j2]>pom)
        {
         d[j1+2][j2]=pom;
         update(1,j1+2,j2);
        }
       if (j1-1>0 && a[j1-1][j2]!='X' && d[j1-1][j2]>pom)
        {
         d[j1-1][j2]=pom;
         update(1,j1-1,j2);
        }
       if (j1+1<=n && a[j1+1][j2]!='X' && d[j1+1][j2]>pom)
        {
         d[j1+1][j2]=pom;
         update(1,j1+1,j2);
        }
       if (j1%2==0)
        {
         if (j2+1<=m && j1-1>0 && a[j1-1][j2+1]!='X' && d[j1-1][j2+1]>pom)
          {
           d[j1-1][j2+1]=pom;
           update(1,j1-1,j2+1);
          }
         if (j2+1<=m && j1+1<=n && a[j1+1][j2+1]!='X' && d[j1+1][j2+1]>pom)
          {
           d[j1+1][j2+1]=pom;
           update(1,j1+1,j2+1);
          }
        }
         else
          {
           if (j2-1>0 && j1-1>0 && a[j1-1][j2-1]!='X' && d[j1-1][j2-1]>pom)
            {
             d[j1-1][j2-1]=pom;
             update(1,j1-1,j2-1);
            }
           if (j2-1>0 && j1+1<=n && a[j1+1][j2-1]!='X' && d[j1+1][j2-1]>pom)
            {
             d[j1+1][j2-1]=pom;
             update(1,j1+1,j2-1);
            }
          }
      }
     del();
     pos[j1][j2]=-1;
    }
//
   res=0;
   for (i=1;i<=n;i++)
    for (j=1;j<=m;j++)
     if (d[i][j]!=inf && res<z[i][j])
      res=z[i][j];
   printf("%ld\n",res);
   return 0;
  }
