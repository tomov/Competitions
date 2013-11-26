#include <stdio.h>

int n;
int max[32];
int ini[32];
int coef[32];
int p;
int deal[262144][4];
char type[1048576];
int neis[1048576];
int reached[1048576];
int ques;
int que[1048576];
int wins, losses;

int main(void) {
	int i, j, q, w, turn;
	int quan[32];

	scanf("%d", &n);
	coef[1]=1;
	for (i=1; i<=n; i++) {
		scanf("%d %d", &max[i], &ini[i]);
		coef[i+1]=coef[i]*(max[i]+1);
	}
	scanf("%d", &p);
	for (i=1; i<=p; i++) scanf("%d %d %d %d", &deal[i][0], &deal[i][1], &deal[i][2], &deal[i][3]);

	for (i=0; i<coef[n+1]; i++) {
		for (j=1; j<=n; j++) quan[j]=(i%coef[j+1])/coef[j];
		for (j=1; j<=p; j++) {
			if (quan[deal[j][0]]>=deal[j][1] && quan[deal[j][2]]+deal[j][3]<=max[deal[j][2]]) neis[i]++;
		}
		if (neis[i]==0) {
			type[i]=1;
			losses++;
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
						wins++;
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
							losses++;
							que[ques]=w;
							ques++;
						}
					}
				}
			}
		}
	}

	w=0;
	for (i=1; i<=n; i++) w+=coef[i]*ini[i];
	turn=(3-type[w])%3;
	printf("Complexity:  %d\n", coef[n+1]*p);
	printf("Situations:  %d\n", coef[n+1]);
	printf("Wins:  %d\n", wins);
	printf("Losses:  %d\n", losses);
	printf("Draws:  %d\n", coef[n+1]-wins-losses);
	printf("Right choice: %d\n", turn);

	return 0;
}
