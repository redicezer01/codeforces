#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, m, q;
	int lng;	
	int i, j;
	int *mx;
	int icons = 0;
	int empty = 0;

	scanf("%d %d %d", &n, &m, &q);
	getchar();
	lng = n*m;

	mx = (int *) calloc(n*m, sizeof(int));

	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			int c;
	
			if ((c = getchar()) == '\n')
				c = getchar();
	
			if (c == '*') {
				mx[j*n+i] = 1;
				++icons;	
			} else {
				mx[j*n+i] = 0;
			}

		}
	}
	getchar();
	
	
	/* */
	for (i = 0; i < icons; ++i) {
		empty += ((mx[i]) ? 0 : 1);
	}

	while (q--) {
		int x, y, coord;
		scanf("%d %d", &x, &y);
		getchar();		
		coord = (y-1)*n+(x-1);
	
		if (coord < icons) {
			if (mx[coord]) {
				--icons;
		 		mx[coord] = mx[coord] ? 0 : 1;
				if (mx[icons])
					++empty;	
			} else {
		 		mx[coord] = mx[coord] ? 0 : 1;
				if (mx[icons])
					--empty;
				++icons;
			}
		} else {
			if (mx[coord]) {
				--icons;
		 		mx[coord] = mx[coord] ? 0 : 1;
				if (!mx[icons])
					--empty;
			} else {
		 		mx[coord] = mx[coord] ? 0 : 1;
				if (!mx[icons])
					++empty;
				++icons;
			}
		}

		printf("%d\n", empty);

	}
	/* */
		
	free(mx);
	return (0);
}

