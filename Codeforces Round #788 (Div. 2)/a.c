#include <stdio.h>
#include <stdlib.h>

#define MAXN ((int) 1e+5)
#define abs(n) ((n < 0) ? -n : n)

int main()
{
	int t;
	int *a;
	
	a = (int *) calloc(MAXN, sizeof(int));

	scanf("%d", &t);
	getchar();

	while (t--) {
		int n, i ,j;
		scanf("%d", &n);
		getchar();
		
		int ai;
		int minus = 0;
		int yes = 1;
		for (i = 0; i < n; ++i) {
			scanf("%d", &ai);
			if (ai < 0)
				++minus;
			a[i] = abs(ai);	
		}
		getchar();
		
		for (i = 0; i < n; ++i) {
			if (minus) {
				a[i] = -a[i];		
				--minus;
			}

			if (i && a[i] < a[i-1]) {
				yes = 0;
				break;
			}
		}

		printf("%s\n", (yes) ? "YES" : "NO");
			
	}

	free(a);
	return (0);
}
