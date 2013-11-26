/*
TASK: score
LANG: C++

FROM: IOI 2001 day 2
PROB: score
KEYW: acyclic game
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define MAXN (1 << 10)

static int N;
static int ma3x[MAXN][MAXN];

static char own[MAXN];
static char ref[MAXN];
static int val[MAXN];

static int opt[MAXN];
static int prev[MAXN];

static int row[MAXN], rp;

static char used[MAXN];
static void topsort (int a) {
	used[a] = 1;
	for (int i = 0; i <= N; ++i)
		if (ma3x[a][i] && !used[i])
			topsort (i);

	row[rp++] = a;
}

static int place = 0;
static int score[2] = {0};

static void input () {
	FILE *in = fopen ("score.in", "r");
	if (!in) {printf ("Error opening score.in\n"); exit (-1);}

	fscanf (in, "%d", &N);

	int i, j;
	int tmp;
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j) {
			fscanf (in, "%d", &tmp);
			ma3x[i][j] = tmp;
		}

	for (i = 1; i < N; ++i)
		if (ma3x[i][0]) {
			ma3x[i][0] = 0;
			ma3x[i][N] = 1;
		}

	for (i = 0; i < N; ++i) {
		fscanf (in, "%d", &tmp);
		own[i] = tmp == 2;
	}

	for (i = 0; i < N; ++i) {
		fscanf (in, "%d", &tmp);
		val[i] = tmp;
		ref[tmp] = own[i];
	}
	if (in != stdin) fclose (in);
	//the last one (virtual) will be winning for us but with val 0 :(    :))

	topsort (0);

	int bw, bl;
	int pw = -1, pl = -1;

	for (i = 1; i < rp; ++i) {
		bw = -1; pw = -1;
		bl = INT_MAX; pl = -1;
		for (j = 0; j <= N; ++j) {
			if (!ma3x[row[i]][j]) continue;

			if (ref[opt[j]] == own[row[i]]) {
				if (bw < opt[j]) {
					bw = opt[j];
					pw = j;
				}
			} else {
				if (bl > opt[j]) {
					bl = opt[j];
					pl = j;
				}
			}
		}
		if (bw != -1) {
			if (val[row[i]] > bw) bw = val[row[i]];
			opt[row[i]] = bw;
			prev[row[i]] = pw;
		} else {
			assert (bl != INT_MAX);
			if (val[row[i]] > bl) bl = val[row[i]];
			opt[row[i]] = bl;
			prev[row[i]] = pl;
		}
	}
}

static int first = 1;

int getpos () {
	if (first) {
		first = 0;
		input ();
	}
//	printf ("getpos - now %d, go %d\n", place, prev[place]);
	if (own[place] == 0) {printf ("0\nits your turn!\n"); exit (0);}
	score[own[place]] >?= val[place];
	if (prev[place] == N) {printf ("%d\nCorrect Play!\n", score[0] > score[1]); exit (0);}
	return (place = prev[place] % N) + 1;
}

void setpos (int pl) {
	if (first) {
		first = 0;
		input ();
	}
	--pl;
//	printf ("setpos - now %d, go %d\n", place, pl);
	if (own[place] == 1) {printf ("0\nits my turn!\n"); exit (0);}
	score[own[place]] >?= val[place];
	if (pl == 0) {printf ("%d\nCorrect Play!\n", score[0] > score[1]); exit (0);}
	if (!ma3x[place][pl]) {printf ("0\nWrong Move!\n"); exit (0);}
	place = pl;
}
