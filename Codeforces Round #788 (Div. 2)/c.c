#include <stdio.h>
#include <stdlib.h>

#define MAXN ((int) (1E+5)+1)

/* #define DEBUG */

int main()
{
	int t, i;
	int *aa, *ab, *ac;

	aa = (int *) calloc(MAXN, sizeof(int));
	ab = (int *) calloc(MAXN, sizeof(int));
	ac = (int *) calloc(MAXN, sizeof(int));

	scanf("%d", &t);
	getchar();
		
	while (t--) {
		int n , cnt = 0;
		scanf("%d", &n);
		getchar();
#ifdef DEBUG
		printf("in: %d\n", n);
#endif
		
		int ei;
		for ( i = 1; i <= n; ++i) {
			scanf("%d", &ei);
			aa[i] = ei;			
#ifdef DEBUG
			printf("%d ", ei);
#endif
		}
		getchar();
#ifdef DEBUG
		printf("\n");
#endif

		for ( i = 1; i <= n; ++i) {
			scanf("%d", &ei);
			ab[i] = ei;			
			
			if (ei != aa[i])
				++cnt;
#ifdef DEBUG
			printf("%d ", ei);
#endif
		}	
		getchar();

#ifdef DEBUG
		printf("\n");

		for ( i = 1; i <= n; ++i) {
			printf("%d ", ab[i]);
		}	
		printf("\n");
#endif

		for ( i = 1; i <= n; ++i) {
			scanf("%d", &ei);
			ac[i] = ei;
			if (ei)
				if (aa[i] != ab[i])
					cnt -= 2;
				else
					--cnt;
		}	
		getchar();
		
#ifdef DEBUG
		printf("\n");
#endif

		if (cnt < 1)
			cnt = 1;
		else if (cnt % 2)
			--cnt;

		printf("%d\n", cnt);

#ifdef DEBUG
		printf("\n");
#endif

		for ( i = 1; i <= n; ++i) {
			ac[i] = 0;
		}	
	}
	
	free(aa);
	free(ab);
	free(ac);
	return (0);
}
