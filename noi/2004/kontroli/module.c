#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int n;
static int move[128][2];
static int cur;
static int ques;
static int que[524288];
static int neis[524288];
static int type[524288];
static int depth[524288];
static int best[524288];
static FILE *fn;
static FILE *fo;
static int kx, ky, cx, cy, bx, by, nx, ny;
static int st=0, turn=0;
static int moves=0;

static void init() {
	int i, j, q, f;
	char tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
	int x, y;

	fn = fopen("chess.in", "r");
	fscanf(fn, "%c%c %c%c %c%c", &tmp1, &tmp2, &tmp3, &tmp4, &tmp5, &tmp6);
	fscanf(fn, "%d", &n);
	for (i=0; i<n; i++) fscanf(fn, "%d %d", &move[i][0], &move[i][1]);
	fclose(fn);

	for (i=0; i<524288; i++) {
		by = i%8;
		bx = (i>>3)%8;
		cy = (i>>6)%8;
		cx = (i>>9)%8;
		ky = (i>>12)%8;
		kx = (i>>15)%8;
		turn = i>>18;
		if ((kx==cx && ky==cy) || (bx==cx && by==cy) || (kx==bx && ky==by)) continue;
		if (turn) {
			if (bx-kx<=1 && kx-bx<=1 && by-ky<=1 && ky-by<=1) {
				type[i] = 1;
				depth[i] = 1;
				best[i] = kx*8+ky;
				que[ques] = i;
				ques++;
			} else if ((bx-cx<=1 && cx-bx<=1 && by-cy<=1 && cy-by<=1) && !(kx-cx<=1 && cx-kx<=1 && ky-cy<=1 && cy-ky<=1)) {
				type[i] = 1;
				depth[i] = 1;
				best[i] = cx*8+cy;
				que[ques] = i;
				ques++;
			} else {
				for (x=bx-1; x<=bx+1; x++) if (x>=0 && x<=7) for (y=by-1; y<=by+1; y++) if (y>=0 && y<=7) {
					if ((x!=bx || y!=by) && (x!=cx || y!=cy) && (x!=kx || y!=ky)) neis[i]++;
				}
			}
		} else {
			if (bx-kx<=1 && kx-bx<=1 && by-ky<=1 && ky-by<=1) {
				type[i] = 1;
				depth[i] = 1;
				best[i] = bx*8+by;
				que[ques] = i;
				ques++;
			} else {
				for (j=0; j<n; j++) if (cx+move[j][0]==bx && cy+move[j][1]==by) break;
				if (j<n) {
					type[i] = 1;
					depth[i] = 1;
					best[i] = 64+bx*8+by;
					que[ques] = i;
					ques++;
				} else {
					for (x=kx-1; x<=kx+1; x++) if (x>=0 && x<=7) for (y=ky-1; y<=ky+1; y++) if (y>=0 && y<=7) {
						if ((x!=bx || y!=by) && (x!=cx || y!=cy) && (x!=kx || y!=ky)) neis[i]++;
					}
					for (j=0; j<n; j++) {
						x = cx+move[j][0];
						y = cy+move[j][1];
						if (x>=0 && x<=7 && y>=0 && y<=7 && (x!=kx || y!=ky)) neis[i]++;
					}
				}
			}
		}
	}

	for (i=0; i<ques; i++) {
		q = que[i];
		if (q==cur) break;
		by = q%8;
		bx = (q>>3)%8;
		cy = (q>>6)%8;
		cx = (q>>9)%8;
		ky = (q>>12)%8;
		kx = (q>>15)%8;
		turn = q>>18;
		if (turn) {
			for (x=kx-1; x<=kx+1; x++) if (x>=0 && x<=7) for (y=ky-1; y<=ky+1; y++) if (y>=0 && y<=7) {
				if ((x!=bx || y!=by) && (x!=cx || y!=cy) && (x!=kx || y!=ky)) {
					f = q-(1<<18)+(x-kx)*(1<<15)+(y-ky)*(1<<12);
					if (type[f]==0) {
						if (type[q]==2) {
							type[f] = 1;
							depth[f] = depth[q]+1;
							best[f] = kx*8+ky;
							que[ques] = f;
							ques++;
						} else if ((--neis[f])==0) {
							type[f] = 2;
							depth[f] = depth[q]+1;
							best[f] = kx*8+ky;
							que[ques] = f;
							ques++;
						}
					}
				}
			}
			for (j=0; j<n; j++) {
				x = cx-move[j][0];
				y = cy-move[j][1];
				if (x>=0 && x<=7 && y>=0 && y<=7 && (x!=bx || y!=by) && (x!=cx || y!=cy) && (x!=kx || y!=ky)) {
					f = q-(1<<18)+(x-cx)*(1<<9)+(y-cy)*(1<<6);
					if (type[f]==0) {
						if (type[q]==2) {
							type[f] = 1;
							depth[f] = depth[q]+1;
							best[f] = 64+cx*8+cy;
							que[ques] = f;
							ques++;
						} else if ((--neis[f])==0) {
							type[f] = 2;
							depth[f] = depth[q]+1;
							best[f] = 64+cx*8+cy;
							que[ques] = f;
							ques++;
						}
					}
				}
			}
		} else {
			for (x=bx-1; x<=bx+1; x++) if (x>=0 && x<=7) for (y=by-1; y<=by+1; y++) if (y>=0 && y<=7) {
				if ((x!=bx || y!=by) && (x!=cx || y!=cy) && (x!=kx || y!=ky)) {
					f = q+(1<<18)+(x-bx)*8+y-by;
					if (type[f]==0) {
						if (type[q]==2) {
							type[f] = 1;
							depth[f] = depth[q]+1;
							best[f] = bx*8+by;
							que[ques] = f;
							ques++;
						} else if ((--neis[f])==0) {
							type[f] = 2;
							depth[f] = depth[q]+1;
							best[f] = bx*8+by;
							que[ques] = f;
							ques++;
						}
					}
				}
			}
		}
	}
	kx = tmp1-'a';
	ky = tmp2-'1';
	cx = tmp3-'a';
	cy = tmp4-'1';
	bx = tmp5-'a';
	by = tmp6-'1';
	cur = (kx<<15)+(ky<<12)+(cx<<9)+(cy<<6)+(bx<<3)+by;
	
	fo = fopen("chess.out", "w");
	st = 1;
	turn = 0;
}

