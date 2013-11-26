#include <stdio.h>
#include <conio.h>

int DEPTH=1000000;

int n;
int max[32];
int ini[32];
int coef[32];
int p;
int deal[262144][4];
int done[1048576];
char type[1048576];
int neis[1048576];
int reached[1048576];
int ques;
int que[1048576];
int goal;
int moves;
FILE *inp;
FILE *login;
FILE *logout;
FILE *config;

int main(void) {
	int i, j, q, w, turn;
	int quan[32];

	config=fopen("config", "r");
	if (config) {
		fscanf(config, "%d", &DEPTH);
		if (DEPTH==0) DEPTH=1000000;
	}
	inp=fopen("input", "r");
	login=fopen("login", "w");
	logout=fopen("logout", "w");
	fscanf(inp, "%d", &n);
	if (n<2) {
		cprintf("Cannot read input - N is less than 2!\n");
		return 0;
	}
	printf("%d\n", n);
	fprintf(login, "%d\n", n);
	coef[1]=1;
	for (i=1; i<=n; i++) {
		fscanf(inp, "%d %d", &max[i], &ini[i]);
		printf("%d %d\n", max[i], ini[i]);
		fprintf(login, "%d %d\n", max[i], ini[i]);
		coef[i+1]=coef[i]*(max[i]+1);
	}
	fscanf(inp, "%d", &p);
	printf("%d\n", p);
	fprintf(login, "%d\n", p);
	for (i=1; i<=p; i++) {
		fscanf(inp, "%d %d %d %d", &deal[i][0], &deal[i][1], &deal[i][2], &deal[i][3]);
		printf("%d %d %d %d\n", deal[i][0], deal[i][1], deal[i][2], deal[i][3]);
		fprintf(login, "%d %d %d %d\n", deal[i][0], deal[i][1], deal[i][2], deal[i][3]);
	}

	for (i=0; i<coef[n+1]; i++) {
		for (j=1; j<=n; j++) quan[j]=(i%coef[j+1])/coef[j];
		for (j=1; j<=p; j++) {
			if (quan[deal[j][0]]>=deal[j][1] && quan[deal[j][2]]+deal[j][3]<=max[deal[j][2]]) neis[i]++;
		}
		if (neis[i]==0) {
			type[i]=1;
			que[ques]=i;
			ques++;
		}
	}

	for (q=0; q<ques; q++) {
		i=que[q];
		for (j=1; j<=n; j++) quan[j]=(i%coef[j+1])/coef[j];
		if (type[i]==1) {
			for (j=1; j<=p; j++) {
				if (quan[deal[j][2]]>=deal[j][3] && quan[deal[j][0]]+deal[j][1]<=max[deal[j][0]]) {
					w=i-deal[j][3]*coef[deal[j][2]]+deal[j][1]*coef[deal[j][0]];
					if (!type[w]) {
						type[w]=2;
						que[ques]=w;
						ques++;
					}
				}
			}
		} else {
			for (j=1; j<=p; j++) {
				if (quan[deal[j][2]]>=deal[j][3] && quan[deal[j][0]]+deal[j][1]<=max[deal[j][0]]) {
					w=i-deal[j][3]*coef[deal[j][2]]+deal[j][1]*coef[deal[j][0]];
					if (!type[w]) {
						reached[w]++;
						if (reached[w]==neis[w]) {
							type[w]=1;
							que[ques]=w;
							ques++;
						}
					}
				}
			}
		}
	}

	fflush(stdout);

	w=0;
	for (i=1; i<=n; i++) w+=coef[i]*ini[i];
	goal=type[w];
	scanf("%d", &turn);
	fprintf(logout, "%d\n", turn);
	if (turn!=1 && turn!=2) {
		printf("0\n");
		fflush(stdout);
		fprintf(login, "0\n");
		cprintf("Invalid starting position - should be 1 or 2!\n");
		return 0;
	}
	if (turn==goal) {
		printf("0\n");
		fflush(stdout);
		fprintf(login, "0\n");
		cprintf("Wrong choice of starting position - %d\n", turn);
		return 0;
	}

	while (1) {
		if (turn==2) {
			if (type[w]==2) {
				printf("0\n");
				fflush(stdout);
				fprintf(login, "0\n");
				cprintf("You lost, buddy! I'm sorry!\n");
				return 0;
			}
			if (type[w]==0 && goal) {
				printf("0\n");
				fflush(stdout);
				fprintf(login, "0\n");
				cprintf("You failed to win, buddy! I'm sorry!\n");
				return 0;
			}
			for (j=1; j<=n; j++) quan[j]=(w%coef[j+1])/coef[j];
			for (j=1; j<=p; j++) {
				if (quan[deal[j][0]]>=deal[j][1] && quan[deal[j][2]]+deal[j][3]<=max[deal[j][2]] && !done[coef[n+1]*(j-1)+w]) {
					i=w-deal[j][1]*coef[deal[j][0]]+deal[j][3]*coef[deal[j][2]];
					if (type[w]==2 && type[i]==1) break;
					if (type[w]==0 && type[i]!=2) break;
					if (type[w]==1) break;
				}
			}
			moves++;
			if (j<=p) {
				if (moves>=DEPTH) {
					printf("0\n");
					fflush(stdout);
					fprintf(login, "0\n");
					if (goal) cprintf("You win!!! Congratulations!!!\n");
					else cprintf("Wow! You can really play forever! Congratulations!!!\n");
					return 0;
				}
				done[coef[n+1]*(j-1)+w]=1;
				q=j;
				printf("%d\n", q);
				fflush(stdout);
				fprintf(login, "%d\n", q);
			} else {
				printf("0\n");
				fflush(stdout);
				fprintf(login, "0\n");
				if (goal) cprintf("You win!!! Congratulations!!!\n");
				else cprintf("Wow! You can really play forever! Congratulations!!!\n");
				return 0;
			}
		} else {
			scanf("%d", &q);
			fprintf(logout, "%d\n", q);
			if (q<1 || q>p) {
				printf("0\n");
				fflush(stdout);
				fprintf(login, "0\n");
				cprintf("Invalid deal - should be between 1 and %d!\n", p);
				return 0;
			}
			for (j=1; j<=n; j++) quan[j]=(w%coef[j+1])/coef[j];
			if (quan[deal[q][0]]<deal[q][1] || quan[deal[q][2]]+deal[q][3]>max[deal[q][2]]) {
				printf("0\n");
				fflush(stdout);
				fprintf(login, "0\n");
				cprintf("Invalid deal - conditions are not met!\n", p);
				return 0;
			}
		}
		w+=deal[q][3]*coef[deal[q][2]]-deal[q][1]*coef[deal[q][0]];
		turn=3-turn;
	}
}
