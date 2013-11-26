#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int hash;
	int pos;
} SHash;

#define CONVERT(x) (((x) >= 'A' && (x) <= 'F') ? (x) - 'A' + 10 : (x) - '0')
#define PRIME	((1 << 25) - 39)
#define SIZE	16
#define LIMIT   100001

int n;
char lines[32][LIMIT];
int s[32][LIMIT];
SHash *first[LIMIT], *second[LIMIT];
SHash firstarr[LIMIT], secondarr[LIMIT];
int first_ptr = 0;
int second_ptr = 0;

int fcmp(const void *e1, const void *e2) {
	SHash *s1, *s2;

	s1 = *((SHash **)e1);
	s2 = *((SHash **)e2);
	return s1->hash - s2->hash;
}

int hash_prog(SHash **temp, SHash *arr, int *s, int len) {
	int i, sum = 0;
	int mul = 1;
	
	for (i = 0; i < len; i++) {
		sum = (sum*SIZE + s[i])%PRIME;
		if (i > 0) 
			mul = (mul*SIZE)%PRIME;
	}
	
	i = 0;
	while (1) {
		temp[i] = arr + i;
		arr[i].pos = i;
		arr[i].hash = sum;
		if (s[i + len] == -1)
			break;
		sum = (SIZE*(PRIME + sum - (mul*s[i])%PRIME) + s[i + len])%PRIME;
		i++;
	}

	i++;
	qsort(temp, i, sizeof(SHash *), fcmp);
	return i;
}

void check_virus(int l) {
	int k, i, j, wr;
	
	first_ptr = hash_prog(first, firstarr, s[0], l);
	for (k = 1; k < n; k++) {
		second_ptr = hash_prog(second, secondarr, s[k], l);
		i = j = wr = 0;
		while (i < first_ptr && j < second_ptr)
			if (first[i]->hash < second[j]->hash)
				i++;
			else
				if (first[i]->hash > second[j]->hash)
					j++;
				else {
					first[wr]->hash = first[i]->hash;
					first[wr++]->pos = first[i++]->pos;
				}
		first_ptr = wr;
		if (!wr)
			break;
	}
}

int pos;
int candidates(int l) {
	static char line[LIMIT];
	int i, k, c = 0;
	int flag;

	line[l] = 0;
	for (i = 0; i < first_ptr; i++) {
		memcpy(line, lines[0] + first[i]->pos, l);
		flag = 1;
		for (k = 1; k < n; k++)
			if (!strstr(lines[k], line)) {
				flag = 0;
				break;
			}
		if (flag) {
			c++;
			pos = first[i]->pos;
			if (c > 1)
				return c;
		}
	}
	return c;
}

int main() {
	int i, j, l, h;
	
	scanf("%i\n", &n);
	h = LIMIT + 1;
	for (i = 0; i < n; i++) {
		fgets(lines[i], LIMIT, stdin);
		l = strlen(lines[i]) - 1;
		if (l < h)
			h = l;
		lines[i][l] = 0;
		for (j = 0; j < l; j++)
			s[i][j] = CONVERT(lines[i][j]);
		s[i][l] = -1;
	}
	
	l = h/10 - 1;
	h = h/2 + 1;

	while (1) {
		i = (l + h)/2;
		check_virus(i);
		j = candidates(i);
		if (j < 1)
			h = i;
		if (j == 1)
			break;
		if (j > 1)
			l = i;
	}

	lines[0][pos + i] = 0;
	printf("%s\n", lines[0] + pos);

	return 0;
}

