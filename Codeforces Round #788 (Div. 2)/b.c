#include <stdio.h>
#include <stdlib.h>

#define MAXN ((int) 1e+5+1)

char spec['z' + 1];

int main()
{
	int t;
	char *s;
	
	s = (char *) calloc(MAXN, sizeof(char));

	scanf("%d", &t);
	getchar();

	while (t--) {
		int n, k, i;
		scanf("%d", &n);
		getchar();

		fgets(s, n+1, stdin);
		s[n] = '\0';
		getchar();

		scanf("%d", &k);		
		char c;		
		for (i = 0; i < k; ++i) {
			getchar();
			c = getchar();
			spec[c] = 1;
		}	
		getchar();
		
		int max, cnt;
		max  =  cnt  = 0;
		for (i = 0; i < n; ++i) {
			if (spec[s[i]]) {
				max = (cnt > max) ? cnt : max;
				/* printf("cnt: %d, max: %d\n", cnt, max); */
				cnt = 0;
			}
			++cnt;
		}

		for (i = 'a'; i <= 'z'; ++i) {
			spec[i] = 0;
		}
		printf("%d\n", max);
	}

	free(s);
	return (0);
}