static void quit(char *errmsg) {
	fprintf(fo, "-1 ERROR: %s!\n", errmsg);
	fclose(fo);
	exit(0);
}

static void printMove(int a) {
	fprintf(fo, "%d\n", a*187+moves*2);
	moves++;
}

void moveKing(char a, long b) {
	char errmsg[256];

	if (!st) init();
	if (a<'a' || a>'h' || b<1 || b>8) {
		sprintf(errmsg, "Subroutine moveKing() called with invalid arguments: %c%d", a, b);
		quit(errmsg);
	}
	if (turn==1) quit("White King is moved, but the Black side is on turn");
	if (turn==2) quit("White King is moved after the end of the game");
	nx = a-'a';
	ny = b-1;
	if (nx-kx>1 || kx-nx>1 || ny-ky>1 || ky-ny>1 || (nx==kx && ny==ky)) {
		sprintf(errmsg, "Invalid King move from %c%d to %c%d", 'a'+kx, 1+ky, a, b);
		quit(errmsg);
	}
	if (nx==cx && ny==cy) {
		sprintf(errmsg, "Invalid King move: King moved over Colonel on %c%d", a, b);
		quit(errmsg);
	}
	kx = nx;
	ky = ny;
	if (cx>=0) cur = (cur&07777)+(1<<18)+(kx<<15)+(ky<<12);
	turn = 1;
	printMove(kx*8+ky);
	if (kx==bx && ky==by) turn = 2;
}

void moveColonel(char a, long b) {
	char errmsg[256];
	int i;

	if (!st) init();
	if (a<'a' || a>'h' || b<1 || b>8) {
		sprintf(errmsg, "Subroutine moveColonel() called with invalid arguments: %c%d", a, b);
		quit(errmsg);
	}
	if (turn==1) quit("White Colonel is moved, but the Black side is on turn");
	if (turn==2) quit("White Colonel is moved after the end of the game");
	if (cx<0) quit("White Colonel is moved after it has been captured");
	nx = a-'a';
	ny = b-1;
	for (i=0; i<n; i++) if (cx+move[i][0]==nx && cy+move[i][1]==ny) break;
	if (i==n) {
		sprintf(errmsg, "Invalid Colonel move from %c%d to %c%d", 'a'+cx, 1+cy, a, b);
		quit(errmsg);
	}
	if (nx==kx && ny==ky) {
		sprintf(errmsg, "Invalid Colonel move: Colonel moved over King on %c%d", a, b);
		quit(errmsg);
	}
	cx = nx;
	cy = ny;
	cur = (cur&0770077)+(1<<18)+(cx<<9)+(cy<<6);
	turn = 1;
	printMove(64+cx*8+cy);
	if (cx==bx && cy==by) turn = 2;
}

void getKing(char *a, long *b) {

	if (!st) init();
	if (turn==0) quit("getKing() called, but the White side is on turn");
	if (turn==2) quit("getKing() is called after the end of the game");
	if (cx>=0) {
		bx = (best[cur]>>3)%8;
		by = best[cur]%8;
		cur = (cur&0777700)+best[cur];
	} else {
		for (nx=bx-1; nx<=bx+1; nx++) {
			for (ny=by-1; ny<=by+1; ny++) {
				if ((nx!=bx || ny!=by) && (nx-kx>1 || kx-nx>1 || ny-ky>1 || ky-ny>1)) break;
			}
			if (ny<=by+1) break;
		}
		bx = nx;
		by = ny;
	}
	turn = 0;
	*a = 'a'+bx;
	*b = 1+by;
	printMove(bx*8+by);
	if (cx==bx && cy==by) cx = -1;
	if (kx==bx && ky==by) turn = 2;
}
