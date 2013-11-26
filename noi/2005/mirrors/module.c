#include <stdio.h>
#include <stdlib.h>

#define TEST_FILE		"mirrors.in"
#define OUT_FILE		"mirrors.out"
#define STATE_DOWN		0
#define STATE_RIGHT		1
#define STATE_LEFT		2
#define MAX_SIZE		128
#define MAX_P			128
#define DIR_UP			0
#define DIR_DOWN		1
#define DIR_LEFT		2
#define DIR_RIGHT		3
#define ROMEO			0
#define JULIET			1

static int init_called;
static int n, m, p;
static int romeo_pos, romeo_row, romeo_col, romeo_dir;
static int juliet_pos, juliet_row, juliet_col, juliet_dir;
static int state_table[MAX_SIZE][MAX_SIZE];
static int mirror_pos[MAX_P][2];
static char position_used[MAX_SIZE][MAX_SIZE];	// one based index of a changeable mirror; zero otherwise

static int path_number[MAX_P+4][3][4][MAX_P];	// mirror; state; direction; mirror position on path
static int path_dir[MAX_P+4][3][4][MAX_P];
static int path_end[MAX_P+4][3][4];

// should be synchronized with DIR_* and STATE_* definitions
static int transition_table[4][3]=
{
	{ DIR_UP, DIR_RIGHT, DIR_LEFT },
	{ DIR_DOWN, DIR_LEFT, DIR_RIGHT },
	{ DIR_LEFT, DIR_DOWN, DIR_UP },
	{ DIR_RIGHT, DIR_UP, DIR_DOWN }
};

// should be synchronized with DIR_* definitions
static int row_change[4]= { -1, 1, 0, 0};
static int col_change[4]= { 0, 0, -1, 1};

static FILE *fp, *fpo;

//	exits the program when needed
static void my_exit(char *msg)
{
	//fpo=fopen(OUT_FILE, "w");
	fpo=stdout;

	fprintf(fpo, msg);
	fprintf(fpo, "\n");

	//fclose(fpo);

	if(fp)
		fclose(fp);

	exit(0);
}

// help function for getting the information out of a position around the table
static void getDetailedInfo(int pos, int *r, int *c, int *dir)
{
	if(pos<=n)
	{
		*r=pos-1; *c=0; *dir=DIR_RIGHT;
	}
	else
		if(pos<=n+m)
		{
			*r=n-1; *c=pos-n-1; *dir=DIR_UP;
		}
		else
			if(pos<=n+m+n)
			{
				*r=n-(pos-n-m); *c=m-1; *dir=DIR_LEFT;
			}
			else
			{
				*r=0; *c=m-(pos-n-m-n); *dir=DIR_DOWN;
			}
}

//	returns position around the table based on row and column information
static int getCompiledPosition(int r, int c)
{
	if(r==-1) // top side
		return n+m+n+m-c;

	if(c==-1) // left side
		return r+1;

	if(r==n) // bottom side
		return n+c+1;

	if(c==m) // right side
		return n+m+n-r;

	return -1;
}

//	precomputes data for a single changeable mirror
//	note : function works for romeo and juliet too
static void mirror_precompute(int ind, int r, int c, int dir, int current_state)
{
	int start_r=r, start_c=c, start_dir=dir;
	int state, current_number=1, mirr;

	if(ind>=p && position_used[r][c])	// romeo and juliet may encounter changeable mirror on the first position of their path
	{
		mirr=position_used[r][c]-1;
		path_number[ind][current_state][dir][mirr]=current_number;
		path_dir[ind][current_state][dir][mirr]=dir;
	}

	while(r>=0 && r<n && c>=0 && c<m)
	{
		state=state_table[r][c];

		if(ind<p && r==mirror_pos[ind][0] && c==mirror_pos[ind][1])
			state=current_state;

		dir=transition_table[dir][state];
		r+=row_change[dir];
		c+=col_change[dir];

		current_number++;

		if(r==start_r && c==start_c && dir==start_dir)	// cycle found : no need to save anything since it won't be used in the query function
			return;

		if(r>=0 && r<n && c>=0 && c<m)
			if(position_used[r][c])
			{
				mirr=position_used[r][c]-1;
				if(!path_number[ind][current_state][start_dir][mirr])	// some mirrors may appear more than once; ignore all appearances after the first one
				{
					path_number[ind][current_state][start_dir][mirr]=current_number;
					path_dir[ind][current_state][start_dir][mirr]=dir;
				}
			}
	}

	path_end[ind][current_state][start_dir]=getCompiledPosition(r, c);
}

//	precomputes data so that queries can be done fast
static void precompute_path_data()
{
	int i, j, k;

	for(i=0; i<p; i++)	// for each mirror
		for(j=0; j<3; j++)	// for each state
			for(k=0; k<4; k++)	// for each direction
				mirror_precompute(i, mirror_pos[i][0], mirror_pos[i][1], k, j);

	mirror_precompute(p, romeo_row, romeo_col, romeo_dir, 0);	// for romeo
	mirror_precompute(p+1, juliet_row, juliet_col, juliet_dir, 0);	// for juliet
}

