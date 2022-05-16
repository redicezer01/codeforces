#include <stdio.h>
#include <stdlib.h>

#define MAXN ((int) 2E+5+1)

int main()
{
	int t, n, i, j;
	int *p , *r;
	int *used;
	char *s;

	
	p = (int *) calloc(MAXN, sizeof(int));
	r = (int *) calloc(MAXN, sizeof(int));
	s = (char *) calloc(MAXN, sizeof(char));
	used = (int *) calloc(MAXN, sizeof(int));
	
	scanf("%d", &t);
	getchar();

	while (t--) {
		scanf("%d", &n);
		getchar();

		
		for (i = 1; i <= n; ++i) {
			int a;
			scanf("%d", &a);
			p[i] = a;	
			if (!used[a] && a != i)
				used[a] = i;
			printf("%d ", p[i]);
		}
		getchar();
		putchar('\n');

		/**/
		
		int len = 0;
		for (i = 1; i <= n; ++i) {
			if (!used[p[i]] && p[i])  {
				sprintf(s, "%d ", p[i]);
				++len;		
				used[p[i]] = 1;
			}
			if (!used[i])  {
				sprintf(s, "%d ", i);
				++len;		
				used[i] = 1;
			}
			for (j = i; j <= n; ++j) {
				sprintf(s, "%d ", r[j]);
				++len;		
				used[i] = 1;
					
			}
			printf("%d\n", len);
			printf("%s\n", s);
		}
		printf("%d\n", j);
		s[j] = '\0';
		printf("%d\n%s\n", len, s);
		len = 0;
		/**/	
				
		for (i = 1; i <= n; ++i) {
			/* printf("%d ", used[i]); */
			
			r[i] = 0;
			used[i] = 0;
		}
		putchar('\n');
		putchar('\n');
		
	}

	free(p);
	free(r);
	free(s);
	free(used);
	return (0);
}
