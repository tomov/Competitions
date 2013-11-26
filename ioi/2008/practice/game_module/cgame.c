/* This program describes how to use the library for the task "game".
   It plays randomly.
 */

#include "cgamelib.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

	int list[2010], n, left, right, city, i;

	srand(0);
	initialize();
	n=getN();
	for(i=0; i<n; i++)
		list[i] = getValue(i);
	
	left = 0;
	right = n-1;

	while(1) {
		city = rand()%(right-left) + left;
		if(!move(city)) right = city;
		else left = city + 1;
	}

	return 0;
}