//	call before any other calls
void init()
{
	int i, j;

	if(init_called)
		my_exit("You're trying to call init more than once!");

	init_called=1;
	fp=fopen(TEST_FILE, "r");

	if(!fp)
		my_exit("Input file does not exist!");

	if(fscanf(fp, "%d%d", &n, &m)!=2)
		my_exit("Invalid input file!");

	if(n<1 || n>MAX_SIZE || m<1 || m>MAX_SIZE)
		my_exit("Invalid table dimensions!");

	for(i=0; i<n; i++)
		for(j=0; j<m; j++)
		{
			if(fscanf(fp, "%d", state_table[i]+j)!=1)
				my_exit("Invalid input file!");

			if(state_table[i][j]!=STATE_DOWN && state_table[i][j]!=STATE_RIGHT && state_table[i][j]!=STATE_LEFT)
				my_exit("Some of the table cells are invalid!");
		}


	if(fscanf(fp, "%d%d", &romeo_pos, &juliet_pos)!=2)
		my_exit("Invalid input file!");

	if(romeo_pos<1 || romeo_pos>m+m+n+n || juliet_pos<1 || juliet_pos>m+m+n+n)
		my_exit("Romeo and/or Juliet position is invalid!");


	if(fscanf(fp, "%d", &p)!=1)
		my_exit("Invalid input file!");

	if(p<0 || p>MAX_P)
		my_exit("Number of changeable mirrors is invalid!");

	for(i=0; i<p; i++)
	{
		if(fscanf(fp, "%d%d", mirror_pos[i]+0, mirror_pos[i]+1)!=2)
			my_exit("Invalid input file!");

		if(mirror_pos[i][0]<0 || mirror_pos[i][0]>=n || mirror_pos[i][1]<0 || mirror_pos[i][1]>=m)
			my_exit("Invalid mirror positions!");

		if(position_used[mirror_pos[i][0]][mirror_pos[i][1]])
			my_exit("Some of the changeable mirrors have the same position!");

		position_used[mirror_pos[i][0]][mirror_pos[i][1]]=i+1;
	}


	fclose(fp);
	fp=NULL;

	getDetailedInfo(romeo_pos, &romeo_row, &romeo_col, &romeo_dir);
	getDetailedInfo(juliet_pos, &juliet_row, &juliet_col, &juliet_dir);

	precompute_path_data();
}

//	returns table height
int getN()
{
	if(!init_called)
		my_exit("Init not called!");

	return n;
}

//	returns table width
int getM()
{
	if(!init_called)
		my_exit("Init not called!");

	return m;
}

//	returns number of moveable mirrors
int getP()
{
	if(!init_called)
		my_exit("Init not called!");

	return p;
}

static int listed_mirrors[MAX_P];
//	checks the input of the user and exits with an error message if something is wrong
//	input for the getView function
static void check_input(int num, int *mirrors, int *states)
{
	int i;

	if(num<0 || num>6)
		my_exit("Query with an invalid number of mirrors!");

	for(i=0; i<num; i++)
	{
		if(mirrors[i]<0 || mirrors[i]>=p)
			my_exit("Query with an invalid mirror number!");

		if(states[i]!=STATE_DOWN && states[i]!=STATE_RIGHT && states[i]!=STATE_LEFT)
			my_exit("Query with an invalid mirror state!");

		if(listed_mirrors[mirrors[i]])
			my_exit("Some mirrors are repeated in the list!");

		listed_mirrors[mirrors[i]]=1;
	}

	for(i=0; i<num; i++)
		listed_mirrors[mirrors[i]]=0;
}

//	not a public function
//	returns ray destination as a number around the table
//	this version of the module uses this version of the function only to check the faster one for correctness
static int getFinalDestination(int r, int c, int dir, int num, int *mirrors, int *states)
{
	int i, state;

	while(r>=0 && r<n && c>=0 && c<m)
	{
		state=state_table[r][c];

		for(i=0; i<num; i++)
			if(mirror_pos[mirrors[i]][0]==r && mirror_pos[mirrors[i]][1]==c)
				state=states[i];

		dir=transition_table[dir][state];
		r+=row_change[dir];
		c+=col_change[dir];
	}

	return getCompiledPosition(r, c);
}

//	not a public function
//	returns ray destination as a number around the table
//	faster version of the above function
//	uses precomputing and has complexity somewhere around num^2
static int getFinalDestinationFast(int person, int r, int c, int dir, int num, int *mirrors, int *states)
{
	int i, state, ind, best, bestind, tmp;

	if(person==ROMEO)	ind=p;
	else				ind=p+1;

	state=0;	// data for romeo and juliet is written as state 0 though they don't have a state as mirrors do

	while(1)
	{
		best=0x7fffffff;
		for(i=0; i<num; i++)
		{
			tmp=path_number[ind][state][dir][mirrors[i]];
			if(tmp && tmp<best)
			{
				best=tmp;
				bestind=i;
			}
		}

		if(best==0x7fffffff)	// no changed mirror found on the path
			return path_end[ind][state][dir];

		dir=path_dir[ind][state][dir][mirrors[bestind]];
		state=states[bestind];
		ind=mirrors[bestind];
	}

	return -1;
}

//	used by the contester to check his/her guesses
void getView(int num, int *mirrors, int *states, int *romeo_view, int *juliet_view)
{
	if(!init_called)
		my_exit("Init not called!");

	check_input(num, mirrors, states);

	*romeo_view=getFinalDestinationFast(ROMEO, romeo_row, romeo_col, romeo_dir, num, mirrors, states);
	*juliet_view=getFinalDestinationFast(JULIET, juliet_row, juliet_col, juliet_dir, num, mirrors, states);

	// this is just for debugging : it compares the values returned by the slower and faster functions
	/*{
		int r2, j2;
		r2=getFinalDestination(romeo_row, romeo_col, romeo_dir, num, mirrors, states);
		j2=getFinalDestination(juliet_row, juliet_col, juliet_dir, num, mirrors, states);

		if(r2!=*romeo_view || j2!=*juliet_view || *romeo_view<1 || *juliet_view<1)
		{
			printf("FATAL ERROR!\n");
			my_exit("FATAL ERROR : module not working properly!");
		}
	}*/
	
	if(*romeo_view==juliet_pos && *juliet_view==romeo_pos)
		my_exit("Correct Answer!");
}
