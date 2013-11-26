#include <stdio.h>
#include <stdlib.h>
#define InFile "flood.in"
#define OutFile "flood.out"
#define MAXN		16000
#define MAXP            200005

struct Drum {int x, y, c; char uz;} d[MAXP];
int n, p;
unsigned up[MAXN];
unsigned h[MAXP];

void creareheap(void);
int extract_min (int *);
void combheap(int, int);

int getrep(int x)
{
	int y, tmp;

	for(y = x; up[y]; y = up[y]) ;
	while (x != y) {
		tmp = up[x];
		up[x] = y;
		x = tmp;
	}
	return(y);
}

void unify(int x, int y)
{
if (h[x]>h[y])
   up[y]=x;
   else
   { up[x]=y;
    if (h[y]==h[x]) h[y]++;
   }
}



int main()
{
 int i, m, j, x, y, rx, ry, nr, sp;
 long sum=0;

 freopen(InFile, "r", stdin);
 freopen(OutFile, "w", stdout);
 scanf("%d%d", &n, &m);
 for (i=0; i<m; i++)
     {
     scanf("%d%d", &x, &y);
     rx=getrep(x);
     ry=getrep(y);
     if (rx!=ry)
        unify(rx,ry);
     }

 scanf("%d", &p);
 for (i=1; i<=p; i++)
     {d[i].uz=0;
      scanf("%d%d%d", &d[i].x, &d[i].y, &d[i].c);}

 for (nr=-1, i=1;  i <=n; i++)
     if (!up[i]) nr++;
 printf("%d\n", nr);
 sp=p;
 creareheap();
 for (i=1; i<=nr; )
     {j=extract_min(&p);
      rx=getrep(d[j].x);
      ry=getrep(d[j].y);
      if (rx!=ry)
         {i++;
          sum+=d[j].c;
          d[j].uz=1;
          unify(rx,ry);
         }
      }
 printf("%ld\n", sum);
 for (i=1; i<=sp; i++)
     if (d[i].uz)
         printf("%d %d %d\n", d[i].x, d[i].y, d[i].c);
 return(0);
}


void combheap (int i, int n)
{
 int fiu, tata, aux;
 tata = i; fiu = 2*i;
 while (fiu<=n)
     {
      if (fiu+1<=n)
          fiu = d[h[fiu]].c>d[h[fiu+1]].c?fiu+1:fiu;
      if (d[h[tata]].c>d[h[fiu]].c)
         {
          aux = h[tata];
          h[tata] = h[fiu];
          h[fiu] = aux;
          tata = fiu; fiu*=2;
         }
         else break;
     }
 }



void creareheap()
{
 int i;
 for (i=1; i<=p; i++) h[i]=i;
 for (i=p/2; i>0; i--)
     combheap(i,p);
}

int extract_min(int *n)
{
 int fiu, tata, aux, x;
 x=h[1]; h[1]=h[*n]; (*n)--;
 tata = 1; fiu = 2;
 while (fiu<=*n)
     {
      if (fiu+1<=*n)
      fiu = d[h[fiu]].c>d[h[fiu+1]].c?fiu+1:fiu;
      if (d[h[tata]].c>d[h[fiu]].c)
         {
          aux = h[tata];
          h[tata] = h[fiu];
          h[fiu] = aux;
          tata = fiu; fiu*=2;
         }
         else break;
      }
 return x;
}
